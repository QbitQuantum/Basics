static void wiiu_font_render_line(
      video_frame_info_t *video_info,
      wiiu_font_t* font, const char* msg, unsigned msg_len,
      float scale, const unsigned int color, float pos_x,
      float pos_y, unsigned text_align)
{
   unsigned i;
   wiiu_video_t* wiiu = (wiiu_video_t*)video_info->userdata;
   unsigned width   = video_info->width;
   unsigned height  = video_info->height;
   int x            = roundf(pos_x * width);
   int y            = roundf((1.0 - pos_y) * height);

   if(  !wiiu ||
         wiiu->vertex_cache.current + (msg_len * 4) > wiiu->vertex_cache.size)
      return;

   switch (text_align)
   {
      case TEXT_ALIGN_RIGHT:
         x -= wiiu_font_get_message_width(font, msg, msg_len, scale);
         break;

      case TEXT_ALIGN_CENTER:
         x -= wiiu_font_get_message_width(font, msg, msg_len, scale) / 2;
         break;
   }

   sprite_vertex_t* v = wiiu->vertex_cache.v + wiiu->vertex_cache.current;

   for (i = 0; i < msg_len; i++)
   {
      const char* msg_tmp            = &msg[i];
      unsigned code                  = utf8_walk(&msg_tmp);
      unsigned skip                  = msg_tmp - &msg[i];

      if (skip > 1)
         i += skip - 1;

      const struct font_glyph* glyph =
         font->font_driver->get_glyph(font->font_data, code);

      if (!glyph) /* Do something smarter here ... */
         glyph = font->font_driver->get_glyph(font->font_data, '?');

      if (!glyph)
         continue;

      v->pos.x = x + glyph->draw_offset_x * scale;
      v->pos.y = y + glyph->draw_offset_y * scale;
      v->pos.width = glyph->width * scale;
      v->pos.height = glyph->height * scale;

      v->coord.u = glyph->atlas_offset_x;
      v->coord.v = glyph->atlas_offset_y;
      v->coord.width = glyph->width;
      v->coord.height = glyph->height;

      v->color = color;

      v++;

      x += glyph->advance_x * scale;
      y += glyph->advance_y * scale;
   }

   int count = v - wiiu->vertex_cache.v - wiiu->vertex_cache.current;

   if (!count)
      return;


   GX2Invalidate(GX2_INVALIDATE_MODE_CPU_ATTRIBUTE_BUFFER, wiiu->vertex_cache.v + wiiu->vertex_cache.current, count * sizeof(wiiu->vertex_cache.v));

   if(font->atlas->dirty)
   {
      for (i = 0; (i < font->atlas->height) && (i < font->texture.surface.height); i++)
         memcpy(font->texture.surface.image + (i * font->texture.surface.pitch),
                font->atlas->buffer + (i * font->atlas->width), font->atlas->width);

      GX2Invalidate(GX2_INVALIDATE_MODE_CPU_TEXTURE, font->texture.surface.image,
                    font->texture.surface.imageSize);
      font->atlas->dirty = false;
   }


   GX2SetPixelTexture(&font->texture, sprite_shader.ps.samplerVars[0].location);
   GX2SetVertexUniformBlock(sprite_shader.vs.uniformBlocks[1].offset, sprite_shader.vs.uniformBlocks[1].size, font->ubo_tex);

   GX2DrawEx(GX2_PRIMITIVE_MODE_POINTS, count, wiiu->vertex_cache.current, 1);

   GX2SetVertexUniformBlock(sprite_shader.vs.uniformBlocks[1].offset, sprite_shader.vs.uniformBlocks[1].size, wiiu->ubo_tex);

   wiiu->vertex_cache.current = v - wiiu->vertex_cache.v;
}