ImgurImageListViewItem::ImgurImageListViewItem(KPImagesListView* const view, const QUrl& url)
    : KPImagesListViewItem(view, url)
{
    const QColor blue = QColor (0, 0, 255);

    setTextColor(3, blue);
    setTextColor(4, blue);
}