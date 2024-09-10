BOOL MacWidgetPainter::DrawProgressbar(const OpRect &drawrect, double percent, INT32 progress_when_total_unknown, OpWidgetString* string, const char *skin_empty, const char *skin_full)
{
	const char *full_skin  = skin_full && *skin_full ? skin_full : "Progress Full Skin";

	OpSkinElement *border_skin = g_skin_manager->GetSkinElement(full_skin);
	if(!g_skin_manager->GetCurrentSkin() || !border_skin || !border_skin->IsNative())
	{
		return IndpWidgetPainter::DrawProgressbar(drawrect, percent, progress_when_total_unknown, string, skin_empty, skin_full);
	}

	UINT32 full_color = g_op_ui_info->GetUICSSColor(CSS_VALUE_HighlightText);

	g_skin_manager->GetTextColor(full_skin, &full_color);
		
	CGRect r = {{0, 0}, {drawrect.width, drawrect.height}};
	
	CGContextRef context;
	OpBitmap* bitmap = NULL;

	int bmpwidth = drawrect.width;
	int bmpheight = drawrect.height;
#ifdef PIXEL_SCALE_RENDERING_SUPPORT
	const PixelScaler& scaler = vd->GetVPScale();
	bmpwidth = TO_DEVICE_PIXEL(scaler, bmpwidth);
	bmpheight = TO_DEVICE_PIXEL(scaler, bmpheight);
#endif // PIXEL_SCALE_RENDERING_SUPPORT

	if(OpStatus::IsSuccess(OpBitmap::Create(&bitmap, bmpwidth, bmpheight, FALSE, TRUE, 0, 0, TRUE)))
	{
		int w = bitmap->Width();
		int h = bitmap->Height();
		int bpl = bitmap->GetBytesPerLine();
		void *image_data = bitmap->GetPointer(OpBitmap::ACCESS_WRITEONLY);
		if (!image_data)
		{
			delete bitmap;
			return FALSE;
		}
		memset(image_data, 0, bpl*h);
		CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
		CGBitmapInfo alpha = kCGBitmapByteOrderVegaInternal;
		context = CGBitmapContextCreate(image_data, w, h, 8, bpl, colorSpace, alpha);
		CGColorSpaceRelease(colorSpace);
		int win_height = drawrect.height;

		float scale = 1.0f;
#ifdef PIXEL_SCALE_RENDERING_SUPPORT
		scale = TO_DEVICE_PIXEL(scaler, scale);
#endif // PIXEL_SCALE_RENDERING_SUPPORT
		CGContextScaleCTM(context, scale, -scale);
		CGContextTranslateCTM(context, 0.0, -win_height);

		if (percent == 0 && progress_when_total_unknown)
		{
			HIThemeTrackDrawInfo drawInfo;
			
			SInt32 thickness = 0;
			SInt32 shadow = 0;
			if	(noErr == GetThemeMetric(kThemeMetricLargeProgressBarThickness, &thickness) &&
				(noErr == GetThemeMetric(kThemeMetricProgressBarShadowOutset, &shadow)))
			{
				SInt32 progressHeight = thickness + shadow;
				
				if((r.size.height) > progressHeight)
				{
					float f = (r.size.height - progressHeight); // / 2;
					r.origin.y += f;
					r.size.height -= f;
				}
			}
			else
			{
				float f = (r.size.height / 4) - 1;
				r.origin.y += f;
				r.size.height -= f;
			}

			drawInfo.version = 0;
			drawInfo.kind = kThemeIndeterminateBarLarge;
			drawInfo.bounds = r;
			drawInfo.min = 0;
			drawInfo.max = 100;
			drawInfo.value = 0;
			drawInfo.attributes = kThemeTrackHorizontal;
			drawInfo.enableState = widget->IsEnabled() ? kThemeTrackActive : kThemeTrackInactive;
			drawInfo.trackInfo.progress.phase = progress_when_total_unknown;
			
			HIThemeDrawTrack(&drawInfo, NULL, context, kHIThemeOrientationNormal);		
		}
		else
		{
			HIThemeTrackDrawInfo drawInfo;
			
			SInt32 thickness = 0;
			SInt32 shadow = 0;
			if	(noErr == GetThemeMetric(kThemeMetricLargeProgressBarThickness, &thickness) &&
				(noErr == GetThemeMetric(kThemeMetricProgressBarShadowOutset, &shadow)))
			{
				SInt32 progressHeight = thickness + shadow;
				
				if((r.size.height) > progressHeight)
				{
					float f = (r.size.height - progressHeight); // / 2;
					r.origin.y += f;
					r.size.height -= f;
				}
			}
			else
			{
				float f = (r.size.height / 4) - 1;
				r.origin.y += f;
				r.size.height -= f;
			}

			drawInfo.version = 0;
			drawInfo.kind = kThemeProgressBarLarge;
			drawInfo.bounds = r;
			drawInfo.min = 0;
			drawInfo.max = 100;
			drawInfo.value = (SInt32)(percent);
			drawInfo.attributes = kThemeTrackHorizontal;
			drawInfo.enableState = widget->IsEnabled() ? kThemeTrackActive : kThemeTrackInactive;
			drawInfo.trackInfo.progress.phase = floorf(GetCurrentEventTime()*16);
			
			HIThemeDrawTrack(&drawInfo, NULL, context, kHIThemeOrientationNormal);
		}
		
		CGContextRelease(context);
		bitmap->ReleasePointer();
		vd->BitmapOut(bitmap, OpRect(0, 0, bitmap->Width(), bitmap->Height()), drawrect);
		delete bitmap;
	}
	
	if (string)
	{
		widget->SetClipRect(drawrect);
		OpRect textRect = drawrect;
		textRect.y -= 1;
		string->Draw(textRect, vd, full_color);
		widget->RemoveClipRect();
	}
	
	return TRUE;
}