		void CULSplitter::DrawXorBar(HDC hDC, int x1, int y1, int width, int height)
		{
			static WORD _dotPatternBmp[8] = 
			{ 
				0x00aa,0x0055,0x00aa,0x0055, 
				0x00aa,0x0055,0x00aa,0x0055
			};


			HBITMAP hbm=CreateBitmap(8,8,1,1,_dotPatternBmp);
			HBRUSH  hbr=CreatePatternBrush(hbm);

			SetBrushOrgEx(hDC,x1,y1,0);
			HBRUSH  hbrushOld=(HBRUSH)SelectObject(hDC, hbr);

			PatBlt(hDC, x1, y1, width, height, PATINVERT);

			SelectObject(hDC, hbrushOld);

			DeleteObject(hbr);
			DeleteObject(hbm);
		}