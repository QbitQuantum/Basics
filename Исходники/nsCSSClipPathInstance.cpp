already_AddRefed<Path>
nsCSSClipPathInstance::CreateClipPathPolygon(DrawTarget* aDrawTarget,
                                             const nsRect& aRefBox)
{
  StyleBasicShape* basicShape = mClipPathStyle.GetBasicShape();
  FillRule fillRule = basicShape->GetFillRule() == StyleFillRule::Nonzero ?
                        FillRule::FILL_WINDING : FillRule::FILL_EVEN_ODD;
  RefPtr<PathBuilder> builder = aDrawTarget->CreatePathBuilder(fillRule);

  nsTArray<nsPoint> vertices =
    ShapeUtils::ComputePolygonVertices(basicShape, aRefBox);
  if (vertices.IsEmpty()) {
    MOZ_ASSERT_UNREACHABLE(
      "ComputePolygonVertices() should've given us some vertices!");
  } else {
    nscoord appUnitsPerDevPixel =
      mTargetFrame->PresContext()->AppUnitsPerDevPixel();
    builder->MoveTo(NSPointToPoint(vertices[0], appUnitsPerDevPixel));
    for (size_t i = 1; i < vertices.Length(); ++i) {
      builder->LineTo(NSPointToPoint(vertices[i], appUnitsPerDevPixel));
    }
  }
  builder->Close();
  return builder->Finish();
}