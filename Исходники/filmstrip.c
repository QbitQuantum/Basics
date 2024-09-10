static gboolean _lib_filmstrip_expose_callback(GtkWidget *widget, GdkEventExpose *event, gpointer user_data)
{
  dt_lib_module_t *self = (dt_lib_module_t *)user_data;
  dt_lib_filmstrip_t *strip = (dt_lib_filmstrip_t *)self->data;

  GtkAllocation allocation;
  gtk_widget_get_allocation(widget, &allocation);
  int32_t width = allocation.width;
  int32_t height = allocation.height;

  gdouble pointerx = strip->pointerx;
  gdouble pointery = strip->pointery;

  if(darktable.gui->center_tooltip == 1)
    darktable.gui->center_tooltip++;

  strip->image_over = DT_VIEW_DESERT;
  DT_CTL_SET_GLOBAL(lib_image_mouse_over_id, -1);

  /* create cairo surface */
  cairo_t *cr = gdk_cairo_create(gtk_widget_get_window(widget));

  /* fill background */
  cairo_set_source_rgb (cr, .2, .2, .2);
  cairo_paint(cr);

  int offset = strip->offset;

  const float wd = height;
  const float ht = height;

  int max_cols = (int)(width/(float)wd) + 2;
  if (max_cols%2 == 0)
    max_cols += 1;

  const int col_start = max_cols/2 - strip->offset;
  const int empty_edge = (width - (max_cols * wd))/2;
  int step_res = SQLITE_ROW;

  sqlite3_stmt *stmt = NULL;

  /* mouse over image position in filmstrip */
  pointerx -= empty_edge;
  const int seli = (pointery > 0 && pointery <= ht) ? pointerx / (float)wd : -1;
  const int img_pointerx = (int)fmodf(pointerx, wd);
  const int img_pointery = (int)pointery;


  /* get the count of current collection */
  strip->collection_count = dt_collection_get_count (darktable.collection);

  /* get the collection query */
  const gchar *query=dt_collection_get_query (darktable.collection);
  if(!query)
    return FALSE;

  if(offset < 0)
    strip->offset = offset = 0;
  if(offset > strip->collection_count-1)
    strip->offset = offset = strip->collection_count-1;

  // dt_view_set_scrollbar(self, offset, count, max_cols, 0, 1, 1);

  DT_DEBUG_SQLITE3_PREPARE_V2(dt_database_get(darktable.db), query, -1, &stmt, NULL);
  DT_DEBUG_SQLITE3_BIND_INT(stmt, 1, offset - max_cols/2);
  DT_DEBUG_SQLITE3_BIND_INT(stmt, 2, max_cols);


  cairo_save(cr);
  cairo_translate(cr, empty_edge, 0.0f);
  for(int col = 0; col < max_cols; col++)
  {
    if(col < col_start)
    {
      cairo_translate(cr, wd, 0.0f);
      continue;
    }

    if(step_res != SQLITE_DONE)
    {
      step_res = sqlite3_step(stmt);
    }

    if(step_res == SQLITE_ROW)
    {
      int id = sqlite3_column_int(stmt, 0);
      // set mouse over id
      if(seli == col)
      {
        strip->mouse_over_id = id;
        DT_CTL_SET_GLOBAL(lib_image_mouse_over_id, strip->mouse_over_id);
      }
      cairo_save(cr);
      // FIXME find out where the y translation is done, how big the value is and use it directly instead of getting it from the matrix ...
      cairo_matrix_t m;
      cairo_get_matrix(cr, &m);
      dt_view_image_expose(&(strip->image_over), id, cr, wd, ht, max_cols, img_pointerx, img_pointery, FALSE);
      cairo_restore(cr);
    }
    else if (step_res == SQLITE_DONE)
    {
      /* do nothing, just add some empty thumb frames */
    }
    else goto failure;
    cairo_translate(cr, wd, 0.0f);
  }
failure:
  cairo_restore(cr);
  sqlite3_finalize(stmt);

  if(darktable.gui->center_tooltip == 1) // set in this round
  {
    char* tooltip = dt_history_get_items_as_string(strip->mouse_over_id);
    if(tooltip != NULL)
    {
      g_object_set(G_OBJECT(strip->filmstrip), "tooltip-text", tooltip, (char *)NULL);
      g_free(tooltip);
    }
  }
  else if(darktable.gui->center_tooltip == 2)   // not set in this round
  {
    darktable.gui->center_tooltip = 0;
    g_object_set(G_OBJECT(strip->filmstrip), "tooltip-text", "", (char *)NULL);
  }

#ifdef _DEBUG
  if(darktable.unmuted & DT_DEBUG_CACHE)
    dt_mipmap_cache_print(darktable.mipmap_cache);
#endif

  /* cleanup */
  cairo_destroy(cr);

  return TRUE;
}