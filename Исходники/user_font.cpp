int main(int, char**) {
	Cairo::RefPtr<Cairo::ImageSurface> surface = Cairo::ImageSurface::create(
			Cairo::FORMAT_ARGB32, WIDTH, HEIGHT);
	Cairo::RefPtr<Cairo::Context> cr = Cairo::Context::create(surface);
	// fill background in white
	cr->set_source_rgb(1.0, 1.0, 1.0);
	cr->paint();

	// draw a little dot at the point where text will be drawn
	cr->arc(TEXT_ORIGIN_X, TEXT_ORIGIN_Y, FONT_SIZE / 4.0, 0, 2 * M_PI);
	cr->set_source_rgba(0.0, 1.0, 0.0, 0.5);
	cr->fill();

	// draw the text
	cr->move_to(TEXT_ORIGIN_X, TEXT_ORIGIN_Y);
	cr->set_source_rgb(0.8, 0.2, 0.2);
	Cairo::RefPtr<BoxFontFace> font = BoxFontFace::create();
	cr->set_font_face(font);
	cr->set_font_size(FONT_SIZE);
	cr->show_text("cairomm!");

	// Now show it with the toy text API to
	// demonstrate how the glyphs match up
	cr->move_to(TEXT_ORIGIN_X, TEXT_ORIGIN_Y);
	cr->set_source_rgba(0.2, 0.2, 0.2, 0.3);
	Cairo::RefPtr<Cairo::ToyFontFace> toy_font = Cairo::ToyFontFace::create(
			"Bitstream Charter", Cairo::FONT_SLANT_NORMAL,
			Cairo::FONT_WEIGHT_BOLD);
	cr->set_font_face(toy_font);
	cr->set_font_size(FONT_SIZE);
	cr->show_text("cairomm!");

	const char* filename = "user-font.png";
	try {
		surface->write_to_png(filename);
		std::cout << "Wrote Image " << filename << std::endl;
		return 0;
	} catch (const std::exception& e) {
		std::cout << "** Unable to write Image " << filename << std::endl;
		return 1;
	}
}