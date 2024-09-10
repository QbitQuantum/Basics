void DlgPropiedades::setOpcion(Gtk::TreeView *tr, unsigned int numOpcion)
{
    Gtk::TreeModel::Row row = tr->get_model()->children()[ numOpcion ];
    Glib::RefPtr<Gtk::TreeSelection> selected = tr->get_selection();

    if( row ) {
      selected->select( row );
    }
}