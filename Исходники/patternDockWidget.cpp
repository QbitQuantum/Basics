void patternDockWidget::
setSymbolList(const QHash<QRgb, QPixmap>& colorSymbols) {

  symbolList_->clear();
  const QVector<symbolPair> sortedList = sortHashByIntensity(colorSymbols);
  for (QVector<symbolPair>::const_iterator it = sortedList.begin(),
          end = sortedList.end(); it != end; ++it) {
    const QRgb thisColor = (*it).first;
    const QPixmap thisSymbol = (*it).second;
    QListWidgetItem* listItem =
      new QListWidgetItem(createIcon(thisColor, thisSymbol), "",
                          symbolList_);
    // also store the color values for convenience
    listItem->setData(Qt::UserRole, QVariant(QColor(thisColor)));
  }
  setSymbolCountLabel(symbolList_->count());
}