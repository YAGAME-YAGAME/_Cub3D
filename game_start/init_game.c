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
	if (!game->conf)
		return ;
	game->conf->no_texture_path = NULL;
	game->conf->so_texture_path = NULL;
	game->conf->we_texture_path = NULL;
	game->conf->ea_texture_path = NULL;
	game->conf->floor_color = -1;
	game->conf->ceiling_color = -1;
	game->conf->map = NULL;
	game->conf->img = NULL;
	game->conf->screen = NULL;
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

	// Create initial render and minimap
	render_frame(game);
	printf(GREEN"Drawing minimap\n"RESET);
	draw_minimap(game);

	mlx_loop_hook(game->mlx, handle_input, game);
	mlx_loop(game->mlx);

	mlx_terminate(game->mlx);
	return (EXIT_SUCCESS);
}

