/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaraden <mkaraden@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 14:13:00 by mkaraden          #+#    #+#             */
/*   Updated: 2023/10/22 02:32:16 by mkaraden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libs.h"

//-------------MAIN-----------------------//
//main
int				ft_loop(t_game *game);

//init
void			init_stuff(t_game *game);
void			init_win(t_game *game);
void			init_textures(t_game *game, t_data *data);
void			set_dir(t_game *game, int dir);
void			load_texture(t_game *game, int index, char *path);

//hook
int				key_hook(int key, t_game *game);
int				ft_press(int key, t_game *game);
int				ft_release(int key, t_game *game);
void			ft_move(t_player player, int dir, t_game *game);
void			ft_move_fr(t_player *player, int dir, t_game *game); //*
int				is_collide(double new_x, double new_y,
					t_player *player, char **map);
void			ft_turn(t_player *player, int dir);
void			routine(t_game *game);

//debug
void			print_stats(t_game *game);
char			*dtoa(double value);

//unitls 				//-ozi
void			ft_error(int err, void *ptr);	//-ozi
void			data_error(int err, t_game *game);

void			cross_handler(t_game *game);

//-------------RAYCAST--------------------//

void			raycast(t_game *game);
void			ray_step(t_ray *ray);

//calculate
void			calculate_step_and_dist(t_game *game, t_ray *ray);
void			calculate_perpetual(t_game *game, t_ray *ray, double angle);
void			determine_texture(t_game *game, t_ray *ray, double angle);
void			calculate_texture_x(t_game *game, t_ray *ray, double angle);
void			fix_mirror(t_ray *ray);

//draw
void			draw_textured_line(t_game *game, t_ray *ray,
					int x, int lineHeight);
void			draw_floor_ceiling(t_game *game, int x, int lineHeight);
void			draw_floor_ceiling_textured(t_game *game, t_ray *ray,
					int x, int lineHeight);
void			clearimg(t_game *game);
void			my_mlx_pixel_put(t_txt_data *data, int x, int y, int color);
int				get_tex_y(int y, t_ray *ray, int line_height);
unsigned int	get_pixel_color(int tex_y, t_ray *ray);

//utils
void			init_ray(t_game *game, t_ray *ray, double angle);
int				is_boundary_violated(t_ray *ray, int map_size);
int				is_hit(t_ray *ray, t_game *game);
int				safe_divide(int numerator, double denominator);

void			ft_error(int err, void *ptr);

//minimap
void			draw_minimap(t_game *game);
void			draw_tile(t_game *game, int i, int j);

//-------------PARSE-----------------------// //oguzhan

void			parse_cub(t_game *game, int ac, char **av);
int				is_mapline(char *line);
char			*ft_strrchr(char *str, char ch);
char			*ft_substr(t_game *game, char *str, int len);
int				ft_strcmp(char *s1, char *s2);
void			get_elements(t_game *game, int i);
void			lexer(t_game *game);
char			**ft_split(char *str, char sep, t_game *game);
void			check_map(t_game *gmae);
int				char_counter(char **map, char ch);
void			trim_nl(t_game *game);
void			square_map(t_game *game);
void			format_map(t_game *game);
void			get_map_val(t_game *game);
void			get_player(t_game *game);
char			get_top(char **map, int column);
char			get_bottom(char **map, int column);
char			get_left(char	*line);
char			get_right(char *line);
void			check_inside(t_game *game);
void			re_format_map(t_game *game);
//DEBUG
void			debug_data(t_data *data);

#endif
