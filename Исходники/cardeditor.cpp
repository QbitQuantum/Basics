BlackEdgeTextItem::BlackEdgeTextItem()
	:skip(0), color(Qt::black), outline(0)
{
	setFlags(ItemIsMovable | ItemIsFocusable);
}