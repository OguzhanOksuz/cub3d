#include "maingpt.c"

void raycast(Game *game)
{
    ...
    for (int x = 0; x < WIDTH; x++, angle += angle_step)
    {
        ...
        while (hit == 0)
        {
            ...
            else if (map[mapY][mapX] > 0) 
            {
                hit = 1;
            }
        }
        
        double wallX;
        if (side == 0) 
            wallX = game->player.y + perpWallDist * dirY;
        else
            wallX = game->player.x + perpWallDist * dirX;
        wallX -= floor(wallX);
        
        if (hit)
        {
            ...
            int texX = (int)(wallX * (double)(texture->width));
            if(side == 0 && dirX > 0) texX = texture->width - texX - 1;
            if(side == 1 && dirY < 0) texX = texture->width - texX - 1;

            ...
            for (int y = drawStart; y < drawEnd; y++)
            {
                int d = y * 256 - HEIGHT * 128 + lineHeight * 128;
                int texY = ((d * texture->height) / lineHeight) / 256;
                int color = ((int *)(texture->addr))[texY * texture->line_length / 4 + texX];
                my_mlx_pixel_put(&game->img, x, y, color);
            }
            ...
        }
    }
}


// Assuming the hit wall cell is (mapX, mapY)...
double wallX;
if (side == 0) // If a wall was hit on the east or west
    wallX = game->player.y + perpWallDist * dirY;
else            // If a wall was hit on the north or south
    wallX = game->player.x + perpWallDist * dirX;

wallX -= floor(wallX);


// Calculate value of texX
int texX = (int)(wallX * (double)(texture->width));
if (side == 0 && dirX > 0)
    texX = texture->width - texX - 1;
if (side == 1 && dirY < 0)
    texX = texture->width - texX - 1;


	void raycast(Game *game)
{
    clearimg(game);
    double angle_step = FOV / WIDTH; // ray count
    double angle = game->player.dir - FOV / 2;
    for (int x = 0; x < WIDTH; x++, angle += angle_step)
    {
        double dirX = cos(angle);
        double dirY = sin(angle);
        
        int mapX = (int)game->player.x;
        int mapY = (int)game->player.y;

        double sideDistX;
        double sideDistY;

        double deltaDistX = fabs(1 / dirX);
        double deltaDistY = fabs(1 / dirY);
        double perpWallDist;

        int stepX;
        int stepY;

        int hit = 0;
        int side;

        if (dirX < 0)
        {
            stepX = -1;
            sideDistX = (game->player.x - mapX) * deltaDistX;
        }
        else
        {
            stepX = 1;
            sideDistX = (mapX + 1.0 - game->player.x) * deltaDistX;
        }

        if (dirY < 0)
        {
            stepY = -1;
            sideDistY = (game->player.y - mapY) * deltaDistY;
        }
        else
        {
            stepY = 1;
            sideDistY = (mapY + 1.0 - game->player.y) * deltaDistY;
        }

        while (hit == 0)
        {
            if (sideDistX < sideDistY)
            {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            }
            else
            {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }

            // add boundary checks here
            if (mapX < 0 || mapX >= MAP_SIZE || mapY < 0 || mapY >= MAP_SIZE) 
            {
                hit = 1;
            }
            else if (map[mapY][mapX] > 0) 
            {
                hit = 1;

				
            }
        }
		int lineHeight = 0;

		double wallX;
        if (side == 0) 
            wallX = game->player.y + perpWallDist * dirY;
        else
            wallX = game->player.x + perpWallDist * dirX;
        wallX -= floor(wallX);
		
        if (hit)
        {
            // Calculate distance of perpendicular ray (Euclidean distance will give fisheye effect!)
            if (side == 0)
                perpWallDist = (mapX - game->player.x + (1 - stepX) / 2) / dirX;
            else
                perpWallDist = (mapY - game->player.y + (1 - stepY) / 2) / dirY;

            perpWallDist *= cos(game->player.dir - angle);

            // Calculate height of line to draw on screen
            lineHeight = (int)(HEIGHT / perpWallDist);

            // Calculate lowest and highest pixel to fill in current stripe
            int drawStart = -lineHeight / 2 + HEIGHT / 2;
            int drawEnd = lineHeight / 2 + HEIGHT / 2;

            // Texture rendering
            txt_data *texture;
            int texX;
            if (side == 0)
                texture = dirX > 0 ? &game->textures[2] : &game->textures[3]; // Choose east or west texture.
            else
                texture = dirY > 0 ? &game->textures[0] : &game->textures[1]; // Choose north or south texture.

            if (side == 0) texX = (int)(game->player.y + perpWallDist * dirY) % texture->width;
            else            texX = (int)(game->player.x + perpWallDist * dirX) % texture->width;

            // Loop through every pixel of the stripe/screen column

			texX = (int)(wallX * (double)(texture->width));
            if(side == 0 && dirX > 0) texX = texture->width - texX - 1;
            if(side == 1 && dirY < 0) texX = texture->width - texX - 1;
            for (int y = drawStart; y < drawEnd; y++)
            {
                int d = y * 256 - HEIGHT * 128 + lineHeight * 128;
                int texY = ((d * texture->height) / lineHeight) / 256;
                int color = ((int *)(texture->addr))[texY * texture->line_length / 4 + texX];
                my_mlx_pixel_put(&game->img, x, y, color);
            }

            // The rest of your function remains unchanged ...
        }

		//FLOOR CEILING
			
        // Determine the start and end of the wall in this column.
        int start = (HEIGHT - lineHeight) / 2;
        int end = (HEIGHT + lineHeight) / 2;

        // Draw the ceiling from 0 to the start of the wall.
        for (int y = 0; y < start; y++)
            my_mlx_pixel_put(&game->img, x, y, 0x00AAAAFF); // Blueish color for the ceiling.

        // Draw the wall.
        //draw_line(game, x, lineHeight, 0x00FF0000);

        // Draw the floor from the end of the wall to the bottom of the screen.
        for (int y = end; y < HEIGHT; y++)
            my_mlx_pixel_put(&game->img, x, y, 0x00660000); // Brownish color for the floor.
    }
}


