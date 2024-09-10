//-------------------------------------------------------------------------------------------------
Action* FlattenBrush::applyHeightToSelection(float height)
{
	beginPaint();
	for (size_t j = 0; j < land->realVerticesMapSide; ++j)
	{
		for (size_t i = 0; i < land->realVerticesMapSide; ++i)
		{
			if (land->isVertexSelected(j, i))
			{
				flattenVertex(j, i, height);
			}
		}
	}
	return endPaint();
}