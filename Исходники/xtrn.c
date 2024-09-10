static Image *ReadXTRNImage(const ImageInfo *image_info,
                            ExceptionInfo *exception)
{
    Image
    *image;

    ImageInfo
    *clone_info;

    void
    *param1,
    *param2,
    *param3;

    param1 = param2 = param3 = (void *) NULL;
    image = (Image *) NULL;
    clone_info=CloneImageInfo(image_info);
    if (clone_info->filename == NULL)
    {
        clone_info=DestroyImageInfo(clone_info);
        ThrowReaderException(FileOpenWarning,"No filename specified");
    }
    if (LocaleCompare(image_info->magick,"XTRNFILE") == 0)
    {
        image=ReadImage(clone_info,exception);
        CatchException(exception);
    }
    else if (LocaleCompare(image_info->magick,"XTRNIMAGE") == 0)
    {
        Image
        **image_ptr;

#ifdef ALL_IMAGEINFO
        ImageInfo
        **image_info_ptr;
#endif

        (void) sscanf(clone_info->filename,"%lx,%lx",&param1,&param2);
        image_ptr=(Image **) param2;
        if (*image_ptr != (Image *) NULL)
            image=CloneImage(*image_ptr,0,0,MagickFalse,exception);
#ifdef ALL_IMAGEINFO
        image_info_ptr=(ImageInfo **) param1;
        if (*image_info_ptr != (ImageInfo *) NULL)
            image_info=*image_info_ptr;
#endif
    }
    else if (LocaleCompare(image_info->magick,"XTRNBLOB") == 0)
    {
        char
        **blob_data;

        size_t
        *blob_length;

        char
        filename[MagickPathExtent];

        (void) sscanf(clone_info->filename,"%lx,%lx,%2048s",&param1,&param2,
                      filename);
        blob_data=(char **) param1;
        blob_length=(size_t *) param2;
        image=BlobToImage(clone_info,*blob_data,*blob_length,exception);
        CatchException(exception);
    }
    else if (LocaleCompare(image_info->magick,"XTRNARRAY") == 0)
    {
        char
        *blob_data,
        filename[MagickPathExtent];

        HRESULT
        hr;

        long
        lBoundl,
        lBoundu;

        SAFEARRAY
        *pSafeArray;

        size_t
        blob_length;

        *filename='\0';
        (void) sscanf(clone_info->filename,"%lx,%2048s",&param1,filename);
        hr=S_OK;
        pSafeArray=(SAFEARRAY *) param1;
        if (pSafeArray)
        {
            hr = SafeArrayGetLBound(pSafeArray, 1, &lBoundl);
            if (SUCCEEDED(hr))
            {
                hr = SafeArrayGetUBound(pSafeArray, 1, &lBoundu);
                if (SUCCEEDED(hr))
                {
                    blob_length = lBoundu - lBoundl + 1;
                    hr = SafeArrayAccessData(pSafeArray,(void**) &blob_data);
                    if(SUCCEEDED(hr))
                    {
                        *clone_info->filename='\0';
                        *clone_info->magick='\0';
                        if (*filename != '\0')
                            (void) CopyMagickString(clone_info->filename,filename,
                                                    MagickPathExtent);
                        image=BlobToImage(clone_info,blob_data,blob_length,
                                          exception);
                        hr=SafeArrayUnaccessData(pSafeArray);
                        CatchException(exception);
                    }
                }
            }
        }
    }
    clone_info=DestroyImageInfo(clone_info);
    return(image);
}