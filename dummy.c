#include "maingpt.c"

void raycastTextured(Game *game)
{
    clearimg(game);
    double angle_step = FOV / WIDTH; 
    double angle = game->player.dir - FOV / 2;
    for (int x = 0; x < WIDTH; x++, angle += angle_step)
    {
        double dirX = cos(angle);
        double dirY = sin(angle);
        
        int mapX = (int)game->player.x;
        int mapY = (int)game->player.y;

        // ... The rest of your DDA algorithm until hit detection ... 

        if (hit)
        {
            // Calculate distance of perpendicular ray (Euclidean distance will give fisheye effect!)
            if (side == 0)
                perpWallDist = (mapX - game->player.x + (1 - stepX) / 2) / dirX;
            else
                perpWallDist = (mapY - game->player.y + (1 - stepY) / 2) / dirY;

            perpWallDist *= cos(game->player.dir - angle);

            // Calculate height of line to draw on screen
            int lineHeight = (int)(HEIGHT / perpWallDist);

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
            for (int y = drawStart; y < drawEnd; y++)
            {
                int d = y * 256 - HEIGHT * 128 + lineHeight * 128;  // 256 and 128 factors to avoid floats
                int texY = ((d * texture->height) / lineHeight) / 256;
                int color = ((int *)(texture->addr))[texY * texture->width + texX];

                my_mlx_pixel_put(&game->img, x, y, color);
            }

            // The rest of your function remains unchanged ...
        }
    }
}
