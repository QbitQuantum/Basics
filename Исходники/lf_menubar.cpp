//------------------------------------------------------------------------------
void mforms::gtk::MenuItemImpl::set_checked(mforms::MenuItem *item, bool on) {
  Gtk::CheckMenuItem *mi = cast<Gtk::CheckMenuItem *>(item->get_data_ptr());
  if (mi) {
    mi->set_data("ignore_signal", (void *)1);
    mi->set_active(on);
    mi->set_data("ignore_signal", 0);
  } else
    logError("Passed MenuItem '%s' does not have CheckMenuItem at %p\n",
             mforms::gtk::MenuItemImpl::get_title(item).c_str(), item->get_data_ptr());
}