void raycast(Game *game)
{
    // Clear the screen before drawing new frame
    clearimg(game);

    // Calculate the angle step for each ray based on the field of view (FOV) and screen width
    double angle_step = FOV / WIDTH;

    // Start angle is the player's current direction minus half the FOV
    double angle = game->player.dir - FOV / 2;

    // Iterate over all the screen columns to calculate and draw rays
    for (int x = 0; x < WIDTH; x++, angle += angle_step)
    {
        // Calculate the direction of the ray
        double dirX = cos(angle);
        double dirY = sin(angle);
        
        // Calculate the map square the player is in
        int mapX = (int)game->player.x;
        int mapY = (int)game->player.y;

        double sideDistX;
        double sideDistY;

        // Calculate the length of the ray from one side to the next in the x and y direction
        double deltaDistX = fabs(1 / dirX);
        double deltaDistY = fabs(1 / dirY);
        double perpWallDist;

        int stepX;
        int stepY;

        // Did the ray hit a wall?
        int hit = 0;

        // Was it a horizontal or vertical wall?
        int side;

        // Calculate step direction and initial distance to side boundary
        if (dirX < 0)
        {
            stepX = -1;
            sideDistX = (game->player.x - mapX) * deltaDistX;
        }
        else
        {
            stepX = 1;
            sideDistX = (mapX + 1.0 - game->player.x) * deltaDistX;
        }

        if (dirY < 0)
        {
            stepY = -1;
            sideDistY = (game->player.y - mapY) * deltaDistY;
        }
        else
        {
            stepY = 1;
            sideDistY = (mapY + 1.0 - game->player.y) * deltaDistY;
        }

        // Loop to find where the ray hits a wall
        while (hit == 0)
        {
            // Jump to next map square in the x or y direction
            if (sideDistX < sideDistY)
            {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            }
            else
            {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }

            // Check if ray has hit a wall or gone out of map bounds
            if (mapX < 0 || mapX >= MAP_SIZE || mapY < 0 || mapY >= MAP_SIZE) 
            {
                hit = 1;
            }
            else if (map[mapY][mapX] > 0) 
            {
                hit = 1;
            }
        }

        // Calculate distance to wall
        if (hit && side == 0)
            perpWallDist = (mapX - game->player.x + (1 - stepX) / 2) / dirX;
        else if (hit)
            perpWallDist = (mapY - game->player.y + (1 - stepY) / 2) / dirY;
        else
            perpWallDist = HEIGHT;

        // Correct the fishbowl effect by multiplying the wall distance by cos(player_dir - ray_dir)
        perpWallDist *= cos(game->player.dir - angle);

        // Choose color based on the wall direction
        int color;
        if (side == 0) // East or west wall.
            color = dirX > 0 ? 0x00FF0000 : 0x0000FF00; // Red for east, green for west.
        else // North or south wall.
            color = dirY > 0 ? 0x000000FF : 0x00FFFF00; // Blue for north, yellow for south.

        // Calculate the height of the wall on the screen based on the distance
        int lineHeight = (int)(HEIGHT / perpWallDist);

        // Draw the wall column
        draw_line(game, x, lineHeight, color);

        // Determine the start and end of the wall in this column
        int start = (HEIGHT - lineHeight) / 2;
        int end = (HEIGHT + lineHeight) / 2;

        // Draw the ceiling from 0 to the start of the wall
        for (int y = 0; y < start; y++)
            my_mlx_pixel_put(&game->img, x, y, 0x00AAAAFF); // Blueish color for the ceiling.

        // Draw the floor from the end of the wall to the bottom of the screen
        for (int y = end; y < HEIGHT; y++)
            my_mlx_pixel_put(&game->img, x, y, 0x00660000); // Brownish color for the floor.
    }
}

            // How much to increase the texture coordinate per screen pixel
      double step = 1.0 * texHeight / lineHeight;
      // Starting texture coordinate
      double texPos = (drawStart - h / 2 + lineHeight / 2) * step;
      for(int y = drawStart; y<drawEnd; y++)
      {
        // Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
        int texY = (int)texPos & (texHeight - 1);
        texPos += step;
        Uint32 color = texture[texNum][texHeight * texY + texX];
        //make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
        if(side == 1) color = (color >> 1) & 8355711;
        buffer[y][x] = color;
      }

