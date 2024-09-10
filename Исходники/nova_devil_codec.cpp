void CDevILCodec::CodeToBuffer(CMemoryBuffer & out, const CImage &image,
							   ESaveFormats ext)
{
	ILuint imageid;
	CDevILFormats informat;
	informat.SetExFormat(image.GetPixelFormat());
	// Generate the main image name to use.
	ilGenImages(1, &imageid);

	// Bind this image name.
	ilBindImage(imageid);

	ilTexImage(image.GetWidth(), image.GetHeight(), image.GetDepth(), informat.GetInternalChannels(),
		informat.GetFormat(), IL_UNSIGNED_BYTE, image.GetBitsPtr());

	ILenum type = 0;
	switch(ext)
	{
	case SF_BMP:
		type = IL_BMP;
		break;
	case SF_ICO:
		type = IL_ICO;
		break;
	case SF_JPG:
		type = IL_JPG;
		break;
	case SF_PCX:
		type = IL_PCX;
		break;
	case SF_PIC:
		type = IL_PIC;
		break;
	case SF_PNG:
		type = IL_PNG;
		break;
	case SF_TGA:
		type = IL_TGA;
		break;
	case SF_TIF:
		type = IL_TIF;
		break;
	case SF_GIF:
		type = IL_GIF;
		break;
	case SF_DDS:
		type = IL_DDS;
		break;
	case SF_PIX:
		type = IL_PIX;
		break;
	case SF_HDR:
		type = IL_HDR;
		break;

	default:
		return;
	}

	out.AllocBuffer(image.GetSize()+0xff);
	ilSaveL(type, out.GetBegin(), out.GetBufferSize());

	ilDeleteImages(1, &imageid);

	ILenum Error = 0;
	if((Error = ilGetError()) != NULL)
	{
		nstring str("CDevILCodec::CodeToStream: ");
		str.append(iluErrorString(Error));
		throw NOVA_EXP(str.c_str(), BAD_OPERATION);
	}
}