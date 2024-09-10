		bool Pixmap::load(const char* chrFilePath)
		{
			DAnsiStr strExt = PS::FILESTRINGUTILS::ExtractFileExt(DAnsiStr(chrFilePath));
			if(strExt.toUpper() == "PNG") {
				std::vector<U8> image;
				U32 width, height;

				//decode
				U32 error = lodepng::decode(image, width, height, chrFilePath);
				if(error) {
					printf("decoder error %d : %s", error, lodepng_error_text(error));
					return false;
				}
				else {
					reset(width, height);
					memcpy(m_bitmap, &image[0], m_width * m_height * 4);
					return true;
				}
			}
			return false;
		}