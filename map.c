/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olopez-s <olopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 01:19:55 by olopez-s          #+#    #+#             */
/*   Updated: 2025/01/17 01:29:59 by olopez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./mlx/mlx.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <X11/X.h>
#include <X11/keysym.h>

typedef struct s_map
{
    int width;      // Map width
    int height;     // Map height
    int **tiles;    // 2D array for map tiles
} t_map;

typedef struct s_data
{
	void		*mlx_ptr; // MLX pointer
	void		*win_ptr; // MLX window pointer
	void		*textures[5]; // MLX image pointers (on the stack)
	t_map		*map;
}	t_data;

/*
typedef struct s_data
{
	void *mlx_ptr;
	void *win_ptr;
} t_data;
*/

int on_destroy(t_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	exit(0);
	return (0);
}

int on_keypress(int keysym, t_data *data)
{
	(void)data;
    if (keysym == XK_Escape) // Escape key
    {
        on_destroy(data);
    }
    printf("Pressed key: %d\n", keysym);
    return (0);
}

void draw_square(t_data *data, int x, int y, int size, int color)
{
    int i, j;
    char *pixel;
    int bpp, line_size, endian;

    // Create a new image
    void *img = mlx_new_image(data->mlx_ptr, size, size);

    // Get image data address
    pixel = mlx_get_data_addr(img, &bpp, &line_size, &endian);

    // Draw the square pixel by pixel
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            int pixel_offset = (i * line_size) + (j * (bpp / 8));
            *(int *)(pixel + pixel_offset) = color; // Set pixel color
        }
    }

    // Put the image onto the window
    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, img, x, y);

    // Destroy the image to free memory
    mlx_destroy_image(data->mlx_ptr, img);
}

int main(void)
{
	t_data data;

	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
		return (1);
	data.win_ptr = mlx_new_window(data.mlx_ptr, 600, 400, "hi :)");
	if (!data.win_ptr)
		return (free(data.mlx_ptr), 1);

	// Register key release hook
	mlx_hook(data.win_ptr, KeyRelease, KeyReleaseMask, &on_keypress, &data);

	// Register destroy hook
	mlx_hook(data.win_ptr, DestroyNotify, StructureNotifyMask, &on_destroy, &data);

	draw_square(&data, 100, 100, 50, 0xFF0000);
	
	// Loop over the MLX pointer
	mlx_loop(data.mlx_ptr);
	return (0);
}
/*
int main(void)
{
	void *mlx_ptr;
	void *win_ptr;

	mlx_ptr = mlx_init();
	if (!mlx_ptr)
		return (1);
	win_ptr = mlx_new_window(mlx_ptr, 600, 400, "hi :)");
	if (!win_ptr)
		return (free(mlx_ptr), 1);
    usleep(12345678985);
	mlx_destroy_window(mlx_ptr, win_ptr);
	mlx_destroy_display(mlx_ptr);
	free(mlx_ptr);
	return (0);
}
*/