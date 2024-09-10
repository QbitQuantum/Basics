void EditorTextureImportPlugin::compress_image(EditorExportPlatform::ImageCompression p_mode,Image& image,bool p_smaller) {


	switch(p_mode) {
		case EditorExportPlatform::IMAGE_COMPRESSION_NONE: {

			//do absolutely nothing

		} break;
		case EditorExportPlatform::IMAGE_COMPRESSION_INDEXED: {

			//quantize
			image.quantize();

		} break;
		case EditorExportPlatform::IMAGE_COMPRESSION_BC: {


			// for maximum compatibility, BC shall always use mipmaps and be PO2
			image.resize_to_po2();
			if (image.get_mipmaps()==0)
				image.generate_mipmaps();

			image.compress(Image::COMPRESS_BC);
			/*
			if (has_alpha) {

				if (flags&IMAGE_FLAG_ALPHA_BIT) {
					image.convert(Image::FORMAT_BC3);
				} else {
					image.convert(Image::FORMAT_BC2);
				}
			} else {

				image.convert(Image::FORMAT_BC1);
			}*/


		} break;
		case EditorExportPlatform::IMAGE_COMPRESSION_PVRTC:
		case EditorExportPlatform::IMAGE_COMPRESSION_PVRTC_SQUARE: {

			// for maximum compatibility (hi apple!), PVRT shall always
			// use mipmaps, be PO2 and square

			if (image.get_mipmaps()==0)
				image.generate_mipmaps();
			image.resize_to_po2(true);

			if (p_smaller) {

				image.compress(Image::COMPRESS_PVRTC2);
				//image.convert(has_alpha ? Image::FORMAT_PVRTC2_ALPHA : Image::FORMAT_PVRTC2);
			} else {
				image.compress(Image::COMPRESS_PVRTC4);
				//image.convert(has_alpha ? Image::FORMAT_PVRTC4_ALPHA : Image::FORMAT_PVRTC4);
			}

		} break;
		case EditorExportPlatform::IMAGE_COMPRESSION_ETC1: {

			image.resize_to_po2(); //square or not?
			if (image.get_mipmaps()==0)
				image.generate_mipmaps();
			if (!image.detect_alpha()) {
				//ETC1 is only opaque
				image.compress(Image::COMPRESS_ETC);
			}

		} break;
		case EditorExportPlatform::IMAGE_COMPRESSION_ETC2: {


		} break;
	}


}