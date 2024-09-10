////////////////////////////////////////////////////////////
/// /see WindowImpl::SetIcon
////////////////////////////////////////////////////////////
void WindowImplWin32::SetIcon(unsigned int Width, unsigned int Height, const Uint8* Pixels)
{
    // First destroy the previous one
    if (myIcon)
        DestroyIcon(myIcon);

    // Windows wants BGRA pixels : swap red and blue channels
    std::vector<Uint8> IconPixels(Width * Height * 4);
    for (std::size_t i = 0; i < IconPixels.size() / 4; ++i)
    {
        IconPixels[i * 4 + 0] = Pixels[i * 4 + 2];
        IconPixels[i * 4 + 1] = Pixels[i * 4 + 1];
        IconPixels[i * 4 + 2] = Pixels[i * 4 + 0];
        IconPixels[i * 4 + 3] = Pixels[i * 4 + 3];
    }

    // Create the icon from the pixels array
    myIcon = CreateIcon(GetModuleHandle(NULL), Width, Height, 1, 32, NULL, &IconPixels[0]);

    // Set it as both big and small icon of the window
    if (myIcon)
    {
        SendMessage(myHandle, WM_SETICON, ICON_BIG,   (LPARAM)myIcon);
        SendMessage(myHandle, WM_SETICON, ICON_SMALL, (LPARAM)myIcon);
    }
    else
    {
        std::cerr << "Failed to set the window's icon" << std::endl;
    }
}