#include "../cub3D.h"

void handle_input(void *param)
{
    t_game *g = (t_game *)param;
    bool redraw = false;

    if (mlx_is_key_down(g->mlx, MLX_KEY_UP))
    {
        g->player.y -= cos(g->player.angle) * g->player.speed;
        g->player.x += sin(g->player.angle) * g->player.speed;
        redraw = true;
    }
    if (mlx_is_key_down(g->mlx, MLX_KEY_DOWN))
    {
        g->player.y += cos(g->player.angle) * g->player.speed;
        g->player.x -= sin(g->player.angle) * g->player.speed;
        redraw = true;
    }
    if (mlx_is_key_down(g->mlx, MLX_KEY_LEFT))
    {
        g->player.x -= cos(g->player.angle) * g->player.speed;
        g->player.y -= sin(g->player.angle) * g->player.speed;
        redraw = true;
    }
    if (mlx_is_key_down(g->mlx, MLX_KEY_RIGHT))
    {
        g->player.x += cos(g->player.angle) * g->player.speed;
        g->player.y += sin(g->player.angle) * g->player.speed;
        redraw = true;
    }
    
    if (redraw)
        draw_minimap(g);
}
