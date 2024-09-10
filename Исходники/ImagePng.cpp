BOOL CImagePng::LoadImagePng(char *szPngName)
{
	try
	{
		if (szPngName == NULL||strlen(szPngName) >= sizeof(m_szPngName))
			return FALSE;

		FILE* file = NULL;
		HDC hDC  = NULL;
		png_structp png_ptr = NULL;
		png_infop info_ptr = NULL;

		do 
		{
			file = fopen(szPngName,"rb");
			if (file == NULL)
				break;

			hDC =  ::CreateCompatibleDC(NULL);
			if (hDC == NULL)
				break;

			png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);
			if (png_ptr == NULL)
				break;

			info_ptr = png_create_info_struct(png_ptr);
			if (info_ptr == NULL)
				break;

			setjmp(png_jmpbuf(png_ptr));

			png_init_io(png_ptr, file);

			// 读文件
			png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_EXPAND, 0);

			// 得到文件的宽高色深
			int width = png_get_image_width(png_ptr,info_ptr);
			int height = png_get_image_height(png_ptr, info_ptr);

			int color_type = png_get_color_type(png_ptr, info_ptr);

			// 申请内存
			int size = height*width*4;

			// row_pointers里边就是rgba数据
			png_bytep* row_pointers = png_get_rows(png_ptr, info_ptr);
			if (row_pointers == NULL)
				break;

			BITMAPINFO bmi;

			memset(&bmi, 0, sizeof(bmi));

			bmi.bmiHeader.biSize = sizeof(BITMAPINFO);

			bmi.bmiHeader.biWidth = width;

			bmi.bmiHeader.biHeight = height;

			bmi.bmiHeader.biPlanes = 1;

			bmi.bmiHeader.biBitCount = 32;

			bmi.bmiHeader.biCompression = BI_RGB;

			bmi.bmiHeader.biSizeImage = size;

			unsigned char* bgra = NULL;

			m_hBmp = CreateDIBSection(hDC, &bmi, DIB_RGB_COLORS,(void**)&bgra,NULL,0);
			if (m_hBmp == NULL)
				break;

			int pos = 0;
			int nAlpha = 0;

			for(int i = 0; i < height; i++)
			{
				for(int j = 0; j < (4 * width); j += 4)
				{
					nAlpha = row_pointers[height-i-1][j + 3]; 
					bgra[pos++] = (row_pointers[height-i-1][j + 2]*nAlpha+127)/255; // blue
					bgra[pos++] = (row_pointers[height-i-1][j + 1]*nAlpha+127)/255; // green
					bgra[pos++] = (row_pointers[height-i-1][j]*nAlpha+127)/255;        // red
					bgra[pos++] = row_pointers[height-i-1][j + 3];              // alpha
				}
			}

			::DeleteDC(hDC);

			png_destroy_read_struct(&png_ptr, &info_ptr, 0);

			fclose(file);

			m_nWidth = width;
			m_nHeight = height;

			return TRUE;

		} while (FALSE);

		if (file != NULL)
		{
			fclose(file);
			file = NULL;
		}

		if (hDC != NULL)
		{
			::DeleteDC(hDC);
			hDC = NULL;
		}

		if (m_hBmp != NULL)
		{
			::DeleteObject(m_hBmp);
			m_hBmp = NULL;
		}

		if (png_ptr != NULL||info_ptr != NULL)
		{
			png_destroy_read_struct(&png_ptr, &info_ptr, 0);
			png_ptr = NULL;
			info_ptr = NULL;
		}

		return FALSE;
	}
	catch(...)
	{

	}
	return FALSE;
}