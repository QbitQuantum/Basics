ImageObject::ImageObject(string FILENAME)
{
    imageSurface = NULL;
    processedSurface = NULL;
    visibility = true;
    ang = 0.0f;
    scale = 1.0f;
    ImageLoad(FILENAME);
}