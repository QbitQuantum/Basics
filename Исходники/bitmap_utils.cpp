void BitmapUtilsT<PFsrc,PFdst>::CopyTransformBlit(uint8_t* dst_pixels, const uint8_t* src_pixels, int src_pitch,
												  int x0, int x1, int y, const Rect& src_rect, const Matrix& inv) {
	const int sx0 = src_rect.x;
	const int sy0 = src_rect.y;
	const int sx1 = src_rect.x + src_rect.width;
	const int sy1 = src_rect.y + src_rect.height;

	for (int x = x0; x < x1; x++) {
		double fx, fy;
		inv.Transform(x + 0.5, y + 0.5, fx, fy);
		int xi = (int) floor(fx);
		int yi = (int) floor(fy);
		if (xi < sx0 || xi >= sx1 || yi < sy0 || yi >= sy1)
			;
		else
			copy_pixel(dst_pixels, &src_pixels[yi * src_pitch + xi * pf_src.bytes]);
		dst_pixels += pf_dst.bytes;
	}
}