// Creates new GdiplusImage from logical to device units
unique_ptr<VsUI::GdiplusImage> CDpiHelper::CreateDeviceFromLogicalImage(_In_ VsUI::GdiplusImage* pImage, ImageScalingMode scalingMode, Color clrBackground)
{
    IfNullAssertRetNull(pImage, "No image given to convert");

    // Get the original/logical bitmap
    Bitmap* pBitmap = pImage->GetBitmap();
    IfNullAssertRetNull(pBitmap, "No image given to convert");
    
    // Create a memory image scaled for size
    int deviceWidth = LogicalToDeviceUnitsX(pBitmap->GetWidth());
    int deviceHeight = LogicalToDeviceUnitsY(pBitmap->GetHeight());
    
    unique_ptr<VsUI::GdiplusImage> pDeviceImage(new VsUI::GdiplusImage());
    pDeviceImage->Create( deviceWidth, deviceHeight, pBitmap->GetPixelFormat() );
       
    if (!pDeviceImage->IsLoaded())
    {
        VSFAIL("Failed to create scaled image, out of memory?");
        return nullptr;
    }
    
    // Get a Graphics object for the device image on which we can paint 
    unique_ptr<Graphics> pGraphics(pDeviceImage->GetGraphics());
    if (pGraphics.get() == nullptr)
    {
        VSFAIL("Failed to obtain image Graphics");
        return nullptr;
    }
    
    // Set the interpolation mode. 
    InterpolationMode interpolationMode = GetInterpolationMode(scalingMode);
    pGraphics->SetInterpolationMode(interpolationMode);
    
    // Clear the background (used when scaling mode is not nearest neighbor)
    pGraphics->Clear(clrBackground);
    
    // Calculate the destination rectangle: full available space, except when keeping the image unscaled and just adding a border
    RectF rectD(0, 0, (float)deviceWidth, (float)deviceHeight);
    if (scalingMode == ImageScalingMode::BorderOnly || (scalingMode == ImageScalingMode::Default && m_PreferredScalingMode == ImageScalingMode::BorderOnly))
    {
        rectD = RectF(0, 0, (float)pBitmap->GetWidth(), (float)pBitmap->GetHeight());
        rectD.Offset( (float)((deviceWidth - pBitmap->GetWidth()) / 2),  (float)((deviceHeight - pBitmap->GetHeight())/ 2) );
    }

    // Define the source rectangle
    RectF rectS(0, 0, (float)pBitmap->GetWidth(), (float)pBitmap->GetHeight());
   
    // Specify a source rectangle shifted by half of pixel to account for GDI+ considering the source origin the center of top-left pixel
    // Failing to do so will result in the right and bottom of the bitmap lines being interpolated with the graphics' background color,
    // and will appear black even if we cleared the background with transparent color. 
    // The apparition of these artifacts depends on the interpolation mode, on the dpi scaling factor, etc.
    // E.g. at 150% DPI, Bicubic produces them and NearestNeighbor is fine, but at 200% DPI NearestNeighbor also shows them.
    // Many articles on the web talk about this problem, e.g. http://www.codeproject.com/Articles/14884/BorderBug
    rectS.Offset(-0.5f, -0.5f);
    
    // Draw the scaled bitmap in the device image
    pGraphics->DrawImage(pBitmap, rectD, rectS.X, rectS.Y, rectS.Width, rectS.Height, UnitPixel);
    
    // Return the new image
    return pDeviceImage;
}