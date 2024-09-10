FPaintGeometry FGeometry::ToPaintGeometry(const FVector2D& LocalSize, const FSlateLayoutTransform& LayoutTransform) const
{
	FSlateLayoutTransform NewAccumulatedLayoutTransform = Concatenate(LayoutTransform, GetAccumulatedLayoutTransform());
	return FPaintGeometry(NewAccumulatedLayoutTransform, Concatenate(LayoutTransform, GetAccumulatedRenderTransform()), LocalSize);
}