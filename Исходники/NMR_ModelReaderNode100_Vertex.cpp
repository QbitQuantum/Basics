	void CModelReaderNode100_Vertex::OnAttribute(_In_z_ const nfWChar * pAttributeName, _In_z_ const nfWChar * pAttributeValue)
	{
		__NMRASSERT(pAttributeName);
		__NMRASSERT(pAttributeValue);

		if (wcscmp(pAttributeName, XML_3MF_ATTRIBUTE_VERTEX_X) == 0) {
			m_fX = wcstof(pAttributeValue, nullptr);
			if (isnan (m_fX))
				throw CNMRException(NMR_ERROR_INVALIDMODELCOORDINATES);
			if (fabs (m_fX) > XML_3MF_MAXIMUMCOORDINATEVALUE)
				throw CNMRException(NMR_ERROR_INVALIDMODELCOORDINATES);
			m_bHasX = true;
		}

		if (wcscmp(pAttributeName, XML_3MF_ATTRIBUTE_VERTEX_Y) == 0) {
			m_fY = wcstof(pAttributeValue, nullptr);
			if (isnan (m_fY))
				throw CNMRException(NMR_ERROR_INVALIDMODELCOORDINATES);
			if (fabs(m_fY) > XML_3MF_MAXIMUMCOORDINATEVALUE)
				throw CNMRException(NMR_ERROR_INVALIDMODELCOORDINATES);
			m_bHasY = true;
		}

		if (wcscmp(pAttributeName, XML_3MF_ATTRIBUTE_VERTEX_Z) == 0) {
			m_fZ = wcstof(pAttributeValue, nullptr);
			if (isnan (m_fZ))
				throw CNMRException(NMR_ERROR_INVALIDMODELCOORDINATES);
			if (fabs(m_fZ) > XML_3MF_MAXIMUMCOORDINATEVALUE)
				throw CNMRException(NMR_ERROR_INVALIDMODELCOORDINATES);
			m_bHasZ = true;
		}
	}