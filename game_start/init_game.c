#include "../cub3D.h"

#define WIDTH 1024
#define HEIGHT 750

// Function to convert RGB to MLX color format (0xRRGGBBAA)
uint32_t rgb_to_mlx_color(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

// Function to fill a rectangular area with a specific color
void fill_rect(mlx_image_t *img, int x, int y, int width, int height, uint32_t color)
{
	int i, j;
	
	for (i = y; i < y + height && i < (int)img->height; i++)
	{
		for (j = x; j < x + width && j < (int)img->width; j++)
		{
			mlx_put_pixel(img, j, i, color);
		}
	}
}

int start_game(t_game *game)
{
	mlx_image_t *background_img;
	uint32_t blue_color;
	uint32_t red_color;
	
	// Initialize MLX
	game->mlx = mlx_init(WIDTH, HEIGHT, "CUB3D", true);
	if(!game->mlx)
	{
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}

	// Create an image for the background
	background_img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!background_img)
	{
		puts(mlx_strerror(mlx_errno));
		mlx_terminate(game->mlx);
		return(EXIT_FAILURE);
	}

	// Define colors (RGB format with alpha = 255 for opaque)
	blue_color = rgb_to_mlx_color(0, 0, 255, 255);  // Pure blue
	red_color = rgb_to_mlx_color(255, 0, 0, 255);   // Pure red

	// Fill top half with blue
	fill_rect(background_img, 0, 0, WIDTH, HEIGHT / 2, blue_color);
	
	// Fill bottom half with red
	fill_rect(background_img, 0, HEIGHT / 2, WIDTH, HEIGHT / 2, red_color);

	// Display the image on the window
	if (mlx_image_to_window(game->mlx, background_img, 0, 0) == -1)
	{
		puts(mlx_strerror(mlx_errno));
		mlx_delete_image(game->mlx, background_img);
		mlx_terminate(game->mlx);
		return(EXIT_FAILURE);
	}

	// Start the main loop
	mlx_loop(game->mlx);
	
	// Cleanup
	mlx_delete_image(game->mlx, background_img);
	mlx_terminate(game->mlx);
    return (EXIT_SUCCESS);
}
	
