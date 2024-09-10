static void gl_raster_font_render_message(
      gl_raster_t *font, const char *msg, GLfloat scale,
      const GLfloat color[4], GLfloat pos_x, GLfloat pos_y,
      unsigned text_align)
{
   int x, y, delta_x, delta_y;
   float inv_tex_size_x, inv_tex_size_y, inv_win_width, inv_win_height;
   unsigned i, msg_len_full, msg_len;
   GLfloat font_tex_coords[2 * 6 * MAX_MSG_LEN_CHUNK];
   GLfloat font_vertex[2 * 6 * MAX_MSG_LEN_CHUNK]; 
   GLfloat font_color[4 * 6 * MAX_MSG_LEN_CHUNK];
   struct gl_coords coords;
   gl_t *gl       = font ? font->gl : NULL;

   if (!gl)
      return;

   msg_len_full   = strlen(msg);
   msg_len        = min(msg_len_full, MAX_MSG_LEN_CHUNK);

   x              = roundf(pos_x * gl->vp.width);
   y              = roundf(pos_y * gl->vp.height);
   delta_x        = 0;
   delta_y        = 0;

   switch (text_align)
   {
      case TEXT_ALIGN_RIGHT:
         x -= get_message_width(font, msg);
         break;
      case TEXT_ALIGN_CENTER:
         x -= get_message_width(font, msg) / 2.0;
         break;
   }

   inv_tex_size_x = 1.0f / font->tex_width;
   inv_tex_size_y = 1.0f / font->tex_height;
   inv_win_width  = 1.0f / font->gl->vp.width;
   inv_win_height = 1.0f / font->gl->vp.height;

   while (msg_len_full)
   {
      for (i = 0; i < msg_len; i++)
      {
         int off_x, off_y, tex_x, tex_y, width, height;
         const struct font_glyph *glyph =
            font->font_driver->get_glyph(font->font_data, (uint8_t)msg[i]);

         if (!glyph) /* Do something smarter here ... */
            glyph = font->font_driver->get_glyph(font->font_data, '?');
         if (!glyph)
            continue;

         off_x  = glyph->draw_offset_x;
         off_y  = glyph->draw_offset_y;
         tex_x  = glyph->atlas_offset_x;
         tex_y  = glyph->atlas_offset_y;
         width  = glyph->width;
         height = glyph->height;

         gl_raster_font_emit(0, 0, 1); /* Bottom-left */
         gl_raster_font_emit(1, 1, 1); /* Bottom-right */
         gl_raster_font_emit(2, 0, 0); /* Top-left */

         gl_raster_font_emit(3, 1, 0); /* Top-right */
         gl_raster_font_emit(4, 0, 0); /* Top-left */
         gl_raster_font_emit(5, 1, 1); /* Bottom-right */

         delta_x += glyph->advance_x;
         delta_y -= glyph->advance_y;
      }

      coords.tex_coord     = font_tex_coords;
      coords.vertex        = font_vertex;
      coords.color         = font_color;
      coords.vertices      = 6 * msg_len;
      coords.lut_tex_coord = gl->coords.lut_tex_coord;

      if (font->block)
         gl_coord_array_add(&font->block->carr, &coords, coords.vertices);
      else
         gl_raster_font_draw_vertices(gl, &coords);

      msg_len_full -= msg_len;
      msg          += msg_len;
      msg_len       = min(msg_len_full, MAX_MSG_LEN_CHUNK);
   }
}