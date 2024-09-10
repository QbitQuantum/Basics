void ColoringRulesDialog::addColoringRule(bool disabled, QString name, QString filter, QColor foreground, QColor background, bool start_editing)
{
    QTreeWidgetItem *ti = new QTreeWidgetItem(ui->coloringRulesTreeWidget);

    ti->setFlags(ti->flags() | Qt::ItemIsUserCheckable | Qt::ItemIsEditable);
    ti->setFlags(ti->flags() & ~(Qt::ItemIsDropEnabled));
    ti->setCheckState(name_col_, disabled ? Qt::Unchecked : Qt::Checked);
    ti->setText(name_col_, name);
    ti->setText(filter_col_, filter);

    for (int i = 0; i < ui->coloringRulesTreeWidget->columnCount(); i++) {
        ti->setForeground(i, foreground);
        ti->setBackground(i, background);
    }

    ui->coloringRulesTreeWidget->addTopLevelItem(ti);

    if (start_editing) {
        ui->coloringRulesTreeWidget->setCurrentItem(ti);
        updateWidgets();
        ui->coloringRulesTreeWidget->editItem(ti, filter_col_);
    }
}