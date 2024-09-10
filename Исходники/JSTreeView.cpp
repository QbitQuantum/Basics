JSBool
JSTreeView::setPropertySwitch(NATIVE & theNative, unsigned long theID,
        JSContext *cx, JSObject *obj, jsval id, jsval *vp)
{
    switch (theID) {
        case PROP_selected_row:
            try {
                Glib::RefPtr<Gtk::TreeSelection> refTreeSelection = theNative.get_selection();
                asl::Ptr<Gtk::TreeIter> myRow;
                convertFrom(cx, *vp, myRow);
                refTreeSelection->select(*myRow);
                return JS_TRUE;
            } HANDLE_CPP_EXCEPTION;
        case PROP_headers_visible:
            try {
                bool theFlag;
                convertFrom(cx, *vp, theFlag);
                theNative.set_headers_visible(theFlag);
                return JS_TRUE;
            } HANDLE_CPP_EXCEPTION;
        case PROP_selected_row_values:
            try {
                Glib::RefPtr<Gtk::TreeSelection> refTreeSelection = theNative.get_selection();
                Gtk::TreeModel::iterator iter = refTreeSelection->get_selected();
                if (iter) {
                    vector<Glib::ustring> myStrings;
                    convertFrom(cx, *vp, myStrings);

                    unsigned int myColCount = theNative.get_model()->get_n_columns();
                    if (myColCount != myStrings.size()+1) {
                        JS_ReportError(cx,"selected_row_values: expected %d strings, got %d",
                                myColCount-1, myStrings.size());
                        return JS_FALSE;
                    }
                    for (unsigned int i=1; i < myColCount; ++i) {
                        iter->set_value(i, myStrings[i-1]);
                    }
                }
                return JS_TRUE;
            } HANDLE_CPP_EXCEPTION;
        default:
            return JSBASE::setPropertySwitch(theNative, theID, cx, obj, id, vp);
    }
}