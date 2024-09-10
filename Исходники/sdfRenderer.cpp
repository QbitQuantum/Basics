void SdfRenderer::render(QPainter *painter, const QRectF &bounds)
{
	current_size_x = static_cast<int>(bounds.width());
	current_size_y = static_cast<int>(bounds.height());
	mStartX = static_cast<int>(bounds.x());
	mStartY = static_cast<int>(bounds.y());
	this->painter = painter;
	QDomElement docElem = doc.documentElement();
	QDomNode node = docElem.firstChild();
	while(!node.isNull())
	{
		QDomElement elem = node.toElement();
		if(!elem.isNull())
		{
			if (elem.tagName()=="line")
			{
				line(elem);
			}
			else if(elem.tagName()=="ellipse")
			{
				ellipse(elem);
			}
			else if (elem.tagName() == "arc") {
				arc(elem);
			}
			else if(elem.tagName()=="background")
			{
				background(elem);
			}
			else if(elem.tagName()=="text")
			{
				draw_text(elem);
			}
			else if (elem.tagName()=="rectangle")
			{
				rectangle(elem);
			}
			else if (elem.tagName()=="polygon")
			{
				polygon(elem);
			}
			else if (elem.tagName()=="point")
			{
				point(elem);
			}
			else if(elem.tagName()=="path")
			{
				path_draw(elem);
			}
			else if(elem.tagName()=="stylus")
			{
				stylus_draw(elem);
			}
			else if(elem.tagName()=="curve")
			{
				curve_draw(elem);
			}
			else if(elem.tagName()=="image")
			{
				image_draw(elem);
			}
		}
		node = node.nextSibling();
	}
	this->painter = 0;
}