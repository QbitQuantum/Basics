void SPAvoidRef::handleSettingChange(void)
{
    SPDesktop *desktop = inkscape_active_desktop();
    if (desktop == NULL) {
        return;
    }
    if (sp_desktop_document(desktop) != item->document) {
        // We don't want to go any further if the active desktop's document
        // isn't the same as the document that this item is part of.  This
        // case can happen if a new document is loaded from the file chooser
        // or via the recent file menu.  In this case, we can end up here
        // as a rersult of a ensureUpToDate performed on a
        // document not yet attached to the active desktop.
        return;
    }

    if (new_setting == setting) {
        // Don't need to make any changes
        return;
    }
    setting = new_setting;

    Router *router = item->document->router;

    _transformed_connection.disconnect();
    if (new_setting) {
        Avoid::Polygon poly = avoid_item_poly(item);
        if (poly.size() > 0) {
            _transformed_connection = item->connectTransformed(
                    sigc::ptr_fun(&avoid_item_move));

            char const *id = item->getAttribute("id");
            g_assert(id != NULL);

            // Get a unique ID for the item.
            GQuark itemID = g_quark_from_string(id);

            shapeRef = new Avoid::ShapeRef(router, poly, itemID);

            router->addShape(shapeRef);
        }
    }
    else
    {
        g_assert(shapeRef);

        // Deleting the shapeRef will remove it completely from 
        // an existing Router instance.
        delete shapeRef;
        shapeRef = NULL;
    }
}