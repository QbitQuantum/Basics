	void VDVideoFilterShowInfo::Run() {
		const VDXFBitmap& dst = *fa->mpOutputFrames[0];
		const VDXPixmap& pxdst = *dst.mpPixmap;

		const float size = 8.0f * 8.0f * 20.0f;

		VDPixmap pxdst2;
		pxdst2.data = pxdst.data;
		pxdst2.data2 = pxdst.data2;
		pxdst2.data3 = pxdst.data3;
		pxdst2.pitch = pxdst.pitch;
		pxdst2.pitch2 = pxdst.pitch2;
		pxdst2.pitch3 = pxdst.pitch3;
		pxdst2.format = pxdst.format;
		pxdst2.w = pxdst.w;
		pxdst2.h = pxdst.h;
		pxdst2.palette = pxdst.palette;

		float y = 20.0f;

		for(int lines=0; lines<3; ++lines) {
			switch(lines) {
			case 0:
				mTextLine.sprintf("Source frame: %d (%.3fs)", (int)fa->pfsi->lCurrentSourceFrame, (double)fa->pfsi->lSourceFrameMS / 1000.0);
				break;
			case 1:
				mTextLine.sprintf("Output frame: %d", (int)fa->pfsi->mOutputFrame);
				break;
			case 2:
				mTextLine.sprintf("Sequence frame: %d (%.3fs)", (int)fa->pfsi->lCurrentFrame, (double)fa->pfsi->lDestFrameMS / 1000.0);
				break;
			}

			mRasterizer.Clear();
			VDPixmapConvertTextToPath(mRasterizer, NULL, size, 8.0f * 8.0f * 10.0f, 8.0f * 8.0f * y, mTextLine.c_str());		
			mRasterizer.ScanConvert(mTextRegion);
			VDPixmapConvolveRegion(mShadowRegion, mTextRegion, mShadowBrush);
			VDPixmapFillRegionAntialiased8x(pxdst2, mShadowRegion, 0, 0, 0xFF000000);
			VDPixmapFillRegionAntialiased8x(pxdst2, mTextRegion, 0, 0, 0xFFFFFF00);

			y += 20.0f;
		}
	}