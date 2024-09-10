static void unselect_dst(GtkWidget *widget, gint row, gint column, GdkEventButton *event, gpointer data)
{
	if (!gUpdateFlag) MidiConnect(row2ref(gCurRow), row2ref(row), 0);
}