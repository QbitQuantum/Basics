void Widget::setCursor(Cursor const& cursor)
{
    ScrollView* theRoot = root();
    if (!theRoot)
        return;
    PlatformPageClient pageClient = theRoot->hostWindow()->platformPageClient();

    if (pageClient)
        pageClient->setCursor(cursor.impl());
}