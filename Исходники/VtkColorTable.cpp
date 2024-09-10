void VtkColorTable::updateBlue(int val, bool updateAll) {
    mainTable->item(mainTable->currentRow(), 3)->setText(QString::number(val));

    Point point = points.at(mainTable->currentRow());
    QColor & color = point.color;
    color.setBlue(val);
    points.replace(mainTable->currentRow(), point);

    if (updateAll) {
        updateColors();
        updateColorFunction();
    }
}