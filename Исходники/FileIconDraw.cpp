void FileIconDrawGlass::Text(HDC hdc, PCTCHAR pcszText, const RECT &rc, eTextColor eColor, UINT uFlags)
{
	if (!pcszText || !*pcszText) return;

	// Find out actual size of text
	int nChars = _tcslen(pcszText);
	uFlags |= DT_NOCLIP;

	int iX = rc.left;
	int iY = rc.top;
	int iXW = (rc.right - iX);
	int iYH = (rc.bottom - iY);

	RECT rcMin = rc;
	if (DrawText(hdcTextDIB, pcszText, nChars, &rcMin, uFlags | DT_CALCRECT)) {
		int iMinXW = rcMin.right - rcMin.left;
		int iMinYH = rcMin.bottom - rcMin.top;
		if (iMinXW < iXW) {
			if (uFlags & DT_CENTER) {
				iX += (iXW - iMinXW)/2;
				uFlags &= ~DT_CENTER;
			} else if (uFlags & DT_RIGHT) {
				iX += (iXW - iMinXW);
				uFlags &= ~DT_RIGHT;
			}
			iXW = iMinXW;
		}
		if (iMinYH < iYH) {
			if (uFlags & DT_SINGLELINE) {
				if (uFlags & DT_VCENTER) {
					iY += (iYH - iMinYH)/2;
					uFlags &= ~DT_VCENTER;
				} else if (uFlags & DT_BOTTOM) {
					iY += (iYH - iMinYH);
					uFlags &= ~DT_BOTTOM;
				}
			}
			iYH = iMinYH;
		}
	}

	iXW += 2;	// NB: +2 'cause we want an extra pixel at the border so that the font smoothing will look bette!
	iYH += 2;

	// Ensure we have a big enough DIB to draw the text to
	if ((iXW > iTextDIBXW) || (iYH > iTextDIBYH)) CreateTextDIB(iXW, iYH);
	if (!hbmpTextDIB) return;

	// Select color
	ieBGRA clr;
	switch (eColor) {
	case eFileName:	clr = clrFileName;		break;
	case eComment:	clr = clrComment;		break;
	case eFileInfo:	clr = clrFileInfo;		break;
	default:		clr = ieBGRA(0,0,0);	break;
	}
	clr.A = 0xFF - clrBkg.A;

	// Draw the text to in-memory DIB
	RECT rcTextDIB = { 0, 0, iXW, iYH };
	FillRect(hdcTextDIB, &rcTextDIB, hbrBkg);

	rcTextDIB.left++;
	rcTextDIB.top++;

	DrawText(hdcTextDIB, pcszText, nChars, &rcTextDIB, uFlags);

	// Modify DIB:
#ifndef __X64__
	if (g_bSSE2) 
#endif
	{
		__m128i r0, r1, r2, r3, r4, r5, r6, r7;

		r7 = _mm_setzero_si128();									// 0
		r6 = _mm_set1_epi32(clr.dw);								// CA  CR  CG  CB  CA  CR  CG  CB  CA  CR  CG  CB  CA  CR  CG  CB
		r6 = _mm_unpacklo_epi8(r7, r6);								// CA<<8   CR<<8   CG<<8   CB<<8   CA<<8   CR<<8   CG<<8   CB<<8
		r5 = _mm_set1_epi16(1);										// 1       1       1       1       1       1       1       1
		r4 = _mm_set1_epi32(0xFF);									// FF              FF              FF              FF
		r3 = _mm_set1_epi32(clrBkg.dw);								// DA  0   0   0   DA  0   0   0   DA  0   0   0   DA  0   0   0

		ieBGRA *py = pTextDIB;
		for (int y = iYH; y--; py += iTextDIBXW) {
			ieBGRA *px = py;

			for (int x_4 = (iXW+3)>>2; x_4--; px += 4) {

				r0 = _mm_load_si128((__m128i *)px);
				r1 = r0;
				r2 = r0;											// X3  R3  G3  B3  X2  R2  G2  B2  X1  R1  G1  B1  X0  R0  G0  B0 
				r0 = _mm_srli_epi32(r0, 16);						// 0   0   X3  R3  0   0   X2  R2  0   0   X1  R1  0   0   X0  R0 
				r1 = _mm_srli_epi32(r1, 8);							// 0   X3  R3  G3  0   X2  R2  G2  0   X1  R1  G1  0   X0  R0  G0 
				r0 = _mm_max_epu8(r0, r2);
				r0 = _mm_max_epu8(r0, r1);							// x   x   x   A3  x   x   x   A2  x   x   x   A1  x   x   x   A0
				r0 = _mm_and_si128(r0, r4);							// 0       A3      0       A2      0       A1      0       A0
				r0 = _mm_shufflelo_epi16(r0, _MM_SHUFFLE(2,2,0,0));
				r0 = _mm_shufflehi_epi16(r0, _MM_SHUFFLE(2,2,0,0));	// A3      A3      A2      A2      A1      A1      A0      A0
				r1 = r0;
				r0 = _mm_unpacklo_epi32(r0, r0);					// A1      A1      A1      A1      A0      A0      A0      A0
				r1 = _mm_unpackhi_epi32(r1, r1);					// A3      A3      A3      A3      A2      A2      A2      A2
				r0 = _mm_add_epi16(r0, r5);							// A1'     A1'     A1'     A1'     A0'     A0'     A0'     A0' 
				r1 = _mm_add_epi16(r1, r5);							// A3'     A3'     A3'     A3'     A2'     A2'     A2'     A2' 
				r0 = _mm_mulhi_epu16(r0, r6);						// xA1"    xR1     xG1     xB1     xA0"    xR0     xG0     xB0
				r1 = _mm_mulhi_epu16(r1, r6);						// xA3"    xR3     xG3     xB3     xA2"    xR2     xG2     xB2
				r0 = _mm_packus_epi16(r0, r1);						// xA3"xR3 xG3 xB3 xA2"xR2 xG2 xB2 xA1"xR1 xG1 xB1 xA0"xR0 xG0 xB0
				r0 = _mm_adds_epu8(r0, r3);							// xA3 xR3 xG3 xB3 xA2 xR2 xG2 xB2 xA1 xR1 xG1 xB1 xA0 xR0 xG0 xB0
				_mm_store_si128((__m128i *)px, r0);
			}
		}
	}
#ifndef __X64__
	else {