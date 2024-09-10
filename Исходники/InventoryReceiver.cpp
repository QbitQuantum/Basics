//------------------------------------------------------------------------------//
void InventoryReceiver::populateGeometryBuffer()
{
    if (!isUserStringDefined("BlockImage"))
        return;

    const Image* img = PropertyHelper<Image*>::fromString(getUserString("BlockImage"));

    if (!img)
        return;

    const Sizef square_size(squarePixelSize());

    for (int y = 0; y < d_content.height(); ++y)
    {
        for (int x = 0; x < d_content.width(); ++x)
        {
            argb_t colour = 0xFFFFFFFF;
            if (d_content.elementAtLocation(x, y))
                colour = 0xFF0000FF;

            img->render(*d_geometry,
                        Vector2f(x * square_size.d_width + 1, y * square_size.d_height + 1),
                        Sizef(square_size.d_width - 2, square_size.d_height - 2), 0,
                        ColourRect(colour));
        }
    }
}