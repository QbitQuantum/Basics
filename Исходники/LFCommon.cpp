void TLFDetectedItem::Resize(double factor)
{
	TLFRect* rect = this->GetBounds();
	if (rect != NULL)
	{
		awpRect  awpr = rect->GetRect();
		awpr.left = (AWPSHORT)floor(awpr.left*factor + 0.5);
		awpr.right = (AWPSHORT)floor(awpr.right*factor + 0.5);
		awpr.top = (AWPSHORT)floor(awpr.top*factor + 0.5);
		awpr.bottom = (AWPSHORT)floor(awpr.bottom*factor + 0.5);
		rect->SetRect(awpr);
	}
}