/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdean <hdean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 21:49:42 by hdean             #+#    #+#             */
/*   Updated: 2019/12/22 20:52:42 by hdean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft.h"
# include "mlx.h"
# include <math.h>

/*
** SCREEN SIZE BY DEFAULT
*/
# define WIDTH 1500
# define HEIGHT 1000

/*
** KEYS FOR HOOKS
*/
# define ESC 53
# define PLUS_N 69
# define PLUS 24
# define MINUS 27
# define MINUS_N 78
# define LEFT 123
# define RIGHT 124
# define UP 125
# define DOWN 126
# define SPACE 49
# define R_X_PN 91
# define R_X_NN 89
# define R_Y_PN 87
# define R_Y_NN 86
# define R_Z_PN 84
# define R_Z_NN 83
# define ISO 34
# define CENTER 8
# define FIT 9
# define PARALLEL 31
# define ZOY 33
# define ZOX 35
# define VALUE 6
# define MOUSE_LEFT 1
# define MOUSE_RIGHT 2
# define MOUSE_UP 5
# define MOUSE_DOWN 4
# define COLOR_A 12
# define COLOR_B 13
# define RESET_COLOR 14

/*
**COLORS
*/
# define AWHITE 0xFFFFFF
# define ABLUE 0x1E90FF
# define BLIME 0x00FF00
# define BPINK 0xFF1493
# define CRED 0xFF4500
# define CSEA 0x20B2AA
# define DBLUE 0x73E5F1
# define DYELLOW 0xFEE08B
# define DGREEN	0x12792D
# define DBROWN 0x8A2D1A
# define DSEA 0x0334EC
# define TYELLOW 0xC8A215

/*
** DATA STRUCTURES
*/
typedef	struct	s_dbl_param
{
	double				x;
	double				y;
	double				z;
}				t_dbl_param;

typedef struct	s_dbl_point
{
	double				x;
	double				y;
	double				z;
	int					color;
	struct s_dbl_point	*next;
}				t_dbl_point;

typedef struct	s_int_coord
{
	int					x;
	int					y;
	int					z;
}				t_int_coord;

typedef	struct	s_point
{
	int					x;
	int					y;
	int					z;
	int					color;
	struct s_point		*next;
}				t_point;

typedef	struct	s_color
{
	int					r;
	int					g;
	int					b;
}				t_color;

typedef	struct	s_image
{
	int					height;
	int					width;
	char				*name;
	t_point				*points;
	t_int_coord			max_xyz;
	double				max_scale;
}				t_image;

typedef	struct	s_mouse
{
	int					press;
	int					old_x;
	int					old_y;
}				t_mouse;

typedef	struct	s_mlx
{
	t_image				*pic;
	void				*mlx_ptr;
	void				*win_ptr;
	void				*img_ptr;
	char				*data;
	int					line_size;
	int					bits_per_pixel;
	int					endian;
	t_int_coord			center;
	t_dbl_point			*dots;
	t_dbl_point			*copy_dots;
	double				scale;
	t_dbl_param			angle;
	double				**z_buffer;
	t_mouse				mouse;
	int					color_scheme;
	int					values_to_win;
}				t_mlx;

/*
** READ
*/
int				read_and_valid(t_image *pic);
int				parse_point(t_point **list, char *buf, t_point dot);
t_dbl_point		*convert_point_values(t_point *points);

/*
** TRANSFORM COORDINATES' FUNCTIONS
*/
void			set_setups_for_transform_params(t_mlx *fdf);
void			transform_coord(t_mlx *fdf);
void			coordinate_rotation(t_dbl_point **dots,
													double **rotation_matrix);
void			scale_image_to_current_screen(t_mlx *fdf);
void			scale_coord(t_dbl_point **dots, double scale);
void			back_to_local_coord(t_mlx *fdf);

/*
** COMPUTING
*/
double			**count_rotation_matrix(t_dbl_param angle);
t_dbl_param		max_dbl_dot(t_dbl_point *dots);
t_dbl_param		min_dbl_dot(t_dbl_point *dots);
t_dbl_param		count_overall_sizes(t_dbl_point *dots);

/*
** MATRIX
*/
double			**new_zero_matrix(int row, int col);
double			**rotation_x(double x_angle);
double			**rotation_y(double y_angle);
double			**rotation_z(double z_angle);
double			**free_matrix(double **matrix, int size);

/*
** DRAW
*/
void			draw_fdf(t_image *pic);
int				draw_line(t_dbl_point *first_point, t_dbl_point *second_point,
																t_mlx *fdf);
int				grad_color(t_int_coord delta, t_point end,
										t_point *current_point, int col);
t_color			get_rgb_color(int color);
void			count_new_color(int *color, double d, t_color start,
																t_color end);
void			clear_image(t_mlx *fdf);
int				draw_vectors(t_mlx *fdf);
int				redraw_vectors(t_mlx *fdf);

/*
** SOME USEFULL FUNCTIONS
*/
int				hex_symb(int c);
double			grad_to_rad(double angle);
char			*ft_itoa_double(double old_n);

/*
** "FREE" FUNCTIONS
*/
void			delete_image_pic(t_image *pic);
void			delete_fdf(t_mlx **fdf);
void			free_dots(t_dbl_point **list);

/*
** HOOKS UTILITES
*/
void			scale(t_mlx *fdf, int key);
void			move(t_mlx *fdf, int key);
void			center(t_mlx *fdf, int key);
void			rotate(t_mlx *fdf, int key);
void			projections(t_mlx *fdf, int key);
void			color_scheme(t_mlx *fdf, int key);
void			terra_color_scheme(t_mlx *fdf);
void			restart(t_mlx *fdf);
int				mouse_press(int button, int x, int y, void *param);
int				mouse_move(int x, int y, void *param);
int				mouse_release(int button, int x, int y, void *param);
int				key_press(int key, void *param);
int				close_hook(void *param);
int				value_to_window(t_mlx *fdf);
void			terra_color_scheme(t_mlx *fdf);

/*
** MENU
*/
void			put_menu(t_mlx *fdf);
void			put_params_menu_to_window(t_mlx *fdf);

#endif
