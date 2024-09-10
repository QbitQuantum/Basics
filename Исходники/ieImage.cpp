ieResult ieImage::CopyFrom(iePCImage pimSrc, bool bCopyAllFrames)
{
	if (!IsEqualSize(pimSrc)) return IE_E_INVALIDPARAM;

	if (Frame.pimNext) {
		Frame.pimNext->FrameParams().pimPrev = nullptr;
		Frame.pimNext->Release();
		Frame.pimNext = nullptr;
	}

	ieResult res;

	switch (PixelFormat()) {

	case iePixelFormat::BGRA:
		res = ie_CopyX2BGRA(this, pimSrc, gie_pClrOptions->bDitherWide);
		break;

	case iePixelFormat::CLUT:
		res = ie_CopyX2CLUT(this, pimSrc, *gie_pClrOptions);
		break;

	case iePixelFormat::L:
		res = ie_CopyX2L(this, pimSrc, gie_pClrOptions->bDitherWide, gie_pClrOptions->bColorimetricRGB2L);
		break;

	case iePixelFormat::wBGRA:
		res = ie_CopyX2wBGRA(this, pimSrc);
		break;

	case iePixelFormat::wL:
		res = ie_CopyX2wL(this, pimSrc, gie_pClrOptions->bColorimetricRGB2L);
		break;

	case iePixelFormat::fBGRA:
		res = ie_CopyX2fBGRA(this, pimSrc);
		break;

	case iePixelFormat::fL:
		res = ie_CopyX2fL(this, pimSrc, gie_pClrOptions->bColorimetricRGB2L);
		break;

	default:
		res = IE_E_INVALIDCLRFORMAT;
	}
	if (ieFailed(res)) return res;

	Frame = iePImage(pimSrc)->FrameParams();
	Frame.pimPrev = nullptr;
	Frame.pimNext = nullptr;
	Frame.pimRest = nullptr;

	if (bCopyAllFrames) {
		iePImage pimNext = const_cast<iePImage>(pimSrc)->FrameParams().pimNext;
		if (pimNext) Frame.pimNext = pimNext->ieImage::CreateCopy(true, pimNext->Draw(), pimNext->Text(), PixelFormat());
	}
	else {
		Frame.msDisplayTime = 0;
	}

	return res;
}