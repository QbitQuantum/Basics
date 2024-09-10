int  GLUI_List::delete_all()
{
  GLUI_List_Item *item;

  item = (GLUI_List_Item *) items_list.first_child();
  while( item ) {
    item->unlink();
    delete item;
    item = (GLUI_List_Item *) items_list.first_child();
  }

  num_lines = 0;
  curr_line = 0;

  return true;
}