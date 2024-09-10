void EmblemCellRenderer::do_render(const Cairo::RefPtr<Cairo::Context>& context, int widget, int background_area, Gdk::Rectangle &cell_area, int flags) {
    context->translate(cell_area.get_x(), cell_area.get_y());
    context->rectangle(0, 0, cell_area.get_width(), cell_area.get_height());
    context->clip();

    // TODO: Incorporate padding
    context->push_group();
    if (!this->_icon_name.empty()) {
        Glib::RefPtr<Gdk::Pixbuf> pixbuf = this->_get_pixbuf(this->_icon_name, this->_icon_size);
        context->set_operator(Cairo::OPERATOR_SOURCE);
        // Assumes square icons; may break if we don't get the requested size
        int height_offset = int((cell_area.get_height() - pixbuf->get_height())/2);
        Gdk::Cairo::set_source_pixbuf(context, pixbuf, 0, height_offset);
        context->rectangle(0, height_offset,
                          pixbuf->get_width(), pixbuf->get_height());
        context->fill();

        if (this->_tint_color) {
            Gdk::RGBA* c = this->_tint_color;
            gushort r = c->get_red();
            gushort g = c->get_green();
            gushort b = c->get_blue();
            // Figure out the difference between our tint colour and an
            // empirically determined (i.e., guessed) satisfying luma and
            // adjust the base colours accordingly
            double luma = (r + r + b + g + g + g) / 6.;
            double extra_luma = (1.2 - luma) / 3.;
            r = std::min(r + extra_luma, 1.);
            g = std::min(g + extra_luma, 1.);
            b = std::min(b + extra_luma, 1.);
            context->set_source_rgba(r, g, b, 0.4);
            context->set_operator(Cairo::OPERATOR_ATOP);
            context->paint();
        }

        if (!this->_emblem_name.empty()) {
            Glib::RefPtr<Gdk::Pixbuf> pixbuf = this->_get_pixbuf(this->_emblem_name, this->_emblem_size);
            int x_offset = this->_icon_size - this->_emblem_size;
            context->set_operator(Cairo::OPERATOR_OVER);
            Gdk::Cairo::set_source_pixbuf(context, pixbuf, x_offset, 0);
            context->rectangle(x_offset, 0,
                              cell_area.get_width(), this->_emblem_size);
            context->fill();
        }
    }

    context->pop_group_to_source();
    context->set_operator(Cairo::OPERATOR_OVER);
    context->paint();
}