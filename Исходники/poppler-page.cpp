/**
 Search the page for some text.

 \param text the text to search
 \param[in,out] r the area where to start search, which will be set to the area
                  of the match (if any)
 \param direction in which direction search for text
 \param case_sensitivity whether search in a case sensitive way
 \param rotation the rotation assumed for the page
 */
bool page::search(const ustring &text, rectf &r, search_direction_enum direction,
                  case_sensitivity_enum case_sensitivity, rotation_enum rotation) const
{
    const size_t len = text.length();
    std::vector<Unicode> u(len);
    for (size_t i = 0; i < len; ++i) {
        u[i] = text[i];
    }

    const GBool sCase = case_sensitivity == case_sensitive ? gTrue : gFalse;
    const int rotation_value = (int)rotation * 90;

    bool found = false;
    double rect_left = r.left();
    double rect_top = r.top();
    double rect_right = r.right();
    double rect_bottom = r.bottom();

    TextOutputDev td(NULL, gTrue, 0, gFalse, gFalse);
    d->doc->doc->displayPage(&td, d->index + 1, 72, 72, rotation_value, false, true, false);
    TextPage *text_page = td.takeText();

    switch (direction) {
    case search_from_top:
        found = text_page->findText(&u[0], len,
                    gTrue, gTrue, gFalse, gFalse, sCase, gFalse, gFalse,
                    &rect_left, &rect_top, &rect_right, &rect_bottom);
        break;
    case search_next_result:
        found = text_page->findText(&u[0], len,
                    gFalse, gTrue, gTrue, gFalse, sCase, gFalse, gFalse,
                    &rect_left, &rect_top, &rect_right, &rect_bottom);
        break;
    case search_previous_result:
        found = text_page->findText(&u[0], len,
                    gFalse, gTrue, gTrue, gFalse, sCase, gTrue, gFalse,
                    &rect_left, &rect_top, &rect_right, &rect_bottom);
        break;
    }

    text_page->decRefCnt();
    r.set_left(rect_left);
    r.set_top(rect_top);
    r.set_right(rect_right);
    r.set_bottom(rect_bottom);

    return found;
}