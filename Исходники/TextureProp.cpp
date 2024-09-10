static void PaintPreviewWnd(CTextureProp *pDlg, HWND hWnd, HDC hDC)
{
	CMoDWordArray rgbData;
	CMoWordArray rgb4444Data;
	TextureData *pTexture;
	FMConvertRequest cRequest;
	FormatMgr formatMgr;
	DRESULT dResult;
	DWORD x, y, *pInLine, r, g, b, a, outYCoord, iMipmap;
	S3TC_Compressor compressor;
	HPEN hPen, hOldPen;
	int oldROP;
	BPPIdent bppIdent;
	char oldText[256];
	TextureMipData *pMip;


	if(!pDlg || !pDlg->m_pPreviewTexture)
		return;

	pTexture = pDlg->m_pPreviewTexture;
	if(!rgbData.SetSize(pTexture->m_Header.m_BaseWidth * pTexture->m_Header.m_BaseHeight))
		return;

	GetWindowText(hWnd, oldText, sizeof(oldText));
	outYCoord = 0;

	for(iMipmap=0; iMipmap < pTexture->m_Header.m_nMipmaps; iMipmap++)
	{
		pMip = &pTexture->m_Mips[iMipmap];

		// Get us into PValue format.
		SetWindowText(hWnd, "Converting...");
		dtx_SetupDTXFormat(pTexture, cRequest.m_pSrcFormat);
		cRequest.m_pSrc = pMip->m_Data;
		cRequest.m_SrcPitch = pMip->m_Pitch;
		cRequest.m_pDestFormat->InitPValueFormat();
		cRequest.m_pDest = (BYTE*)rgbData.GetArray();
		cRequest.m_DestPitch = pMip->m_Width * sizeof(DWORD);
		cRequest.m_Width = pMip->m_Width;
		cRequest.m_Height = pMip->m_Height;

		if( pTexture->m_Header.GetBPPIdent() == BPP_32P )
		{
			DtxSection* pSection = dtx_FindSection(pTexture, "PALLETE32");
			if( pSection )
			{
				cRequest.m_pSrcPalette = (RPaletteColor*)pSection->m_Data;  
			}
		}

		dResult = formatMgr.ConvertPixels(&cRequest);
		if(dResult != LT_OK)
		{
			SetWindowText(hWnd, oldText);
			return;
		}

		// Store this in the stack so it doesn't crash if they change it in the other thread.
		bppIdent = pDlg->m_BPPIdent;

		// Possibly compress.
		if(IsBPPCompressed(bppIdent) && bppIdent != pTexture->m_Header.GetBPPIdent())
		{
			compressor.m_Format = bppIdent;
			compressor.m_Width = pMip->m_Width;
			compressor.m_Height = pMip->m_Height;

			compressor.m_pData = rgbData.GetArray();
			compressor.m_Pitch = pMip->m_Width * sizeof(DWORD);
			compressor.m_DataFormat.InitPValueFormat();
			
			SetWindowText(hWnd, "Compressing...");
			dResult = compressor.CompressUsingLibrary();
			if(dResult == LT_OK)
			{
				// Now decompress into the PValue format.
				cRequest.m_pSrcFormat->Init(bppIdent, 0, 0, 0, 0);
				cRequest.m_pSrc = (BYTE*)compressor.m_pOutData;
				cRequest.m_pDestFormat->InitPValueFormat();
				cRequest.m_pDest = (BYTE*)rgbData.GetArray();
				cRequest.m_DestPitch = pMip->m_Width * sizeof(DWORD);
				cRequest.m_Width = pMip->m_Width;
				cRequest.m_Height = pMip->m_Height;

				SetWindowText(hWnd, "Decompressing...");
				dResult = formatMgr.ConvertPixels(&cRequest);

				delete compressor.m_pOutData;
			}
		}
		

		SetWindowText(hWnd, "Drawing...");
		hPen = CreatePen(PS_SOLID, 1, RGB(255,255,255));
		hOldPen = (HPEN)SelectObject(hDC, hPen);
			pInLine = rgbData.GetArray();
			for(y=0; y < pMip->m_Height; y++)
			{
				oldROP = SetROP2(hDC, R2_XORPEN);
				MoveToEx(hDC, 0, outYCoord+1, NULL);
				LineTo(hDC, pMip->m_Width*2, outYCoord+1);
				SetROP2(hDC, oldROP);

				for(x=0; x < pMip->m_Width; x++)
				{
					PValue_Get(pInLine[x], a, r, g, b);
					SetPixel(hDC, x, outYCoord, RGB(r, g, b));
					SetPixel(hDC, x+pMip->m_Width, outYCoord, RGB(a, a, a));
				}

				pInLine += pMip->m_Width;
				++outYCoord;
			}
		SelectObject(hDC, hOldPen);
		DeleteObject(hPen);
	}

	SetWindowText(hWnd, oldText);
}