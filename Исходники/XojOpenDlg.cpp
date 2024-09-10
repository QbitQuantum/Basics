void XojOpenDlg::updatePreviewCallback(GtkFileChooser* fileChooser, void* userData)
{
	gchar* filename = gtk_file_chooser_get_preview_filename(fileChooser);

	if (!filename)
	{
		gtk_file_chooser_set_preview_widget_active(fileChooser, false);
		return;
	}

	string filepath = filename;
	g_free(filename);
	filename = NULL;

	if (filepath.size() <= 4 || filepath.substr(filepath.size() - 4) != ".xoj")
	{
		gtk_file_chooser_set_preview_widget_active(fileChooser, false);
		return;
	}

	XojPreviewExtractor extractor;
	PreviewExtractResult result = extractor.readFile(filepath);

	if (result != PREVIEW_RESULT_IMAGE_READ)
	{
		gtk_file_chooser_set_preview_widget_active(fileChooser, false);
		return;
	}

	GError* error = NULL;
	GInputStream* in = g_memory_input_stream_new_from_data(extractor.getData().c_str(), extractor.getData().length(), NULL);
	GdkPixbuf* pixbuf = gdk_pixbuf_new_from_stream(in, NULL, &error);
	g_input_stream_close(in, NULL, &error);

	if (pixbuf)
	{
		GtkWidget * image = gtk_file_chooser_get_preview_widget(fileChooser);
		gtk_image_set_from_pixbuf(GTK_IMAGE(image), pixbuf);
		g_object_unref(pixbuf);
		gtk_file_chooser_set_preview_widget_active(fileChooser, true);
	}
}