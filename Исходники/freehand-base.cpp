void spdc_create_single_dot(ToolBase *ec, Geom::Point const &pt, char const *tool, guint event_state) {
    g_return_if_fail(!strcmp(tool, "/tools/freehand/pen") || !strcmp(tool, "/tools/freehand/pencil"));
    Glib::ustring tool_path = tool;

    SPDesktop *desktop = ec->desktop;
    Inkscape::XML::Document *xml_doc = desktop->doc()->getReprDoc();
    Inkscape::XML::Node *repr = xml_doc->createElement("svg:path");
    repr->setAttribute("sodipodi:type", "arc");
    SPItem *item = SP_ITEM(desktop->currentLayer()->appendChildRepr(repr));
    Inkscape::GC::release(repr);

    // apply the tool's current style
    sp_desktop_apply_style_tool(desktop, repr, tool, false);

    // find out stroke width (TODO: is there an easier way??)
    double stroke_width = 3.0;
    gchar const *style_str = repr->attribute("style");
    if (style_str) {
        SPStyle style(SP_ACTIVE_DOCUMENT);
        style.mergeString(style_str);
        stroke_width = style.stroke_width.computed;
    }

    // unset stroke and set fill color to former stroke color
    gchar * str;
    str = g_strdup_printf("fill:#%06x;stroke:none;", sp_desktop_get_color_tool(desktop, tool, false) >> 8);
    repr->setAttribute("style", str);
    g_free(str);

    // put the circle where the mouse click occurred and set the diameter to the
    // current stroke width, multiplied by the amount specified in the preferences
    Inkscape::Preferences *prefs = Inkscape::Preferences::get();

    Geom::Affine const i2d (item->i2dt_affine ());
    Geom::Point pp = pt * i2d.inverse();
    double rad = 0.5 * prefs->getDouble(tool_path + "/dot-size", 3.0);
    if (event_state & GDK_MOD1_MASK) {
        // TODO: We vary the dot size between 0.5*rad and 1.5*rad, where rad is the dot size
        // as specified in prefs. Very simple, but it might be sufficient in practice. If not,
        // we need to devise something more sophisticated.
        double s = g_random_double_range(-0.5, 0.5);
        rad *= (1 + s);
    }
    if (event_state & GDK_SHIFT_MASK) {
        // double the point size
        rad *= 2;
    }

    sp_repr_set_svg_double (repr, "sodipodi:cx", pp[Geom::X]);
    sp_repr_set_svg_double (repr, "sodipodi:cy", pp[Geom::Y]);
    sp_repr_set_svg_double (repr, "sodipodi:rx", rad * stroke_width);
    sp_repr_set_svg_double (repr, "sodipodi:ry", rad * stroke_width);
    item->updateRepr();

    desktop->getSelection()->set(item);

    desktop->messageStack()->flash(Inkscape::NORMAL_MESSAGE, _("Creating single dot"));
    DocumentUndo::done(desktop->getDocument(), SP_VERB_NONE, _("Create single dot"));
}