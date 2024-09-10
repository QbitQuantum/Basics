/**
 * This widget was created before render transforms existed for each widget, and it chose to apply the render transform AFTER the layout transform.
 * This means leveraging the render transform of FGeometry would be expensive, as we would need to use Concat(LayoutTransform, RenderTransform, Inverse(LayoutTransform).
 * Instead, we maintain the old way of doing it by modifying the AllottedGeometry only during rendering to append the widget's implied RenderTransform to the existing LayoutTransform.
 */
int32 SFxWidget::OnPaint( const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyClippingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled ) const
{
	// Convert the 0..1 origin into local space extents.
	const FVector2D ScaleOrigin = RenderScaleOrigin.Get() * AllottedGeometry.Size;
	const FVector2D Offset = VisualOffset.Get() * AllottedGeometry.Size;
	// create the render transform as a scale around ScaleOrigin and offset it by Offset.
	const auto RenderTransform = Concatenate(Inverse(ScaleOrigin), RenderScale.Get(), ScaleOrigin, Offset);
	// This will append the render transform to the layout transform, and we only use it for rendering.
	FGeometry ModifiedGeometry = AllottedGeometry.MakeChild(AllottedGeometry.Size, RenderTransform);
	
	FArrangedChildren ArrangedChildren(EVisibility::Visible);
	this->ArrangeChildren(ModifiedGeometry, ArrangedChildren);

	// There may be zero elements in this array if our child collapsed/hidden
	if( ArrangedChildren.Num() > 0 )
	{
		// We can only have one direct descendant.
		check( ArrangedChildren.Num() == 1 );
		const FArrangedWidget& TheChild = ArrangedChildren[0];

		// SFxWidgets are able to ignore parent clipping.
		const FSlateRect ChildClippingRect = (bIgnoreClipping.Get())
			? ModifiedGeometry.GetClippingRect()
			: MyClippingRect.IntersectionWith(ModifiedGeometry.GetClippingRect());

		FWidgetStyle CompoundedWidgetStyle = FWidgetStyle(InWidgetStyle)
			.BlendColorAndOpacityTint(ColorAndOpacity.Get())
			.SetForegroundColor( ForegroundColor );

		return TheChild.Widget->Paint( Args.WithNewParent(this), TheChild.Geometry, ChildClippingRect, OutDrawElements, LayerId + 1, CompoundedWidgetStyle, ShouldBeEnabled( bParentEnabled ) );
	}
	return LayerId;

}