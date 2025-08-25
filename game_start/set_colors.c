#include "../cub3D.h"

void ft_set_ceil_floor_color(t_game * game)
{
    mlx_image_t *image = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	for(int y = 0; y < HEIGHT / 2; y++){

		for(int x = 0; x < WIDTH; x++){
			uint32_t color = game->conf->ceiling_color;
			mlx_put_pixel(image, x ,y, color);
		}
	}
	for(int y = HEIGHT / 2; y < HEIGHT ; y++){

		for(int x = 0; x < WIDTH; x++){
			uint32_t color = game->conf->floor_color;
			mlx_put_pixel(image, x ,y, color);
		}
	}
	mlx_image_to_window(game->mlx, image, 0, 0);
}