void	draw_textured_line(t_game *game, t_ray *ray, int x, int lineHeight)
{
    // Calculate the start and end points of the line on the screen
    int lineStart = (HEIGHT - lineHeight) / 2;
    int lineEnd = (HEIGHT + lineHeight) / 2;

    // Constants for the texture Y-coordinate calculation
    double textureHeight = (double)ray->texture->height;
    double halfScreenHeight = HEIGHT / 2.0;
    double halfLineHeight = lineHeight / 2.0;
    int textureByteSize = ray->texture->bits_per_pixel / 8;

    for (int y = lineStart; y < lineEnd; y++)
    {
       // Calculate the proportion of y within the lineHeight and scale it by textureHeight
        double d = (y - halfScreenHeight + halfLineHeight) * textureHeight / lineHeight;
        int texY = (int)d;
        
        // Ensure the texY is within the bounds of the texture
        if(texY < 0) texY = 0;
        if(texY >= textureHeight) texY = textureHeight - 1;

		int texY = get_tex_y(y, ray, lineHeight);

        // Calculate the memory offset for the desired pixel in the texture
        int textureOffset = texY * ray->texture->line_length + ray->tex_x * textureByteSize;
        
        // Extract the color from the texture using the offset
        unsigned int pixel_color = *(unsigned int *)(ray->texture->addr + textureOffset);
        
        // Draw the pixel on the screen at the given x,y position
        my_mlx_pixel_put(&game->img, x, y, pixel_color);
    }
}