#include "../cub3D.h"


static void put_square(mlx_image_t *img, int x, int y, uint32_t color)
{
    for (int dy = 0; dy < TILE; dy++)
    {
        for (int dx = 0; dx < TILE; dx++)
            mlx_put_pixel(img, x + dx, y + dy, color);
    }
}

void draw_map(t_game *g)
{
    // Check for null pointers
    if (!g || !g->conf || !g->conf->map || !g->mlx)
    {
        printf(RED"Error: Invalid game data in draw_map\n"RESET);
        return;
    }
    
    // Create image if it doesn't exist
    if (!g->conf->img)
    {
        g->conf->img = mlx_new_image(g->mlx, WIDTH, HEIGHT);
        if (!g->conf->img)
        {
            printf(RED"Error: Failed to create MLX image\n"RESET);
            return;
        }
        mlx_image_to_window(g->mlx, g->conf->img, 0, 0);
    }
    
    printf(GREEN"Drawing map: %dx%d\n"RESET, g->conf->map_width, g->conf->map_height);
    
    for (int y = 0; y < g->conf->map_height; y++)
    {
        for (int x = 0; x < g->conf->map_width; x++)
        {
            if (g->conf->map[y][x] == '1')
                put_square(g->conf->img, x * TILE, y * TILE, 0x333333FF);
            else
                put_square(g->conf->img, x * TILE, y * TILE, 0xDDDDDDFF);
        }
    }

    // Player dot
    mlx_put_pixel(g->conf->img, (int)g->player.x, (int)g->player.y, 0xFF0000FF);
}