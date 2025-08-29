#include "../cub3D.h"

#define FOV (M_PI / 3.0) // 60 degrees

static void put_vline(mlx_image_t *img, int x, int y0, int y1, uint32_t color)
{
    int y;

    if (!img || x < 0 || x >= (int)img->width)
        return;
    if (y0 < 0)
        y0 = 0;
    if (y1 >= (int)img->height)
        y1 = img->height - 1;
    y = y0;
    while (y <= y1)
    {
        mlx_put_pixel(img, x, y, color);
        y++;
    }
}

static uint32_t shade_color(uint32_t color)
{
    uint32_t a;
    uint32_t b;
    uint32_t g;
    uint32_t r;

    a = color & 0x000000FF;
    b = (color >> 8) & 0x000000FF;
    g = (color >> 16) & 0x000000FF;
    r = (color >> 24) & 0x000000FF;
    r = r / 2;
    g = g / 2;
    b = b / 2;
    return (r << 24) | (g << 16) | (b << 8) | a;
}

static int init_screen(t_game *g)
{
    if (!g->conf->screen)
    {
        g->conf->screen = mlx_new_image(g->mlx, WIDTH, HEIGHT);
        if (!g->conf->screen)
        {
            printf(RED"Failed to create screen image\n"RESET);
            return (0);
        }
        mlx_image_to_window(g->mlx, g->conf->screen, 0, 0);
    }
    return (1);
}

static void get_background_colors(t_game *g, uint32_t *ceil_col, 
                                  uint32_t *floor_col)
{
    if (g->conf->ceiling_color == -1)
        *ceil_col = 0x87CEEBFF;
    else
        *ceil_col = (uint32_t)g->conf->ceiling_color;
    if (g->conf->floor_color == -1)
        *floor_col = 0x3CB371FF;
    else
        *floor_col = (uint32_t)g->conf->floor_color;
}

static void fill_background(mlx_image_t *img, t_game *g)
{
    uint32_t ceil_col;
    uint32_t floor_col;
    uint32_t row_color;
    int y;
    int x;

    get_background_colors(g, &ceil_col, &floor_col);
    y = 0;
    while (y < (int)img->height)
    {
        if ((unsigned int)y < img->height / 2)
            row_color = ceil_col;
        else
            row_color = floor_col;
        x = 0;
        while (x < (int)img->width)
        {
            mlx_put_pixel(img, x, y, row_color);
            x++;
        }
        y++;
    }
}

static void init_ray_data(t_game *g, int x, double *ray_data)
{
    double posX;
    double posY;
    double cameraX;

    posX = (double)g->player.x / (double)TILE;
    posY = (double)g->player.y / (double)TILE;
    cameraX = 2.0 * x / (double)WIDTH - 1.0;
    ray_data[0] = posX;
    ray_data[1] = posY;
    ray_data[2] = g->player.angle + cameraX * (FOV / 2.0);
    ray_data[3] = sin(ray_data[2]);
    ray_data[4] = -cos(ray_data[2]);
    if (ray_data[3] == 0)
        ray_data[5] = 1e30;
    else
        ray_data[5] = fabs(1.0 / ray_data[3]);
    if (ray_data[4] == 0)
        ray_data[6] = 1e30;
    else
        ray_data[6] = fabs(1.0 / ray_data[4]);
}

static void setup_ray_step(double *ray_data, int *step_data, double *side_data)
{
    if (ray_data[3] < 0)
    {
        step_data[0] = -1;
        side_data[0] = (ray_data[0] - (int)ray_data[0]) * ray_data[5];
    }
    else
    {
        step_data[0] = 1;
        side_data[0] = ((int)ray_data[0] + 1.0 - ray_data[0]) * ray_data[5];
    }
    if (ray_data[4] < 0)
    {
        step_data[1] = -1;
        side_data[1] = (ray_data[1] - (int)ray_data[1]) * ray_data[6];
    }
    else
    {
        step_data[1] = 1;
        side_data[1] = ((int)ray_data[1] + 1.0 - ray_data[1]) * ray_data[6];
    }
}

static int check_wall_hit(t_game *g, int *map_data)
{
    char c;

    if (map_data[1] < 0 || map_data[1] >= g->conf->map_height ||
        map_data[0] < 0 || map_data[0] >= g->conf->map_width)
        return (1);
    c = g->conf->map[map_data[1]][map_data[0]];
    if (c == '1')
        return (1);
    return (0);
}

static int perform_dda(t_game *g, double *ray_data, int *step_data, 
                       double *side_data, int *map_data)
{
    int hit;
    int side;

    hit = 0;
    side = 0;
    while (!hit)
    {
        if (side_data[0] < side_data[1])
        {
            side_data[0] += ray_data[5];
            map_data[0] += step_data[0];
            side = 0;
        }
        else
        {
            side_data[1] += ray_data[6];
            map_data[1] += step_data[1];
            side = 1;
        }
        hit = check_wall_hit(g, map_data);
    }
    return (side);
}

static double calculate_wall_distance(double *ray_data, int *step_data, 
                                      int *map_data, int side, int hit)
{
    double perpWallDist;

    if (!hit)
        perpWallDist = 1e30;
    else
    {
        if (side == 0)
            perpWallDist = (map_data[0] - ray_data[0] + 
                           (1 - step_data[0]) / 2.0) / ray_data[3];
        else
            perpWallDist = (map_data[1] - ray_data[1] + 
                           (1 - step_data[1]) / 2.0) / ray_data[4];
        if (perpWallDist <= 0)
            perpWallDist = 1e-6;
    }
    return (perpWallDist);
}

static void draw_wall_line(mlx_image_t *img, int x, double perpWallDist, int side)
{
    int lineHeight;
    int drawStart;
    int drawEnd;
    uint32_t color;

    lineHeight = (int)((double)HEIGHT / perpWallDist);
    drawStart = -lineHeight / 2 + HEIGHT / 2;
    drawEnd = lineHeight / 2 + HEIGHT / 2;
    color = 0xBBBBBBFF;
    if (side == 1)
        color = shade_color(color);
    put_vline(img, x, drawStart, drawEnd, color);
}

static void cast_single_ray(t_game *g, int x, mlx_image_t *img)
{
    double ray_data[7];
    double side_data[2];
    int step_data[2];
    int map_data[2];
    double perpWallDist;
    int side;
    int hit;

    init_ray_data(g, x, ray_data);
    map_data[0] = (int)ray_data[0];
    map_data[1] = (int)ray_data[1];
    setup_ray_step(ray_data, step_data, side_data);
    hit = 1;
    side = perform_dda(g, ray_data, step_data, side_data, map_data);
    perpWallDist = calculate_wall_distance(ray_data, step_data, 
                                           map_data, side, hit);
    draw_wall_line(img, x, perpWallDist, side);
}

void render_frame(t_game *g)
{
    mlx_image_t *img;
    int x;
    // (void)x;
    // (void)cast_single_ray;

    if (!g || !g->conf || !g->conf->map || !g->mlx)
        return;
    if (!init_screen(g))
        return;
    img = g->conf->screen;
    fill_background(img, g);
    x = 0;
    while (x < WIDTH)
    {
        cast_single_ray(g, x, img);
        x++;
    }
}
