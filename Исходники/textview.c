void TE_View::keystroke(const Event& e)
{
    if (active_) {
   current_window_ = e.window();
   
   // check if known key symbol
   unsigned long keysym = e.keysym();
   for (TE_ViewKeySymInfo* k = &default_key_sym_map[0];
	k->keysym != 0; k++) {
      if (keysym == k->keysym) {
	 TE_ViewKeyFunc f = k->func;
	 (this->*f)();
	 return;
      }
   }

   // map event to key
   signed char c;
   if (e.mapkey((char *)&c, 1) == 0)
      return;

   // check if known key map
#ifndef __sgi /* avoid SGI gcc warning */
   if (c >= 0) { // fix alt-V on linux/pc
#else
   if (1) { 
#endif
       TE_ViewKeyFunc f =  key_[c];
       if (f != nil) {
	   (this->*f)();
	   return;
       }
   }

#ifndef __sgi /* avoid SGI gcc warning */
   if (c >= 0 && (isspace(c) || !iscntrl(c))) 
#else
   if (isspace(c) || !iscntrl(c)) 
#endif
      insert_char(c);
   else 
      printf("Unknown character - ignored!\n");
}
}

void TE_View::double_click(const Event& e)
{
    if (active_) {
   boolean tripple_click = false;
   int dot, mark;
   unsigned long t = e.time();
   if (t - click_time_ < threshold_) {
      tripple_click = true;
   }
   click_time_ = t;

   int index = event_to_index(e);
   text_editor_->Select(index);

   // select work or line
   if (tripple_click) {
      // line
      text_editor_->BeginningOfLine();
      dot = text_editor_->Dot();
      text_editor_->EndOfLine();
      mark = text_editor_->Dot();
   }
   else {
      // word
      text_editor_->BeginningOfWord();
      dot = text_editor_->Dot();
      text_editor_->EndOfWord();
      mark = text_editor_->Dot();
   }
   text_editor_->Select(dot, mark);

   // copy and own current selection
   SelectionManager* s = e.display()->primary_selection();
   copy_selection(s);
   own_selection(s);
}
}

void TE_View::popup_menu(const Event&e)
{
  // display popup-menu
  const Window& rel = *e.window();
  Coord x = rel.left() + e.pointer_x();
  Coord y = rel.bottom() + e.pointer_y() - menu_window_->height() + 6;
  menu_window_->place(x, y);
  menu_window_->map();
}

void TE_View::line_update()
{
   // update line information
   lines_ = displayed_lines();
   end_row_ = start_row_ + lines_ - 1;
   notify();			// notify adjustable
}