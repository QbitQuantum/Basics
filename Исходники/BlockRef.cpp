// gets bounding box of element
Rectf DXFBlockRef::GetBoundingBox(void) const
{
	Rectf res;
	
	// get dxf object
	DXF const &dxf = GetDXF();

	// get block data by name; if none, returns
	if(!dxf.HasBlock(name))
		return Rectf(1e99, -1e99, -1e99, 1e99);
	DXFBlock const &blk = dxf.GetBlock(name);

	// get the bounding box of included entities
	Rectf bbe = blk.entities.GetBoundingBox();
	
	// now we need to apply transformation to bbox points
	TransMatrix M;
	M.Translate(insertPoint).Rotate(angle).Scale(scale);
	Pointf bl = M(bbe.BottomLeft());
	Pointf tl = M(bbe.TopLeft());
	Pointf br = M(bbe.BottomRight());
	Pointf tr = M(bbe.TopRight());
	
	// and now get the minimum and maximum coordinate values
	res.left	= min(min(bl.x, tl.x), min(br.x, tr.x));
	res.right	= max(max(bl.x, tl.x), max(br.x, tr.x));
	res.bottom	= min(min(bl.y, tl.y), min(br.y, tr.y));
	res.top		= max(max(bl.y, tl.y), max(br.y, tr.y));

	return res;
}