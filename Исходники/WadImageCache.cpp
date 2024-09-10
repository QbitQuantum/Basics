std::string WadImageCache::image_to_new_name(SDL_Surface *image, int32 *filesize) const
{
	// create name
	boost::uuids::random_generator gen;
	boost::uuids::uuid u = gen();
	std::string ustr = boost::uuids::to_string(u);
	
	FileSpecifier File;
	File.SetToImageCacheDir();
	File.AddPart(ustr);
	
	FileSpecifier TempFile;
	TempFile.SetTempName(File);
	
	int ret;
//#if defined(HAVE_PNG) && defined(HAVE_SDL_IMAGE)
//	ret = aoIMG_SavePNG(TempFile.GetPath(), image, IMG_COMPRESS_DEFAULT, NULL, 0);
#ifdef HAVE_SDL_IMAGE
	ret = IMG_SavePNG(image, TempFile.GetPath());
#else
	ret = SDL_SaveBMP(image, TempFile.GetPath());
#endif
	if (ret == 0 && TempFile.Rename(File))
	{
		if (filesize)
		{
			OpenedFile of;
			if (File.Open(of))
				of.GetLength(*filesize);
		}
		return ustr;
	}
	
	if (filesize)
		*filesize = 0;
	return "";
}