/** void QWidget::setParent(QWidget *parent)
 * bind/QWidget.h:16
 */
static int Widget_setParent(lua_State *L) {
  try {
    Widget *self = *((Widget **)dub_checksdata(L, 1, "mimas.Widget"));
    QWidget *parent = *((QWidget **)dub_checksdata(L, 2, "mimas.QWidget"));
    self->setParent(parent);
    return 0;
  } catch (std::exception &e) {
    lua_pushfstring(L, "setParent: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "setParent: Unknown exception");
  }
  return dub_error(L);
}