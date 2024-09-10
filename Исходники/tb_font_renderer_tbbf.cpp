bool TBBFRenderer::Load(const char *filename, int size)
{
	m_size = size;
	if (!m_node.ReadFile(filename))
		return false;

	// Check for size nodes and get the one closest to the size we want.
	TBNode *size_node = nullptr;
	for (TBNode *n = m_node.GetFirstChild(); n; n = n->GetNext())
	{
		if (strcmp(n->GetName(), "size") == 0)
		{
			if (!size_node || ABS(m_size - n->GetValue().GetInt()) < ABS(m_size - size_node->GetValue().GetInt()))
				size_node = n;
		}
	}
	if (!size_node)
		return false;

	// Metrics
	m_metrics.ascent = size_node->GetValueInt("ascent", 0);
	m_metrics.descent = size_node->GetValueInt("descent", 0);
	m_metrics.height = m_metrics.ascent + m_metrics.descent;

	// Other data
	m_advance_delta = size_node->GetValueInt("advance_delta", 0);
	m_space_advance = size_node->GetValueInt("space_advance", 0);
	m_x_ofs = size_node->GetValueInt("x_ofs", 0);

	// Info
	m_rgb = m_node.GetValueInt("info>rgb", 0);

	// Get the path for the bitmap file.
	TBTempBuffer bitmap_filename;
	if (!bitmap_filename.AppendPath(filename))
		return false;

	// Append the bitmap filename for the given size.
	bitmap_filename.AppendString(size_node->GetValueString("bitmap", ""));

	m_img = TBImageLoader::CreateFromFile(bitmap_filename.GetData());

	return FindGlyphs();
}