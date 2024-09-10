/** void QWidget::addWidget(QWidget *widget)
 * bind/QWidget.h:46
 */
static int TableView_addWidget(lua_State *L) {
  try {
    TableView *self = *((TableView **)dub_checksdata(L, 1, "mimas.TableView"));
    QWidget *widget = *((QWidget **)dub_checksdata(L, 2, "mimas.QWidget"));
    widget->setParent(self);
    return 0;
  } catch (std::exception &e) {
    lua_pushfstring(L, "addWidget: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "addWidget: Unknown exception");
  }
  return dub_error(L);
}