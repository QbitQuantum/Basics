  bool BugzillaNoteAddin::insert_bug(int x, int y, const std::string & uri, int id)
  {
    try {
      BugzillaLink::Ptr link_tag = 
        BugzillaLink::Ptr::cast_dynamic(get_note()->get_tag_table()->create_dynamic_tag(TAG_NAME));
      link_tag->set_bug_url(uri);

      // Place the cursor in the position where the uri was
      // dropped, adjusting x,y by the TextView's VisibleRect.
      Gdk::Rectangle rect;
      get_window()->editor()->get_visible_rect(rect);
      x = x + rect.get_x();
      y = y + rect.get_y();
      Gtk::TextIter cursor;
      gnote::NoteBuffer::Ptr buffer = get_buffer();
      get_window()->editor()->get_iter_at_location(cursor, x, y);
      buffer->place_cursor (cursor);

      std::string string_id = boost::lexical_cast<std::string>(id);
      buffer->undoer().add_undo_action (new InsertBugAction (cursor, 
                                                             string_id, 
                                                             link_tag));

      std::vector<Glib::RefPtr<Gtk::TextTag> > tags;
      tags.push_back(link_tag);
      buffer->insert_with_tags (cursor, 
                                string_id, 
                                tags);
      return true;
    } 
    catch (...)
    {
		}
    return false;
  }