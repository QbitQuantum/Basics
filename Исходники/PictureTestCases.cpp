static void testStrokeShape(BView *view, BRect frame)
{
	frame.InsetBy(2, 2);
	BShape shape;
	shape.MoveTo(BPoint(frame.left, frame.bottom));
	shape.LineTo(BPoint(frame.right, frame.top));
	shape.LineTo(BPoint(frame.left, frame.top));
	shape.LineTo(BPoint(frame.right, frame.bottom));
	view->StrokeShape(&shape);
}