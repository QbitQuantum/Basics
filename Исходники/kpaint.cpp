void CardWidget::paintEvent( QPaintEvent *)
{
	bitBlt(this, 0, 0, pm, 0, 0, pm->size().width(), pm->size().height());
}