int
main (int argc,
      char **argv)
{
    FT_Error error;
    FT_Library library;
    FT_Face face;
    GFile *file;
    gint font_size, thumb_size = THUMB_SIZE;
    gchar *thumbstr_utf8 = NULL, *help, *uri;
    gchar **arguments = NULL;
    GOptionContext *context;
    GError *gerror = NULL;
    gchar *contents = NULL;
    gboolean retval, default_thumbstr = TRUE;
    gint rv = 1;
    GdkRGBA white = { 1.0, 1.0, 1.0, 1.0 };
    GdkRGBA black = { 0.0, 0.0, 0.0, 1.0 };
    cairo_surface_t *surface;
    cairo_t *cr;
    cairo_text_extents_t text_extents;
    cairo_font_face_t *font;
    gchar *str;
    gdouble scale, scale_x, scale_y;

    const GOptionEntry options[] = {
	    { "text", 't', 0, G_OPTION_ARG_STRING, &thumbstr_utf8,
	      N_("Text to thumbnail (default: Aa)"), N_("TEXT") },
	    { "size", 's', 0, G_OPTION_ARG_INT, &thumb_size,
	      N_("Thumbnail size (default: 128)"), N_("SIZE") },
	    { G_OPTION_REMAINING, 0, 0, G_OPTION_ARG_FILENAME_ARRAY, &arguments,
	      NULL, N_("FONT-FILE OUTPUT-FILE") },
	    { NULL }
    };

    bindtextdomain (GETTEXT_PACKAGE, GNOMELOCALEDIR);
    bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");
    textdomain (GETTEXT_PACKAGE);

    setlocale (LC_ALL, "");

    g_type_init ();

    context = g_option_context_new (NULL);
    g_option_context_add_main_entries (context, options, GETTEXT_PACKAGE);

    retval = g_option_context_parse (context, &argc, &argv, &gerror);
    if (!retval) {
	g_printerr ("Error parsing arguments: %s\n", gerror->message);

	g_option_context_free  (context);
	g_error_free (gerror);
        return 1;
    }

    if (!arguments || g_strv_length (arguments) != 2) {
	help = g_option_context_get_help (context, TRUE, NULL);
	g_printerr ("%s", help);

	g_option_context_free (context);
	goto out;
    }

    g_option_context_free (context);

    if (thumbstr_utf8 != NULL)
	default_thumbstr = FALSE;

    error = FT_Init_FreeType (&library);
    if (error) {
	g_printerr("Could not initialise freetype: %s\n", get_ft_error (error));
	goto out;
    }

    totem_resources_monitor_start (arguments[0], 30 * G_USEC_PER_SEC);

    file = g_file_new_for_commandline_arg (arguments[0]);
    uri = g_file_get_uri (file);
    g_object_unref (file);

    face = sushi_new_ft_face_from_uri (library, uri, &contents, &gerror);
    if (gerror) {
	g_printerr ("Could not load face '%s': %s\n", uri,
		    gerror->message);
        g_free (uri);
        g_error_free (gerror);
	goto out;
    }

    g_free (uri);

    if (default_thumbstr) {
        if (check_font_contain_text (face, "Aa"))
            str = g_strdup ("Aa");
        else
            str = build_fallback_thumbstr (face);
    } else {
        str = thumbstr_utf8;
    }

    surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32,
                                          thumb_size, thumb_size);
    cr = cairo_create (surface);

    gdk_cairo_set_source_rgba (cr, &white);
    cairo_paint (cr);

    font = cairo_ft_font_face_create_for_ft_face (face, 0);
    cairo_set_font_face (cr, font);
    cairo_font_face_destroy (font);

    font_size = thumb_size - 2 * PADDING_VERTICAL;
    cairo_set_font_size (cr, font_size);
    cairo_text_extents (cr, str, &text_extents);

    if ((text_extents.width) > (thumb_size - 2 * PADDING_HORIZONTAL)) {
        scale_x = (gdouble) (thumb_size - 2 * PADDING_HORIZONTAL) / (text_extents.width);
    } else {
        scale_x = 1.0;
    }

    if ((text_extents.height) > (thumb_size - 2 * PADDING_VERTICAL)) {
        scale_y = (gdouble) (thumb_size - 2 * PADDING_VERTICAL) / (text_extents.height);
    } else {
        scale_y = 1.0;
    }

    scale = MIN (scale_x, scale_y);
    cairo_scale (cr, scale, scale);
    cairo_translate (cr, 
                     PADDING_HORIZONTAL - text_extents.x_bearing + (thumb_size - scale * text_extents.width) / 2.0,
                     PADDING_VERTICAL - text_extents.y_bearing + (thumb_size - scale * text_extents.height) / 2.0);

    gdk_cairo_set_source_rgba (cr, &black);
    cairo_show_text (cr, str);
    cairo_destroy (cr);

    cairo_surface_write_to_png (surface, arguments[1]);
    cairo_surface_destroy (surface);

    totem_resources_monitor_stop ();

    error = FT_Done_Face (face);
    if (error) {
	g_printerr("Could not unload face: %s\n", get_ft_error (error));
	goto out;
    }

    error = FT_Done_FreeType (library);
    if (error) {
	g_printerr ("Could not finalize freetype library: %s\n",
		   get_ft_error (error));
	goto out;
    }

    rv = 0; /* success */

  out:

    g_strfreev (arguments);
    g_free (str);
    g_free (contents);

    return rv;
}