							 //const Cairo::RefPtr<Cairo::Context>& cr
		virtual bool on_draw(const Cairo::RefPtr<Cairo::Context> &cr) {
			Gtk::Allocation alloc = get_allocation();
			int ancho = alloc.get_width();
			int alto = alloc.get_height();
			int x = ancho / 2;
			int y = alto / 2;
			
			int w = 3 * ancho / 4.0;
			int h = alto / 2.0;
			cr->save();
			
			cr->translate(x, y);
			cr->scale(w, h);
			cr->arc(0, 0, 1.0, 0, 2 * M_PI);
			cr->set_source_rgba(0, 0, 1.0, 0);
			// cr->fill_preserve();
			cr->restore();  // back to opaque black
			cr->stroke();
			return true;
		}