BShape*
TransportControlGroup::_CreatePauseShape(float height) const
{
	BShape* shape = new BShape();

	float stemWidth = floorf(height / 3);

	shape->MoveTo(BPoint(0, height));
	shape->LineTo(BPoint(stemWidth, height));
	shape->LineTo(BPoint(stemWidth, 0));
	shape->LineTo(BPoint(0, 0));
	shape->Close();

	shape->MoveTo(BPoint(height - stemWidth, height));
	shape->LineTo(BPoint(height, height));
	shape->LineTo(BPoint(height, 0));
	shape->LineTo(BPoint(height - stemWidth, 0));
	shape->Close();

	return shape;
}