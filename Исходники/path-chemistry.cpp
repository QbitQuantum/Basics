void
sp_selected_path_break_apart(SPDesktop *desktop, bool skip_undo)
{
    Inkscape::Selection *selection = desktop->getSelection();

    if (selection->isEmpty()) {
        desktop->getMessageStack()->flash(Inkscape::WARNING_MESSAGE, _("Select <b>path(s)</b> to break apart."));
        return;
    }

    desktop->messageStack()->flash(Inkscape::IMMEDIATE_MESSAGE, _("Breaking apart paths..."));
    // set "busy" cursor
    desktop->setWaitingCursor();

    bool did = false;

    std::vector<SPItem*> itemlist(selection->itemList());
    for (std::vector<SPItem*>::const_iterator i = itemlist.begin(); i != itemlist.end(); ++i){

        SPItem *item = *i;

        SPPath *path = dynamic_cast<SPPath *>(item);
        if (!path) {
            continue;
        }

        SPCurve *curve = path->get_curve_for_edit();
        if (curve == NULL) {
            continue;
        }
        did = true;

        Inkscape::XML::Node *parent = item->getRepr()->parent();
        gint pos = item->getRepr()->position();
        char const *id = item->getRepr()->attribute("id");

        // XML Tree being used directly here while it shouldn't be...
        gchar *style = g_strdup(item->getRepr()->attribute("style"));
        // XML Tree being used directly here while it shouldn't be...
        gchar *path_effect = g_strdup(item->getRepr()->attribute("inkscape:path-effect"));
        Geom::Affine transform = path->transform;
        // it's going to resurrect as one of the pieces, so we delete without advertisement
        item->deleteObject(false);


        GSList *list = curve->split();

        curve->unref();

        std::vector<Inkscape::XML::Node*> reprs;
        for (GSList *l = list; l != NULL; l = l->next) {
            curve = (SPCurve *) l->data;

            Inkscape::XML::Node *repr = parent->document()->createElement("svg:path");
            repr->setAttribute("style", style);

            repr->setAttribute("inkscape:path-effect", path_effect);

            gchar *str = sp_svg_write_path(curve->get_pathvector());
            if (path_effect)
                repr->setAttribute("inkscape:original-d", str);
            else
                repr->setAttribute("d", str);
            g_free(str);
            repr->setAttribute("transform", sp_svg_transform_write(transform));
            
            // add the new repr to the parent
            parent->appendChild(repr);

            // move to the saved position
            repr->setPosition(pos > 0 ? pos : 0);

            // if it's the first one, restore id
            if (l == list)
                repr->setAttribute("id", id);

            reprs.push_back(repr);

            Inkscape::GC::release(repr);
        }
        selection->setReprList(reprs);

        g_slist_free(list);
        g_free(style);
        g_free(path_effect);
    }

    desktop->clearWaitingCursor();

    if (did) {
        if ( !skip_undo ) {
            DocumentUndo::done(desktop->getDocument(), SP_VERB_SELECTION_BREAK_APART, 
                               _("Break apart"));
        }
    } else {
        desktop->getMessageStack()->flash(Inkscape::ERROR_MESSAGE, _("<b>No path(s)</b> to break apart in the selection."));
    }
}