bool ImageSplitter::SplitImage(const FilePath &pathname, Set<String> &errorLog)
{
    Image *loadedImage = CreateTopLevelImage(pathname);
    if(!loadedImage)
    {
        errorLog.insert(String(Format("Can't load image %s", pathname.GetAbsolutePathname().c_str())));
        return false;
    }
    
    if(loadedImage->GetPixelFormat() != FORMAT_RGBA8888)
    {
        errorLog.insert(String(Format("Incorrect image format %s. Must be RGBA8888", Texture::GetPixelFormatString(loadedImage->GetPixelFormat()))));
        return false;
    }
    

    Image *red = Image::Create(loadedImage->width, loadedImage->height, FORMAT_A8);
    Image *green = Image::Create(loadedImage->width, loadedImage->height, FORMAT_A8);
    Image *blue = Image::Create(loadedImage->width, loadedImage->height, FORMAT_A8);
    Image *alpha = Image::Create(loadedImage->width, loadedImage->height, FORMAT_A8);

    int32 size = loadedImage->width * loadedImage->height;
    int32 pixelSize = Texture::GetPixelFormatSizeInBytes(FORMAT_RGBA8888);
    for(int32 i = 0; i < size; ++i)
    {
        int32 offset = i * pixelSize;
        red->data[i] = loadedImage->data[offset];
        green->data[i] = loadedImage->data[offset + 1];
        blue->data[i] = loadedImage->data[offset + 2];
        alpha->data[i] = loadedImage->data[offset + 3];
    }
    
    FilePath folder(pathname.GetDirectory());
    
    SaveImage(red, folder + "r.png");
    SaveImage(green, folder + "g.png");
    SaveImage(blue, folder + "b.png");
    SaveImage(alpha, folder + "a.png");


    ReleaseImages(red, green, blue, alpha);
    SafeRelease(loadedImage);
    return true;
}