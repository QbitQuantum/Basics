	void renderLabels(Cairo::RefPtr<Cairo::Context> cr, std::vector<std::pair<string, FloatPoint> >& toPlace) {
		cr->save();
		cr->set_source_rgba(0.0, 0.0, 0.0, 0.5);
		Cairo::RefPtr<Cairo::ToyFontFace> font = Cairo::ToyFontFace::create(DEFAULT_FONT, Cairo::FONT_SLANT_NORMAL, Cairo::FONT_WEIGHT_NORMAL);
		cr->set_font_face(font);
		cr->set_font_size(120.0);
		cr->set_line_width(2.0);

		Cairo::TextExtents textSize;
		std::list<shared_ptr<Label> > labels;
		int i = 0;
		std::vector<shared_ptr<Style>> styles;
		for (auto& pair : toPlace)
		{
			string& text = pair.first;
			cr->get_text_extents(text, textSize);
			shared_ptr<Style> s = boost::make_shared<Style>();
			s->text = text;
			styles.push_back(s);
			FloatPoint center = pair.second + FloatPoint(textSize.width/2.0, textSize.height/2.0);
			FloatRect owner = FloatRect(center.x, center.y, center.x, center.y);
			FloatPoint origin = pair.second - FloatPoint(textSize.x_bearing, textSize.y_bearing);
			shared_ptr<Label> l = boost::make_shared<Label>(FloatRect(pair.second, textSize.width, textSize.height), owner, s->text, s.get(), origin);

			cr->rectangle(l->box.minX, l->box.minY, l->box.getWidth(), l->box.getHeight());
			cr->stroke();

			labels.push_back(l);
		}

		std::vector<shared_ptr<Label> > placed;
		placeLabels(labels, placed);

		for (auto& l: placed)
		{
			cr->set_source_rgba(0.0, 0.0, 0.0, 1.0);
			cr->move_to(l->box.minX, l->box.maxY);
			cr->show_text(l->style->text.str());
			cr->fill();

			cr->set_source_rgba(1.0, 0.0, 0.0, 0.5);
			cr->rectangle(l->box.minX, l->box.minY, l->box.getWidth(), l->box.getHeight());
			cr->fill();
		}

		cr->restore();
	}