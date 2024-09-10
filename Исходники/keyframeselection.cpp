void TKeyframeSelection::setKeyframes() {
  TApp *app                   = TApp::instance();
  TXsheetHandle *xsheetHandle = app->getCurrentXsheet();
  TXsheet *xsh                = xsheetHandle->getXsheet();
  TStageObjectId cameraId     = xsh->getStageObjectTree()->getCurrentCameraId();
  if (isEmpty()) return;
  Position pos         = *m_positions.begin();
  int row              = pos.first;
  int col              = pos.second;
  TStageObjectId id    = col < 0 ? cameraId : TStageObjectId::ColumnId(col);
  TStageObject *pegbar = xsh->getStageObject(id);
  if (!pegbar) return;
  if (pegbar->isKeyframe(row)) {
    TStageObject::Keyframe key = pegbar->getKeyframe(row);
    pegbar->removeKeyframeWithoutUndo(row);
    UndoRemoveKeyFrame *undo =
        new UndoRemoveKeyFrame(id, row, key, xsheetHandle);
    undo->setObjectHandle(app->getCurrentObject());
    TUndoManager::manager()->add(undo);
  } else {
    pegbar->setKeyframeWithoutUndo(row);
    UndoSetKeyFrame *undo = new UndoSetKeyFrame(id, row, xsheetHandle);
    undo->setObjectHandle(app->getCurrentObject());
    TUndoManager::manager()->add(undo);
  }
  TApp::instance()->getCurrentScene()->setDirtyFlag(true);
  TApp::instance()->getCurrentObject()->notifyObjectIdChanged(false);
}