#include "../cub3D.h"

static void put_player(mlx_image_t *img, int x, int y, uint32_t color)
{
    // Draw a simple 5x5 square for the player
    for (int dy = -5; dy < 5; dy++)
    {
        for (int dx = -5; dx < 5; dx++)
        {
            int pixel_x = x + dx;
            int pixel_y = y + dy;
            
            // Bounds checking to prevent segfault
            if (pixel_x >= 0 && pixel_x < (int)img->width && 
                pixel_y >= 0 && pixel_y < (int)img->height)
            {
                mlx_put_pixel(img, pixel_x, pixel_y, color);
            }
        }
    }
}

static void put_square(mlx_image_t *img, int x, int y, uint32_t color)
{
    for (int dy = 0; dy < TILE; dy++)
    {
        for (int dx = 0; dx < TILE; dx++)
        {
            int pixel_x = x + dx;
            int pixel_y = y + dy;
            
            // Bounds checking to prevent segfault
            if (pixel_x >= 0 && pixel_x < (int)img->width && 
                pixel_y >= 0 && pixel_y < (int)img->height)
            {
                // printf(YELLOW"Putting pixel at (%d, %d) with color 0x%X\n"RESET, pixel_x, pixel_y, color);
                mlx_put_pixel(img, pixel_x, pixel_y, color);
            }
        }
    }
}

void draw_minimap(t_game *g)
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
        g->conf->img = mlx_new_image(g->mlx, WIDTH / 5, HEIGHT / 5);
        if (!g->conf->img)
        {
            printf(RED"Error: Failed to create MLX image\n"RESET);
            return;
        }
        mlx_image_to_window(g->mlx, g->conf->img, 0, 0);
    }

    for (int y = 0; y < g->conf->map_height; y++)
    {
        if (!g->conf->map[y])
            continue;
            
        for (int x = 0; x < g->conf->map_width; x++)
        {
            // Make sure we don't go out of bounds
            if (x >= (int)ft_strlen(g->conf->map[y]))
                continue;
                
            if (g->conf->map[y][x] == '1')
            {
                put_square(g->conf->img, x * TILE, y * TILE, 0x4F003AFF);
            }
            else
            {
                put_square(g->conf->img, x * TILE, y * TILE, 0xFFD856FF);
            }

        }
    }

    // Player dot
    put_player(g->conf->img, g->player.x, g->player.y, 0x000000FF);
//    mlx_put_pixel(g->conf->img, g->player.x, g->player.y, 0x000000FF);
}
