#include "../cub3D.h"

void handle_input(void *param)
{
    t_game *g = (t_game *)param;
    bool redraw = false;

    // Movement forward/back
    if (mlx_is_key_down(g->mlx, MLX_KEY_W) || mlx_is_key_down(g->mlx, MLX_KEY_UP))
    {
        double nx = g->player.x + sin(g->player.angle) * g->player.speed;
        double ny = g->player.y - cos(g->player.angle) * g->player.speed;
        g->player.x = (int)nx;
        g->player.y = (int)ny;
        redraw = true;
    }
    if (mlx_is_key_down(g->mlx, MLX_KEY_S) || mlx_is_key_down(g->mlx, MLX_KEY_DOWN))
    {
        double nx = g->player.x - sin(g->player.angle) * g->player.speed;
        double ny = g->player.y + cos(g->player.angle) * g->player.speed;
        g->player.x = (int)nx;
        g->player.y = (int)ny;
        redraw = true;
    }

    // Strafe left/right
    if (mlx_is_key_down(g->mlx, MLX_KEY_A))
    {
        double nx = g->player.x - cos(g->player.angle) * g->player.speed;
        double ny = g->player.y - sin(g->player.angle) * g->player.speed;
        g->player.x = (int)nx;
        g->player.y = (int)ny;
        redraw = true;
    }
    if (mlx_is_key_down(g->mlx, MLX_KEY_D))
    {
        double nx = g->player.x + cos(g->player.angle) * g->player.speed;
        double ny = g->player.y + sin(g->player.angle) * g->player.speed;
        g->player.x = (int)nx;
        g->player.y = (int)ny;
        redraw = true;
    }

    // Rotate
    if (mlx_is_key_down(g->mlx, MLX_KEY_LEFT))
    {
        g->player.angle -= 0.05;
        redraw = true;
    }
    if (mlx_is_key_down(g->mlx, MLX_KEY_RIGHT))
    {
        g->player.angle += 0.05;
        redraw = true;
    }

    if (redraw)
    {
        render_frame(g);
        draw_minimap(g);
    }
}
