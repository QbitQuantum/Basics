void Gosu::applyBorderFlags(Bitmap& dest, const Bitmap& source,
    unsigned srcX, unsigned srcY, unsigned srcWidth, unsigned srcHeight,
    unsigned imageFlags)
{
    dest.resize(srcWidth + 2, srcHeight + 2);

    // The borders are made "harder" by duplicating the original bitmap's
    // borders.

    // Top.
    if (imageFlags & ifTileableTop)
        dest.insert(source, 1, 0, srcX, srcY, srcWidth, 1);
    // Bottom.
    if (imageFlags & ifTileableBottom)
        dest.insert(source, 1, dest.height() - 1,
            srcX, srcY + srcHeight - 1, srcWidth, 1);
    // Left.
    if (imageFlags & ifTileableLeft)
        dest.insert(source, 0, 1, srcX, srcY, 1, srcHeight);
    // Right.
    if (imageFlags & ifTileableRight)
        dest.insert(source, dest.width() - 1, 1, 
            srcX + srcWidth - 1, srcY, 1, srcHeight);

    // Top left.
    if ((imageFlags & ifTileableTop) && (imageFlags & ifTileableLeft))
        dest.setPixel(0, 0,
            source.getPixel(srcX, srcY));
    // Top right.
    if ((imageFlags & ifTileableTop) && (imageFlags & ifTileableRight))
        dest.setPixel(dest.width() - 1, 0,
            source.getPixel(srcX + srcWidth - 1, srcY));
    // Bottom left.
    if ((imageFlags & ifTileableBottom) && (imageFlags & ifTileableLeft))
        dest.setPixel(0, dest.height() - 1,
            source.getPixel(srcX, srcY + srcHeight - 1));
    // Bottom right.
    if ((imageFlags & ifTileableBottom) && (imageFlags & ifTileableRight))
        dest.setPixel(dest.width() - 1, dest.height() - 1,
            source.getPixel(srcX + srcWidth - 1, srcY + srcHeight - 1));

    // Now put the final image into the prepared borders.
    dest.insert(source, 1, 1, srcX, srcY, srcWidth, srcHeight);
}