ieResult ie_CopyX2wBGRA(iePImage pimDst, iePCImage pimSrc)
{
	if (!pimDst->wBGRA() || !pimSrc->IsEqualSize(pimDst)) return IE_E_INVALIDPARAM;
	
	if (pimSrc->wBGRA()) {
		// wBGRA -> wBGRA
		return ie_CopyX2X(pimDst, pimSrc);
	}

	iePwBGRA pDst8 = pimDst->wBGRA()->PixelPtr();
	DWORD	nPitchDst8 = pimDst->wBGRA()->Pitch();
	ieWH	wh{ pimSrc->WH() };

	switch (pimSrc->PixelFormat()) {

	case iePixelFormat::CLUT: {
		// CLUT -> wBGRA
		iePCILUT pSrc1 = pimSrc->CLUT()->PixelPtr();
		DWORD	nPitchSrc1 = pimSrc->CLUT()->Pitch();
		iePCBGRA pLUTSrc4 = pimSrc->CLUT()->CLUTPtr();

		for (; wh.nY--; pSrc1 += nPitchSrc1, pDst8 += nPitchDst8) {
			ie_ILUT2wBGRA(pDst8, pSrc1, pLUTSrc4, wh.nX);
		}
	}	break;

	case iePixelFormat::L: {
		// L -> wBGRA
		iePCL	pSrc1 = pimSrc->L()->PixelPtr();
		DWORD	nPitchSrc1 = pimSrc->L()->Pitch();

		for (; wh.nY--; pSrc1 += nPitchSrc1, pDst8 += nPitchDst8) {
			ie_L2wBGRA(pDst8, pSrc1, wh.nX);
		}
	}	break;

	case iePixelFormat::BGRA: {
		// BGRA -> wBGRA
		iePCBGRA pSrc4 = pimSrc->BGRA()->PixelPtr();
		DWORD	nPitchSrc4 = pimSrc->BGRA()->Pitch();

		for (; wh.nY--; pSrc4 += nPitchSrc4, pDst8 += nPitchDst8) {
			ie_BGRA2wBGRA(pDst8, pSrc4, wh.nX);
		}
	}	break;

	case iePixelFormat::wL: {
		// wL -> wBGRA
		iePCwL	pSrc2 = pimSrc->wL()->PixelPtr();
		DWORD	nPitchSrc2 = pimSrc->wL()->Pitch();

		for (; wh.nY--; pSrc2 += nPitchSrc2, pDst8 += nPitchDst8) {
			ie_wL2wBGRA(pDst8, pSrc2, wh.nX);
		}
	}	break;

	case iePixelFormat::fBGRA: {
		// fBGRA -> wBGRA
		iePCfBGRA pSrc16 = pimSrc->fBGRA()->PixelPtr();
		DWORD	nPitchSrc16 = pimSrc->fBGRA()->Pitch();

		for (; wh.nY--; pSrc16 += nPitchSrc16, pDst8 += nPitchDst8) {
			ie_fBGRA2wBGRA(pDst8, pSrc16, wh.nX);
		}
	}	break;

	case iePixelFormat::fL: {
		// fL -> wBGRA
		iePCfL	pSrc4 = pimSrc->fL()->PixelPtr();
		DWORD	nPitchSrc4 = pimSrc->fL()->Pitch();

		for (; wh.nY--; pSrc4 += nPitchSrc4, pDst8 += nPitchDst8) {
			ie_fL2wBGRA(pDst8, pSrc4, wh.nX);
		}
	}	break;

	default:
		return IE_E_INVALIDCLRFORMAT;

	}

	pimDst->CopyTextFrom(pimSrc);
	pimDst->SetAlphaType(pimSrc->AlphaType());

	return IE_S_OK;
}