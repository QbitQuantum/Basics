bool PhotoPreview::on_draw(const Cairo::RefPtr<Cairo::Context>& cr) {
	if (!Image)
		return false;

	int Width,Height;
	Gtk::Allocation Allocation = get_allocation();
	Width=Allocation.get_width();
	Height=Allocation.get_height();

	if (Width<=1 || Height<=1)
		return false;

	/* Scale the photo */
	Glib::RefPtr<Gdk::Pixbuf> Scaled;

	/* Preserve aspect ratio */
	double ImageAspectRatio,PreviewAspectRatio;
	PreviewAspectRatio=(float)Width/Height;
	ImageAspectRatio=(float)Image->get_width()/Image->get_height();
	if (ImageAspectRatio<PreviewAspectRatio) {
		Width=Height*ImageAspectRatio;
	} else {
		Height=Width/ImageAspectRatio;
	}

	Scaled=Image->scale_simple(
		Width,
		Height,
		Gdk::INTERP_BILINEAR);

	if (Cfg->GetFlipPreview())
		Scaled=Scaled->flip();

	Gdk::Cairo::set_source_pixbuf(cr, Scaled,
		(Allocation.get_width()/2)-(Scaled->get_width()/2),
		(Allocation.get_height()/2)-(Scaled->get_height()/2)
		);
	cr->paint();

	double TimeLeft=Util::TimeDiff(&PhotoTime,NULL);
	double MinDim=get_width();
	if (get_height()<MinDim)
		MinDim=get_height();

	if (Overlay.length()==0 && TimeLeft>0) {
		double TotalTime=Cfg->GetCountdownCount()*(Cfg->GetCountdownTimeout()/1000.0);
		unsigned int Whole=floor(Cfg->GetCountdownCount()*TimeLeft/TotalTime);
		float Frac=(Cfg->GetCountdownCount()*TimeLeft/TotalTime)-Whole;

		Cairo::RefPtr<Cairo::Context> Context = get_window()->create_cairo_context();

		Context->set_source_rgba(1.0, 1.0, 1.0,0.5);
		Context->translate(get_width()/2.0,get_height()/2.0);

		/* Draw the fractional portion of the countdown */
		Context->save();
		Context->rotate(M_PI/2.0);
		Context->arc(0.0,0.0,MinDim/4.0,0,Frac*2*M_PI);
		Context->fill();
		Context->restore();

		/* Draw the Whole portion of the countdown */
		Context->save();
		Context->set_font_size(MinDim/2.0);
		char StrBuf[1024];
		snprintf(StrBuf,sizeof(StrBuf),"%d",Whole+1);
		Cairo::TextExtents Extents;
		Context->get_text_extents(StrBuf,Extents);
		Context->translate(-Extents.width/2.0,Extents.height/2.0);

		Context->show_text(StrBuf);
		Context->stroke();
		Context->restore();
	}

	if (Overlay.length()) {
		Cairo::RefPtr<Cairo::Context> Context = get_window()->create_cairo_context();
		Context->set_source_rgba(1.0, 1.0, 1.0,0.5);
		Context->translate(get_width()/2.0,get_height()/2.0);

		Context->save();
		Context->set_font_size(MinDim/2.0);
		Cairo::TextExtents Extents;
		Context->get_text_extents(Overlay,Extents);
		Context->translate(-Extents.width/2.0,Extents.height/2.0);

		Context->show_text(Overlay);
		Context->stroke();
		Context->restore();
	}

	return true;
}