void Image_controls::set_thumbnail(const Image_buffer<rendering::Color4>& source, uint32_t channel, bool inverted, float modulate_factor)
{
	Image_buffer<rendering::Color4>& scratch_buffer = thumbnail_provider_->scratch_buffer();

	Channel_to_grayscale<rendering::Color4> to_grayscale(channel);
	to_grayscale.filter(scratch_buffer, source);

	if (inverted)
	{
		Invert<rendering::Color4> invert;
		invert.filter(scratch_buffer, scratch_buffer);
	}

	if (1.f != modulate_factor)
	{
		Modulate modulate(modulate_factor);
		modulate.filter(scratch_buffer, scratch_buffer);
	}

	const uint2& source_dimensions = source.dimensions();
	const uint2& thumbnail_dimensions = thumbnail_.dimensions();

	if (source_dimensions.x < thumbnail_dimensions.x || source_dimensions.y < thumbnail_dimensions.y)
	{
		Copy<rendering::Color4c> copy;
		copy.filter(thumbnail_, thumbnail_provider_->checkerboard());
	}

	// No need to swap channels for Qt here, as it is grayscale
	To_BGRA filter(false);
	filter.filter(thumbnail_, scratch_buffer, source.dimensions());

	QImage qimage(reinterpret_cast<const uchar*>(thumbnail_.data()),
				  thumbnail_dimensions.x, thumbnail_dimensions.y, QImage::Format_RGB32);

	QPixmap pixmap = QPixmap::fromImage(qimage);

	ui->image_label_->setPixmap(pixmap);
}