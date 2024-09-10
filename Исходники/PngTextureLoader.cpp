//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
bool PngTextureLoader::Load(void* data, int32_t size, bool rev)
{
#if __PNG_DDI
	auto global = GlobalAlloc(GMEM_MOVEABLE,size);
	auto buf = GlobalLock(global);
	CopyMemory(buf, data, size);
	GlobalUnlock(global);
	LPSTREAM stream = NULL;
	CreateStreamOnHGlobal( global, false, &stream);
	Gdiplus::Bitmap* bmp = Gdiplus::Bitmap::FromStream(stream);
	ES_SAFE_RELEASE(stream);
	GlobalFree(global);


	if( bmp != NULL && bmp->GetLastStatus() == Gdiplus::Ok )
	{
		textureWidth = bmp->GetWidth();
		textureHeight = bmp->GetHeight();
		textureData.resize(textureWidth * textureHeight * 4);

		if(rev)
		{
			for(auto y = 0; y < textureHeight; y++ )
			{
				for(auto x = 0; x < textureWidth; x++ )
				{
					Gdiplus::Color  color;
					bmp->GetPixel(x, textureHeight - y - 1, &color);

					textureData[(x + y * textureWidth) * 4 + 0] = color.GetR();
					textureData[(x + y * textureWidth) * 4 + 1] = color.GetG();
					textureData[(x + y * textureWidth) * 4 + 2] = color.GetB();
					textureData[(x + y * textureWidth) * 4 + 3] = color.GetA();
				}
			}
		}
		else
		{
			for(auto y = 0; y < textureHeight; y++ )
			{
				for(auto x = 0; x < textureWidth; x++ )
				{
					Gdiplus::Color  color;
					bmp->GetPixel(x, y, &color);

					textureData[(x + y * textureWidth) * 4 + 0] = color.GetR();
					textureData[(x + y * textureWidth) * 4 + 1] = color.GetG();
					textureData[(x + y * textureWidth) * 4 + 2] = color.GetB();
					textureData[(x + y * textureWidth) * 4 + 3] = color.GetA();
				}
			}
		}
		
		return true;
	}
	else
	{
		ES_SAFE_DELETE(bmp);
		return false;
	}
#else
	uint8_t* data_ = (uint8_t*) data;

	/* pngアクセス構造体を作成 */
	png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	
	/* リードコールバック関数指定 */
	png_set_read_fn(png, &data_, &PngReadData);

	/* png画像情報構造体を作成 */
	png_infop png_info = png_create_info_struct(png);

	/* エラーハンドリング */
	if (setjmp(png_jmpbuf(png)))
	{
		png_destroy_read_struct(&png, &png_info, NULL);
		return false;
	}

	/* IHDRチャンク情報を取得 */
	png_read_info(png, png_info);
	png_uint_32 width, height;
	int bit_depth, color_type, interlace_type, comp_type, filter_type;
	png_get_IHDR(png, png_info, &width, &height, &bit_depth, &color_type, &interlace_type,
				 &comp_type, &filter_type);

	/* RGBA8888フォーマットに変換する */
	if (bit_depth < 8)
	{
		png_set_packing(png);
	}
	else if (bit_depth == 16)
	{
		png_set_strip_16(png);
	}

	uint32_t pixelBytes = 4;
	switch (color_type)
	{
	case PNG_COLOR_TYPE_PALETTE:
		png_set_palette_to_rgb(png);
		pixelBytes = 4;
		break;
	case PNG_COLOR_TYPE_GRAY:
		png_set_expand_gray_1_2_4_to_8(png);
		pixelBytes = 3;
		break;
	case PNG_COLOR_TYPE_RGB:
		pixelBytes = 3;
		break;
	case PNG_COLOR_TYPE_RGBA:
		break;
	}

	uint8_t* image = new uint8_t[width * height * pixelBytes];
	uint32_t pitch = width * pixelBytes;

	/* イメージデータを読み込む */

	textureWidth = width;
	textureHeight = height;
	textureData.resize(textureWidth * textureHeight * 4);

	if (rev)
	{
		for (uint32_t i = 0; i < height; i++)
		{
			png_read_row(png, &image[(height - 1 - i) * pitch], NULL);
		}
	}
	else
	{
		for (uint32_t i = 0; i < height; i++)
		{
			png_read_row(png, &image[i * pitch], NULL);
		}
	}

	if (pixelBytes == 4)
	{
		memcpy(textureData.data(), image, width * height * pixelBytes);
	}
	else
	{
		for (int32_t y = 0; y < height; y++)
		{
			for (int32_t x = 0; x < width; x++)
			{
				int32_t src = (x + y * width) * 3;
				int32_t dst = (x + y * width) * 4;
				textureData[dst + 0] = image[src + 0];
				textureData[dst + 1] = image[src + 1];
				textureData[dst + 2] = image[src + 2];
				textureData[dst + 3] = 255;
			}
		}
	}
	
	delete [] image;
	png_destroy_read_struct(&png, &png_info, NULL);

	return true;
#endif
}