void PageView::addRerenderRect(double x, double y, double width, double height)
{
	XOJ_CHECK_TYPE(PageView);

	if (this->rerenderComplete)
	{
		return;
	}

	Rectangle* rect = new Rectangle(x, y, width, height);

	Rectangle dest;

	g_mutex_lock(this->repaintRectMutex);

	for (GList* l = this->rerenderRects; l != NULL; l = l->next)
	{
		Rectangle* r = (Rectangle*) l->data;

		// its faster to redraw only one rect than repaint twice the same area
		// so loop through the rectangles to be redrawn, if new rectangle
		// intersects any of them, replace it by the union with the new one
		if (r->intersects(*rect))
		{
			r->add(*rect);

			delete rect;

			g_mutex_unlock(this->repaintRectMutex);
			return;
		}
	}

	this->rerenderRects = g_list_append(this->rerenderRects, rect);
	g_mutex_unlock(this->repaintRectMutex);

	this->xournal->getControl()->getScheduler()->addRerenderPage(this);
}