int TApp::getCurrentImageType() {
  /*-- 現在のセルの種類に関係無く、Splineを選択中はベクタを編集できるようにする
   * --*/
  if (getCurrentObject()->isSpline()) return TImage::VECTOR;

  TXshSimpleLevel *sl = 0;

  if (getCurrentFrame()->isEditingScene()) {
    int row = getCurrentFrame()->getFrame();
    int col = getCurrentColumn()->getColumnIndex();
    if (col < 0)
#ifdef LINETEST
      return TImage::RASTER;
#else
    {
      int levelType = Preferences::instance()->getDefLevelType();
      return (levelType == PLI_XSHLEVEL)
                 ? TImage::VECTOR
                 :  // RASTER image type includes both TZI_XSHLEVEL
                 (levelType == TZP_XSHLEVEL)
                     ? TImage::TOONZ_RASTER
                     : TImage::RASTER;  // and OVL_XSHLEVEL level types
    }
#endif

    TXsheet *xsh  = getCurrentXsheet()->getXsheet();
    TXshCell cell = xsh->getCell(row, col);
    if (cell.isEmpty()) {
      int r0, r1;
      xsh->getCellRange(col, r0, r1);
      if (0 <= r0 && r0 <= r1) {
        /*-- Columnに格納されている一番上のLevelのTypeに合わせる--*/
        cell = xsh->getCell(r0, col);
      } else /*-- Columnが空の場合 --*/
      {
#ifdef LINETEST
        return TImage::RASTER;
#else
        int levelType = Preferences::instance()->getDefLevelType();
        return (levelType == PLI_XSHLEVEL)
                   ? TImage::VECTOR
                   : (levelType == TZP_XSHLEVEL) ? TImage::TOONZ_RASTER
                                                 : TImage::RASTER;
#endif
      }
    }

    sl = cell.getSimpleLevel();
  } else if (getCurrentFrame()->isEditingLevel())
    sl = getCurrentLevel()->getSimpleLevel();

  if (sl) {
    switch (sl->getType()) {
    case TZP_XSHLEVEL:
      return TImage::TOONZ_RASTER;
    case OVL_XSHLEVEL:
      return TImage::RASTER;
    case PLI_XSHLEVEL:
    default:
      return TImage::VECTOR;
    case MESH_XSHLEVEL:
      return TImage::MESH;
    }
  }

  return TImage::VECTOR;
}