	void Font_DrawFlat::draw_text(Canvas &canvas, const Pointf &position, const std::string &text, const Colorf &color, float line_spacing)
	{
		float offset_x = 0;
		float offset_y = 0;
		UTF8_Reader reader(text.data(), text.length());
		RenderBatchTriangle *batcher = canvas.impl->batcher.get_triangle_batcher();

		while (!reader.is_end())
		{
			unsigned int glyph = reader.get_char();
			reader.next();

			if (glyph == '\n')
			{
				offset_x = 0;
				offset_y += line_spacing;
				continue;
			}

			Font_TextureGlyph *gptr = glyph_cache->get_glyph(canvas, font_engine, glyph);
			if (gptr)
			{
				if (!gptr->texture.is_null())
				{
					float xp = offset_x + position.x + gptr->offset.x;
					float yp = offset_y + position.y + gptr->offset.y;

					Rectf dest_size(xp, yp, Sizef(gptr->geometry.get_size()));
					batcher->draw_image(canvas, gptr->geometry, dest_size, color, gptr->texture);
				}
				offset_x += gptr->metrics.advance.width;
				offset_y += gptr->metrics.advance.height;
			}
		}
	}