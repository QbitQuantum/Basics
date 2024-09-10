	inline Global::_BlipType SaveImageToFileFromDIB(unsigned char* data, int size, const std::wstring& file_name)//without ext
	{
		Global::_BlipType result = Global::msoblipERROR;

		CBgraFrame oFrame;
		int offset = 0, biSizeImage = 0;

		__BITMAPINFOHEADER * header = (__BITMAPINFOHEADER*)data;
		if (!header) return result;

		result = Global::msoblipDIB;

		if (header->biWidth > 100000 || header->biHeight > 100000 || header->biSize != 40)
		{
			__BITMAPCOREHEADER * header_core = (__BITMAPCOREHEADER *)data;
			if (header_core->bcSize != 12)
			{
				result = Global::msoblipWMF;
			}
			else
			{
				offset = 12; //sizeof(BITMAPCOREHEADER)			
			
				oFrame.put_Height	(header_core->bcHeight );
				oFrame.put_Width	(header_core->bcWidth );
				
				int sz_bitmap = header_core->bcHeight * header_core->bcWidth * header_core->bcBitCount/ 8;
				
				//if (header_core->bcWidth % 2 != 0 && sz_bitmap < size - offset)
				//	header_core->bcWidth++;
				///???? todooo непонятно .. в biff5 нужно флипать картинку, в biff8 не ясно ( - 
				
				int stride =  -(size - offset) / header_core->bcHeight;
				oFrame.put_Stride	(stride/*header_core->bcBitCount * header_core->bcWidth /8 */);

				biSizeImage = size - offset;
				
				if (-stride >= header_core->bcWidth && header_core->bcBitCount >=24 )
				{
					result = Global::msoblipPNG;
				}
			}
		}
		else
		{
			offset = 40; //sizeof(BITMAPINFOHEADER)

			oFrame.put_Height	(header->biHeight );
			oFrame.put_Width	(header->biWidth );
			
			int sz_bitmap = header->biHeight * header->biWidth * header->biBitCount/ 8;
			
			//if (header->biWidth % 2 != 0 && sz_bitmap < size -offset)
			//	header->biWidth++;
			
			int stride = -(size - offset) / header->biHeight;

			if (-stride >= header->biWidth && header->biBitCount >= 24)
			{
				result = Global::msoblipPNG;
			}
			oFrame.put_Stride	(stride/*header->biBitCount * header->biWidth /8*/);
			
			biSizeImage = header->biSizeImage > 0 ? header->biSizeImage : (size - offset);
		}
		
//------------------------------------------------------------------------------------------

		if (result == Global::msoblipPNG)
		{
			oFrame.put_Data((unsigned char*)data + offset);
			
            if (!oFrame.SaveFile(file_name + L".png", 4/*CXIMAGE_FORMAT_PNG*/))
				result = Global::msoblipERROR;

			oFrame.put_Data(NULL);
		}
		else if (result == Global::msoblipWMF)
		{
			NSFile::CFileBinary file;
            if (file.CreateFileW(file_name + L".wmf"))
			{
				file.WriteFile((BYTE*)data, size);
				file.CloseFile();
			}
		}
		else if (biSizeImage > 0)
		{
			NSFile::CFileBinary file;
            if (file.CreateFileW(file_name + L".bmp"))
			{
                _UINT16 vtType		= 0x4D42;				file.WriteFile((BYTE*)&vtType,	2);
                _UINT32 dwLen		= biSizeImage;			file.WriteFile((BYTE*)&dwLen,	4);
                _UINT32 dwRes		= 0;					file.WriteFile((BYTE*)&dwRes,	4);
                _UINT32 dwOffset	= 2;					file.WriteFile((BYTE*)&dwOffset, 4);
			
				file.WriteFile((BYTE*)data, size);
				file.CloseFile();
			}
		}
		return result;
	}