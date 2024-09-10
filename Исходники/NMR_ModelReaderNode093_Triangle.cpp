	void CModelReaderNode093_Triangle::OnAttribute(_In_z_ const nfWChar * pAttributeName, _In_z_ const nfWChar * pAttributeValue)
	{
		__NMRASSERT(pAttributeName);
		__NMRASSERT(pAttributeValue);
		nfInt32 nValue;

		if (wcscmp(pAttributeName, XML_3MF_ATTRIBUTE_TRIANGLE_V1) == 0) {
			nValue = fnWStringToInt32(pAttributeValue);
			if ((nValue >= 0) && (nValue < XML_3MF_MAXRESOURCEINDEX))
				m_nIndex1 = nValue;
		}

		if (wcscmp(pAttributeName, XML_3MF_ATTRIBUTE_TRIANGLE_V2) == 0) {
			nValue = fnWStringToInt32(pAttributeValue);
			if ((nValue >= 0) && (nValue < XML_3MF_MAXRESOURCEINDEX))
				m_nIndex2 = nValue;
		}

		if (wcscmp(pAttributeName, XML_3MF_ATTRIBUTE_TRIANGLE_V3) == 0) {
			nValue = fnWStringToInt32(pAttributeValue);
			if ((nValue >= 0) && (nValue < XML_3MF_MAXRESOURCEINDEX))
				m_nIndex3 = nValue;
		}

		if (wcscmp(pAttributeName, XML_3MF_ATTRIBUTE_TRIANGLE_CV1) == 0) {
			nValue = fnWStringToInt32(pAttributeValue);
			if ((nValue >= 0) && (nValue < XML_3MF_MAXRESOURCEINDEX))
				m_nTextureIndex1 = nValue;
		}

		if (wcscmp(pAttributeName, XML_3MF_ATTRIBUTE_TRIANGLE_CV2) == 0) {
			nValue = fnWStringToInt32(pAttributeValue);
			if ((nValue >= 0) && (nValue < XML_3MF_MAXRESOURCEINDEX))
				m_nTextureIndex2 = nValue;
		}

		if (wcscmp(pAttributeName, XML_3MF_ATTRIBUTE_TRIANGLE_CV3) == 0) {
			nValue = fnWStringToInt32(pAttributeValue);
			if ((nValue >= 0) && (nValue < XML_3MF_MAXRESOURCEINDEX))
				m_nTextureIndex3 = nValue;
		}

		if (wcscmp(pAttributeName, XML_3MF_ATTRIBUTE_TRIANGLE_COLORID) == 0) {
			std::wstring sValue(pAttributeValue);
			std::wstring sSubStr = sValue.substr(0, 4);
			if (sSubStr == L"tex(") {
				if (sValue.length() > 4) {
					std::wstring sTexID = sValue.substr(4, sValue.length() - sSubStr.length() - 1);
					nfInt32 nValue = fnWStringToInt32(sTexID.c_str());
					if ((nValue < 0) || (nValue >= XML_3MF_MAXRESOURCEINDEX))
						throw CNMRException(NMR_ERROR_INVALIDTEXTUREREFERENCE);

					m_nTextureID = nValue + 1;

				}
				else {
					throw CNMRException(NMR_ERROR_INVALIDTEXTUREREFERENCE);
				}

			}
			else {
				const wchar_t * pCommaValue = wcschr(pAttributeValue, L',');

				// Check, if we have a single value
				if (pCommaValue == nullptr) {

					nValue = fnWStringToInt32(pAttributeValue);
					if ((nValue >= 0) && (nValue < XML_3MF_MAXRESOURCEINDEX)) {
						m_nColorID1 = nValue + 1;
						m_nColorID2 = nValue + 1;
						m_nColorID3 = nValue + 1;
					}
				}
				else {
					// Check, if we have a color triplet
					nfInt32 nColorID1 = -1;
					nfInt32 nColorID2 = -1;
					nfInt32 nColorID3 = -1;

					fnStringToCommaSeparatedIntegerTriplet(pAttributeValue, nColorID1, nColorID2, nColorID3);

					if ((nColorID1 >= 0) && (nColorID1 < XML_3MF_MAXRESOURCEINDEX))
						m_nColorID1 = nColorID1 + 1;
					if ((nColorID2 >= 0) && (nColorID2 < XML_3MF_MAXRESOURCEINDEX))
						m_nColorID2 = nColorID2 + 1;
					if ((nColorID3 >= 0) && (nColorID3 < XML_3MF_MAXRESOURCEINDEX))
						m_nColorID3 = nColorID3 + 1;
				}
			}
		}

		if (wcscmp(pAttributeName, XML_3MF_ATTRIBUTE_TRIANGLE_MATERIALID) == 0) {
			nValue = fnWStringToInt32(pAttributeValue);
			if ((nValue >= 0) && (nValue < XML_3MF_MAXRESOURCEINDEX))
				m_nMaterialID = nValue + 1;
		}

	}