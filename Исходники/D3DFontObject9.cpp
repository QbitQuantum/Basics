	RECT D3DFontObject9::GetTextExtent(std::wstring textString, RECT rect, uint32 flags) const {
		if (m_d3dxFont != nullptr) {
			uint32 length = textString.length();
			bool trailingSpace = (length != 0 && textString.back() == L' ');
			if (trailingSpace)
				textString.back() = L'.';

			m_d3dxFont->DrawTextW(nullptr, textString.data(), length, &rect, flags | DT_CALCRECT, 0);

			// adjust the rectangle...
			if (trailingSpace) {
				rect.right += m_spaceExtent.x;
				rect.right -= m_pointExtent.x;
			}
		}

		return rect;
	}