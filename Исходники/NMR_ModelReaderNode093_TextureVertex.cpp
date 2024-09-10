	void CModelReaderNode093_TextureVertex::OnAttribute(_In_z_ const nfWChar * pAttributeName, _In_z_ const nfWChar * pAttributeValue)
	{
		__NMRASSERT(pAttributeName);
		__NMRASSERT(pAttributeValue);

		if (wcscmp(pAttributeName, XML_3MF_ATTRIBUTE_TEXTURE_U) == 0) {
			m_fU = wcstof(pAttributeValue, nullptr);
			if (std::isnan (m_fU))
				throw CNMRException(NMR_ERROR_INVALIDMODELTEXTURECOORDINATES);
			if (fabs (m_fU) > XML_3MF_MAXIMUMCOORDINATEVALUE)
				throw CNMRException(NMR_ERROR_INVALIDMODELTEXTURECOORDINATES);
			m_bHasU = true;
		}

		if (wcscmp(pAttributeName, XML_3MF_ATTRIBUTE_TEXTURE_V) == 0) {
			m_fV = wcstof(pAttributeValue, nullptr);
			if (std::isnan (m_fV))
				throw CNMRException(NMR_ERROR_INVALIDMODELTEXTURECOORDINATES);
			if (fabs(m_fV) > XML_3MF_MAXIMUMCOORDINATEVALUE)
				throw CNMRException(NMR_ERROR_INVALIDMODELTEXTURECOORDINATES);
			m_bHasV = true;
		}

	}