/texturing calculations
      int texNum = worldMap[mapX][mapY] - 1; //1 subtracted from it so that texture 0 can be used!

      //calculate value of wallX
      double wallX; //where exactly the wall was hit
      if (side == 0) wallX = posY + perpWallDist * rayDirY;
      else           wallX = posX + perpWallDist * rayDirX;
      wallX -= floor((wallX));

      //x coordinate on the texture
      int texX = int(wallX * double(texWidth));
      if(side == 0 && rayDirX > 0) texX = texWidth - texX - 1;
      if(side == 1 && rayDirY < 0) texX = texWidth - texX - 1; 



// This function takes in a pointer to the Game state, a pointer to a ray, and an angle
void calculate_perpetual_and_color(Game *game, t_ray *ray, double angle) 
{
    // If the ray hits a wall and the side of the hit is 0 (meaning the wall is facing a certain direction, possibly East-West)
    if (ray->hit && ray->side == 0)
    {
        // Calculate the perpendicular distance to the wall hit by the ray
        // This formula takes into account the ray's direction and the player's position
        ray->perp_wall_dist = (ray->map_x - game->player.x + (1 - ray->step_x) / 2) / ray->ray_dir.x;

        // Determine the x coordinate of the texture based on player's position and the ray direction
        ray->tex_x = (int)(game->player.y + ray->perp_wall_dist * ray->ray_dir.y) % game->textures[ray->map_x % 4].width;
    }
    // If the ray hits a wall (regardless of the side hit)
    else if (ray->hit)
    {
        // Calculate the perpendicular distance to the wall hit by the ray
        ray->perp_wall_dist = (ray->map_y - game->player.y + (1 - ray->step_y) / 2) / ray->ray_dir.y;

        // Determine the x coordinate of the texture based on player's position and the ray direction
        ray->tex_x = (int)(game->player.x + ray->perp_wall_dist * ray->ray_dir.x) % game->textures[ray->map_y % 4].width;
    }
    // If the ray did not hit any wall, set the distance to be the HEIGHT constant
    else
        ray->perp_wall_dist = HEIGHT;

    // Correct for the "fishbowl effect". The distortion which makes straight walls look curved
    // This is because rays at the edge of the player's field of view have longer distance to the wall than those in the center
    // To correct this, multiply the distance by the cosine of the difference between the player's direction and the ray angle
    ray->perp_wall_dist *= cos(game->player.dir - angle);

    // Determine the texture to use for the wall hit by the ray
    // The actual texture depends on the side hit and the step directions of the ray
    ray->texture = &game->textures[(ray->side + ray->step_x + ray->step_y) % 4];
    
    // This line is commented out, but if it were active it would put the ray's texture to the game window at position (0, 64)
    // mlx_put_image_to_window(game->mlx, game->win, ray->texture->img, 0, 64);
}


	  