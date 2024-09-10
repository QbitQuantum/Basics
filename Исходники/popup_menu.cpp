void PopupMenu::paintBg(Painter &p) {
	if (_useTransparency) {
		Shadow::paint(p, _inner, width(), _st.shadow);
		App::roundRect(p, _inner, _st.menu.itemBg, ImageRoundRadius::Small);
	} else {
		p.fillRect(0, 0, width() - _padding.right(), _padding.top(), _st.shadow.fallback);
		p.fillRect(width() - _padding.right(), 0, _padding.right(), height() - _padding.bottom(), _st.shadow.fallback);
		p.fillRect(_padding.left(), height() - _padding.bottom(), width() - _padding.left(), _padding.bottom(), _st.shadow.fallback);
		p.fillRect(0, _padding.top(), _padding.left(), height() - _padding.top(), _st.shadow.fallback);
		p.fillRect(_inner, _st.menu.itemBg);
	}
}