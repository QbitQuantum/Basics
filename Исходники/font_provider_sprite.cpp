void FontProvider_Sprite::draw_text(Canvas &canvas, float xpos, float ypos, float scale_x, float scale_y, const std::string &text, const Colorf &color)
{
	float f_spacelen = spacelen;
	float ascent = font_metrics.get_ascent() * scale_x;

	// Scan the string
	UTF8_Reader reader(text.data(), text.length());
	while(!reader.is_end())
	{
		unsigned int glyph = reader.get_char();
		reader.next();

		Font_Sprite_Glyph *gptr = get_glyph(glyph);
		if (gptr)
		{
			spr_glyphs.set_frame(gptr->sprite_index);
			Size frame_size = spr_glyphs.get_frame_size(gptr->sprite_index);
			float dest_width = scale_x * frame_size.width;
			float dest_height = scale_y * frame_size.height;
			spr_glyphs.set_color(color);
			spr_glyphs.draw(canvas, Rectf(xpos, ypos - ascent, Sizef(dest_width, dest_height)));
			xpos += dest_width;
		}
		else
		{
			xpos += f_spacelen;
		}
	}
}