void DotPlotDialog::sl_invertedColorButton() {
    QObjectScopedPointer<QColorDialog> d = new QColorDialog(invertedColor, this);
    d->exec();
    CHECK(!d.isNull(), );

    if (QDialog::Accepted == d->result()) {
        invertedColor = d->selectedColor();
        invertedCheckBox->setChecked(true);
    }

    updateColors();
}