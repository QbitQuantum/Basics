QJsonObject JsonSaver::saveRectU(const utils::RectU& rect)
{
    QJsonObject res;
    res.insert("size", saveSizeU(rect.size()));
    res.insert("topleft", savePointU(rect.topLeft()));
    return res;
}