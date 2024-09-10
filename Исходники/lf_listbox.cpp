//------------------------------------------------------------------------------
void ListBoxImpl::set_index(::mforms::ListBox *self, ssize_t index)
{
  ListBoxImpl* sel= self->get_data<ListBoxImpl>();

  if ( sel )
  {
    Glib::RefPtr<Gtk::TreeView::Selection> selection = sel->_lbox.get_selection();
    Gtk::TreeModel::Children children = sel->_store->children();
    if ( children.size() > (unsigned int)index && index >= 0 )
    {
      Gtk::TreeModel::Row row = children[index];
      if ( row )
        selection->select(row);
    }
  }
}