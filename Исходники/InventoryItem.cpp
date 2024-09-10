//------------------------------------------------------------------------------//
void InventoryItem::populateGeometryBuffer()
{
    if (!isUserStringDefined("BlockImage"))
        return;

    const Image* img = PropertyHelper<Image*>::fromString(getUserString("BlockImage"));

    if (!img)
        return;

    const Sizef square_size(squarePixelSize());

    argb_t colour = 0xFF00FF00;

    if (d_dragging && !currentDropTargetIsValid())
        colour = 0xFFFF0000;

    for (int y = 0; y < d_content.height(); ++y)
    {
        for (int x = 0; x < d_content.width(); ++x)
        {
            if (d_content.elementAtLocation(x, y))
            {
                img->render(d_geometryBuffers,
                            glm::vec2(x * square_size.d_width + 1, y * square_size.d_height + 1),
                            Sizef(square_size.d_width - 2, square_size.d_height - 2), 0, false,
                            ColourRect(colour));
            }
        }
    }
}