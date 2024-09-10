static bool decodeDataObject(ArgumentDecoder& decoder, RefPtr<DataObjectGtk>& dataObject)
{
    RefPtr<DataObjectGtk> data = DataObjectGtk::create();

    bool hasText;
    if (!decoder.decode(hasText))
        return false;
    if (hasText) {
        String text;
        if (!decoder.decode(text))
            return false;
        data->setText(text);
    }

    bool hasMarkup;
    if (!decoder.decode(hasMarkup))
        return false;
    if (hasMarkup) {
        String markup;
        if (!decoder.decode(markup))
            return false;
        data->setMarkup(markup);
    }

    bool hasURL;
    if (!decoder.decode(hasURL))
        return false;
    if (hasURL) {
        String url;
        if (!decoder.decode(url))
            return false;
        data->setURL(URL(URL(), url), String());
    }

    bool hasURIList;
    if (!decoder.decode(hasURIList))
        return false;
    if (hasURIList) {
        String uriList;
        if (!decoder.decode(uriList))
            return false;
        data->setURIList(uriList);
    }

    bool hasImage;
    if (!decoder.decode(hasImage))
        return false;
    if (hasImage) {
        GRefPtr<GdkPixbuf> image;
        if (!decodeImage(decoder, image))
            return false;
        data->setImage(image.get());
    }

    bool hasUnknownTypeData;
    if (!decoder.decode(hasUnknownTypeData))
        return false;
    if (hasUnknownTypeData) {
        HashMap<String, String> unknownTypes;
        if (!decoder.decode(unknownTypes))
            return false;

        auto end = unknownTypes.end();
        for (auto it = unknownTypes.begin(); it != end; ++it)
            data->setUnknownTypeData(it->key, it->value);
    }

    dataObject = data;

    return true;
}