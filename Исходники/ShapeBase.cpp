bool wxSFShapeBase::Intersects(const wxRect& rct)
{
	// HINT: overload it for custom actions...

	return rct.Intersects(this->GetBoundingBox());
}