/* redraw activity */
static void statusbar_activity(SBAR_ITEM_REC *item, int ypos)
{
    WINDOW_REC *window;
    GList *tmp;
    gchar str[MAX_INT_STRLEN];
    int size_needed;
    gboolean act, det;

    size_needed = 0; act = det = FALSE;
    for (tmp = activity_list; tmp != NULL; tmp = tmp->next)
    {
	window = tmp->data;

	size_needed += 1+ltoa(str, window->refnum);

	if (!use_colors && window->new_data == NEWDATA_MSG_FORYOU)
	    det = TRUE;
	else
	    act = TRUE;
    }

    if (act) size_needed += 6; /* [Act: ], -1 */
    if (det) size_needed += 6; /* [Det: ], -1 */
    if (act && det) size_needed--;

    if (item->size != size_needed)
    {
        /* we need more (or less..) space! */
        statusbar_item_resize(item, size_needed);
        return;
    }

    if (item->size == 0)
        return;

    move(ypos, item->xpos);
    set_color((1 << 4)+3); addch('[');
    if (act) draw_activity("Act: ", TRUE, !det);
    if (act && det) addch(' ');
    if (det) draw_activity("Det: ", FALSE, TRUE);
    set_color((1 << 4)+3); addch(']');

    screen_refresh();
}