#include "../cub3D.h"

void ft_error(char *msg)
{
	ft_putstr_fd("Error : ", 2);
	ft_putstr_fd(msg, 2);
}

void _init(t_game *game)
{
	if(!game)
		return ;
	game->player.x =  0;
	game->player.y =  0;
	game->player.dir = 'N';
	game->player.angle = 0.0f;
	game->player.speed = 1;
	game->conf->no_texture_path = NULL;
	game->conf->so_texture_path = NULL;
	game->conf->we_texture_path = NULL;
	game->conf->ea_texture_path = NULL;
	game->conf->floor_color = -1;
	game->conf->ceiling_color = -1;
	game->conf->map = NULL;
	game->conf->img = NULL;
	game->conf->map_width = 0;
	game->conf->map_height = 0;
}

int start_game(t_game *game)
{
	if(!game)
		return (EXIT_FAILURE);
	game->mlx = mlx_init(WIDTH, HEIGHT, "CUB3D", false);
	if(!game->mlx)
	{
		ft_error("MLX initialization failed!");
		return (EXIT_FAILURE);
	}

	ft_set_ceil_floor_color(game);
	printf(GREEN"Drawing minimap\n"RESET);
	draw_minimap(game);

	mlx_loop_hook(game->mlx, handle_input, game);
	mlx_loop(game->mlx);

	mlx_terminate(game->mlx);
	return (EXIT_SUCCESS);
}
	
