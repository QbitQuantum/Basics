void StrokeSelection::paste() {
  TTool *tool = TTool::getApplication()->getCurrentTool()->getTool();
  if (!tool) return;
  if (TTool::getApplication()->getCurrentObject()->isSpline()) {
    const StrokesData *stData = dynamic_cast<const StrokesData *>(
        QApplication::clipboard()->mimeData());
    if (!stData) return;
    TVectorImageP splineImg = tool->getImage(true);
    TVectorImageP img       = stData->m_image;
    if (!splineImg || !img) return;

    QMutexLocker lock(splineImg->getMutex());
    TUndo *undo = new ToolUtils::UndoPath(
        tool->getXsheet()->getStageObject(tool->getObjectId())->getSpline());
    while (splineImg->getStrokeCount() > 0) splineImg->deleteStroke(0);

    TStroke *stroke = img->getStroke(0);
    splineImg->addStroke(new TStroke(*stroke), false);
    TUndoManager::manager()->add(undo);
    tool->notifyImageChanged();
    tool->invalidate();
    return;
  }

  TVectorImageP tarImg = tool->touchImage();
  if (!tarImg) return;
  TPaletteP palette       = tarImg->getPalette();
  TPaletteP oldPalette    = new TPalette();
  if (palette) oldPalette = palette->clone();
  bool isPaste = pasteStrokesWithoutUndo(tarImg, m_indexes, m_sceneHandle);
  if (isPaste) {
    TXshSimpleLevel *level =
        TTool::getApplication()->getCurrentLevel()->getSimpleLevel();
    TUndoManager::manager()->add(new PasteStrokesUndo(
        level, tool->getCurrentFid(), m_indexes, oldPalette, m_sceneHandle));
    m_updateSelectionBBox = isPaste;
  }
  tool->notifyImageChanged();
  tool->getApplication()
      ->getPaletteController()
      ->getCurrentLevelPalette()
      ->notifyPaletteChanged();
  m_updateSelectionBBox = false;
  tool->invalidate();
}