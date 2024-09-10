void
ags_note_edit_draw_segment(AgsNoteEdit *note_edit, cairo_t *cr)
{
  AgsEditor *editor;
  GtkWidget *widget;
  double tact;
  guint i, j;
  guint j_set;

  widget = (GtkWidget *) note_edit->drawing_area;

  editor = (AgsEditor *) gtk_widget_get_ancestor(GTK_WIDGET(note_edit),
						 AGS_TYPE_EDITOR);

  cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
  cairo_rectangle(cr, 0.0, 0.0, (double) widget->allocation.width, (double) widget->allocation.height);
  cairo_fill(cr);

  cairo_set_line_width(cr, 1.0);

  cairo_set_source_rgb(cr, 0.8, 0.8, 0.8);

  for(i = note_edit->y0 ; i < note_edit->height;){
    cairo_move_to(cr, 0.0, (double) i);
    cairo_line_to(cr, (double) note_edit->width, (double) i);
    cairo_stroke(cr);

    i += note_edit->control_height;
  }

  tact = exp2((double) gtk_combo_box_get_active(editor->toolbar->zoom) - 4.0);

  i = note_edit->control_current.x0;
  
  if(i < note_edit->width &&
     tact > 1.0 ){
    j_set = note_edit->control_current.nth_x % ((guint) tact);
    cairo_set_source_rgb(cr, 0.6, 0.6, 0.6);

    if(j_set != 0){
      j = j_set;
      goto ags_note_edit_draw_segment0;
    }
  }

  for(; i < note_edit->width; ){
    cairo_set_source_rgb(cr, 1.0, 1.0, 0.0);
    
    cairo_move_to(cr, (double) i, 0.0);
    cairo_line_to(cr, (double) i, (double) note_edit->height);
    cairo_stroke(cr);
    
    i += note_edit->control_current.control_width;
    
    cairo_set_source_rgb(cr, 0.6, 0.6, 0.6);
    
    for(j = 1; i < note_edit->width && j < tact; j++){
    ags_note_edit_draw_segment0:
      cairo_move_to(cr, (double) i, 0.0);
      cairo_line_to(cr, (double) i, (double) note_edit->height);
      cairo_stroke(cr);
      
      i += note_edit->control_current.control_width;
    }
  }
}