void BrowserNode::update_stereotype(bool rec) {
  BasicData * data = get_data();
  
  if (data != 0) {
    const char * stereotype = data->get_stereotype();
    
    if (show_stereotypes && stereotype[0]) {
      QString s = toUnicode(stereotype);
      int index = s.find(':');
      
      setText(0,
	      "<<" + ((index == -1) ? s : s.mid(index + 1))
	      + ">> " + name);
    }
    else
      setText(0, (const char *) name);
  }
  
  if (rec) {
    Q3ListViewItem * child;
    
    for (child = firstChild(); child != 0; child = child->nextSibling())
      ((BrowserNode *) child)->update_stereotype(TRUE);
  }
}