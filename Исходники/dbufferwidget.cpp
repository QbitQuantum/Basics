void NDbufferWidget::paintEvent ( QPaintEvent * ) {
	bitBlt(this, 0, 0, backpixmap_[showpixmap_]);
}