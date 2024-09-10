Eina_List *
epdf_page_text_find (const Epdf_Page *page,
                     const char      *text,
                     unsigned char    is_case_sensitive)
{
    Epdf_Rectangle *match;
    TextOutputDev  *output_dev;
    Eina_List      *matches = NULL;
    double          xMin, yMin, xMax, yMax;
    int             length;
    int             height;


    if (!page || !text)
        return NULL;

    GooString tmp (text);
    Unicode *s;

    {
        length = tmp.getLength();
        s = (Unicode *)gmallocn(length, sizeof(Unicode));
        bool anyNonEncoded = false;
        for (int j = 0; j < length && !anyNonEncoded; ++j) {
            s[j] = pdfDocEncoding[tmp.getChar(j) & 0xff];
            if (!s[j]) anyNonEncoded = true;
        }
        if ( anyNonEncoded )
        {
            for (int j = 0; j < length; ++j) {
                s[j] = tmp.getChar(j);
            }
        }
    }

    length = strlen (text);

    output_dev = new TextOutputDev (NULL, 1, 0, 0);

    epdf_page_size_get (page, NULL, &height);
    page->page->display (output_dev, 72, 72, 0, false,
                         true, false,
                         page->doc->pdfdoc->getCatalog());

    xMin = 0;
    yMin = 0;
#warning you probably want to add backwards as parameters
    while (output_dev->findText (s, tmp.getLength (),
                                 0, 1, // startAtTop, stopAtBottom
                                 1, 0, // startAtLast, stopAtLast
                                 is_case_sensitive, 0, // caseSensitive, backwards
                                 &xMin, &yMin, &xMax, &yMax)) {
        match = (Epdf_Rectangle *)malloc (sizeof (Epdf_Rectangle));
        match->x1 = xMin;
        match->y1 = yMin;//height - yMax;
        match->x2 = xMax;
        match->y2 = yMax;//height - yMin;
        matches = eina_list_append (matches, match);
    }

    delete output_dev;

    return matches;
}