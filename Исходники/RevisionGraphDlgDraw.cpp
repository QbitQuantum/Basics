void CRevisionGraphWnd::DrawGlyphs
	( GraphicsDevice& graphics
	, Image* glyphs
	, const CVisibleGraphNode* node
	, const RectF& nodeRect
	, DWORD state
	, DWORD allowed
	, bool upsideDown)
{
	// shortcut

	if ((state == 0) && (allowed == 0))
		return;

	// draw all glyphs

	PointF topCenter (0.5f * nodeRect.GetLeft() + 0.5f * nodeRect.GetRight(), nodeRect.GetTop());
	PointF rightCenter (nodeRect.GetRight(), 0.5f * nodeRect.GetTop() + 0.5f * nodeRect.GetBottom());
	PointF bottomCenter (0.5f * nodeRect.GetLeft() + 0.5f * nodeRect.GetRight(), nodeRect.GetBottom());

	DrawGlyphs ( graphics
				, glyphs
				, node
				, upsideDown ? bottomCenter : topCenter
				, (state & CGraphNodeStates::COLLAPSED_ABOVE) ? ExpandGlyph : CollapseGlyph
				, (state & CGraphNodeStates::SPLIT_ABOVE) ? JoinGlyph : SplitGlyph
				, upsideDown ? Below : Above
				, CGraphNodeStates::COLLAPSED_ABOVE
				, CGraphNodeStates::SPLIT_ABOVE
				, (allowed & CGraphNodeStates::COLLAPSED_ABOVE) != 0);

	DrawGlyphs ( graphics
				, glyphs
				, node
				, rightCenter
				, (state & CGraphNodeStates::COLLAPSED_RIGHT) ? ExpandGlyph : CollapseGlyph
				, (state & CGraphNodeStates::SPLIT_RIGHT) ? JoinGlyph : SplitGlyph
				, Right
				, CGraphNodeStates::COLLAPSED_RIGHT
				, CGraphNodeStates::SPLIT_RIGHT
				, (allowed & CGraphNodeStates::COLLAPSED_RIGHT) != 0);

	DrawGlyphs ( graphics
				, glyphs
				, node
				, upsideDown ? topCenter : bottomCenter
				, (state & CGraphNodeStates::COLLAPSED_BELOW) ? ExpandGlyph : CollapseGlyph
				, (state & CGraphNodeStates::SPLIT_BELOW) ? JoinGlyph : SplitGlyph
				, upsideDown ? Above : Below
				, CGraphNodeStates::COLLAPSED_BELOW
				, CGraphNodeStates::SPLIT_BELOW
				, (allowed & CGraphNodeStates::COLLAPSED_BELOW) != 0);

}