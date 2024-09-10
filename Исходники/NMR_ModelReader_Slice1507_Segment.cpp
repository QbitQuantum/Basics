	void CModelReaderNode_Slices1507_Segment::OnAttribute(_In_z_ const nfWChar * pAttributeName, _In_z_ const nfWChar * pAttributeValue) {
		if (wcscmp(pAttributeName, XML_3MF_ATTRIBUTE_SLICESEGMENT_V2) == 0) {
			m_pSlice->addPolygonIndex(m_PolygonIndex, fnWStringToInt32(pAttributeValue));
		}
	}