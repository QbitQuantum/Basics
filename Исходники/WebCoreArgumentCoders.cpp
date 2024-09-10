bool ArgumentCoder<Cursor>::decode(ArgumentDecoder& decoder, Cursor& cursor)
{
    Cursor::Type type;
    if (!decoder.decodeEnum(type))
        return false;

    if (type > Cursor::Custom)
        return false;

    if (type != Cursor::Custom) {
        const Cursor& cursorReference = Cursor::fromType(type);
        // Calling platformCursor here will eagerly create the platform cursor for the cursor singletons inside WebCore.
        // This will avoid having to re-create the platform cursors over and over.
        (void)cursorReference.platformCursor();

        cursor = cursorReference;
        return true;
    }

    bool isValidImagePresent;
    if (!decoder.decode(isValidImagePresent))
        return false;

    if (!isValidImagePresent) {
        cursor = Cursor(Image::nullImage(), IntPoint());
        return true;
    }

    RefPtr<Image> image;
    if (!decodeImage(decoder, image))
        return false;

    IntPoint hotSpot;
    if (!decoder.decode(hotSpot))
        return false;

    if (!image->rect().contains(hotSpot))
        return false;

    cursor = Cursor(image.get(), hotSpot);
    return true;
}