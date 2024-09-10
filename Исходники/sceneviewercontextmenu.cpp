void onShowHideSelectObject(QAction *action) {
  TApp *app = TApp::instance();
  TStageObjectId id;
  id.setCode(action->data().toInt());
  if (id == TStageObjectId::NoneId) return;
  if (action->text().startsWith("Show ") ||
      action->text().startsWith("Hide ")) {
    if (id.isColumn()) {
      app->getCurrentXsheet()
          ->getXsheet()
          ->getColumn(id.getIndex())
          ->setCamstandVisible(action->text().startsWith("Show "));
      TApp::instance()->getCurrentXsheet()->notifyXsheetChanged();
    }
  } else if (action->text().startsWith("Select ")) {
    if (id.isColumn()) {
      app->getCurrentColumn()->setColumnIndex(id.getIndex());
      app->getCurrentObject()->setObjectId(id);
    } else {
      app->getCurrentObject()->setObjectId(id);
      app->getCurrentTool()->setTool(T_Edit);
    }
  }
}