void PeerListWidget::paintOutlinedRect(Painter &p, int x, int y, int w, int h) const {
	auto outlineWidth = _st.button.outlineWidth;
	if (outlineWidth) {
		p.fillRect(rtlrect(x, y, outlineWidth, h, width()), _st.button.outlineFgOver);
	}
	p.fillRect(rtlrect(x + outlineWidth, y, w - outlineWidth, h, width()), _st.button.textBgOver);
}