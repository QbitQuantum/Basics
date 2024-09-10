void CoverWidget::paintDivider(Painter &p) {
	auto dividerHeight = st::profileDividerLeft.height();
	auto divider = rtlrect(0, _dividerTop, width(), dividerHeight, width());
	p.fillRect(divider, st::profileDividerBg);
	auto dividerFillTop = rtlrect(0, _dividerTop, width(), st::profileDividerTop.height(), width());
	st::profileDividerTop.fill(p, dividerFillTop);
	auto dividerFillBottom = rtlrect(0, _dividerTop + dividerHeight - st::profileDividerBottom.height(), width(), st::profileDividerBottom.height(), width());
	st::profileDividerBottom.fill(p, dividerFillBottom);
}