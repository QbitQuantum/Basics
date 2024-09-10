PictureManager::PictureManager(void)
{
    GdiplusStartupInput input;
    GdiplusStartup(&gdiToken_, &input, nullptr);
}