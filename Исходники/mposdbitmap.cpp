bool MpOsdBitmap::copy(const sub_bitmaps *imgs, const QSize &renderSize) {
	if (imgs->num_parts <= 0 || imgs->format == SUBBITMAP_EMPTY || (m_id == imgs->bitmap_id && m_pos == imgs->bitmap_pos_id))
		return false;
	m_renderSize = renderSize;
	if (m_size < imgs->num_parts)
		_Expand(m_parts, m_size = imgs->num_parts);

//							    	   none      ass  rgba    indexed
	static const int corrections[] = { 0,        1,   1,      4 };
	static const Format fmts[]     = { NoFormat, Ass, RgbaPA, Rgba };
	static const int  shifts[]     = { 0,        0,   2,      2 };
	static const int max = OpenGLCompat::maximumTextureSize();

	const int c_stride = corrections[imgs->format];
	const int shift = shifts[imgs->format];
	m_format = fmts[imgs->format];
	m_id = imgs->bitmap_id;
	m_pos = imgs->bitmap_pos_id;
	m_parts.resize(imgs->num_parts);
	m_sheet = {0, 0};

	int offset = 0, lineHeight = 0;
	QPoint map{0, 0};
	for (int i=0; i<imgs->num_parts; ++i) {
		auto &img = imgs->parts[i];
		auto &part = m_parts[i];
		part.m_size = {img.w, img.h};
		part.m_display = {img.x, img.y, img.dw, img.dh};
		if (imgs->format == SUBBITMAP_LIBASS) {
			const quint32 color = img.libass.color;
			part.m_color = (color & 0xffffff00) | (0xff - (color & 0xff));
		}
		part.m_stride = _Aligned<4>(img.stride*c_stride);
		part.m_strideAsPixel = (part.m_stride >> shift);
		part.m_offset = offset;
		offset += part.m_stride*part.height();

		if (part.strideAsPixel() > m_maximumSize.width())
			m_maximumSize.rwidth() = part.strideAsPixel();
		if (part.size().height() > m_maximumSize.height())
			m_maximumSize.rheight() = part.size().height();
		if (map.x() + part.strideAsPixel() > max) {
			map.rx() = 0; map.ry() += lineHeight;
			lineHeight = 0;
		}
		part.m_map = map;
		if (part.size().height() > lineHeight)
			lineHeight = part.size().height();
		map.rx() += part.strideAsPixel();
		if (map.x() > m_sheet.width())
			m_sheet.rwidth() = map.x();
	}
	m_sheet.rheight() = map.y() + lineHeight;
	_Expand(m_data, offset);
	for (int i=0; i<imgs->num_parts; ++i) {
		auto &img = imgs->parts[i];
		auto &part = m_parts[i];
		if (imgs->format == SUBBITMAP_INDEXED) {
			auto bmp = static_cast<osd_bmp_indexed*>(img.bitmap);
			quint32 *p = data<quint32>(i);
			for (int y=0; y<img.h; ++y) {
				quint32 *dest = p + y*part.strideAsPixel();
				const uchar *src = bmp->bitmap + y*img.stride;
				for (int x=0; x<img.w; ++x)
					*dest++ = bmp->palette[*src++];
			}
		} else {
			if (part.m_stride == img.stride)
				memcpy(data(i), img.bitmap, img.stride*img.h);
			else {
				auto dest = data(i);
				auto src = static_cast<uchar*>(img.bitmap);
				for (int i=0; i<img.h; ++i, dest += part.m_stride, src += img.stride)
					memcpy(dest, src, img.w);
			}
		}
	}
	return true;
}