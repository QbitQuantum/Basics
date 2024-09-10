// add the entire signal b to this signal, at the integer destination offset. 
// 
void MLSignal::add2D(const MLSignal& b, int destX, int destY)
{
	MLSignal& a = *this;
	MLRect srcRect(0, 0, b.getWidth(), b.getHeight());
	MLRect destRect = srcRect.translated(Vec2(destX, destY)).intersect(getBoundsRect());
	
	for(int j=destRect.top(); j<destRect.bottom(); ++j)
	{
		for(int i=destRect.left(); i<destRect.right(); ++i)
		{
			a(i, j) += b(i - destX, j - destY);
		}
	}

	setConstant(false);
}