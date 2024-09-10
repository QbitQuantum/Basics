FQTermShortcutDialog::FQTermShortcutDialog(FQTermShortcutHelper* helper, QWidget *parent_, Qt::WindowFlags fl)
  : QDialog(parent_, fl),
    helper_(helper),
    table_(NULL) {
  setWindowTitle(tr("Shortcut Setting"));
  //grabKeyboard();
  if (helper_)
  {
    QSignalMapper* signalMapper = new QSignalMapper(this);
    int row = FQTermShortcutHelper::FQTERM_APPLICATION_SHORTCUT_END - FQTermShortcutHelper::FQTERM_APPLICATION_SHORTCUT_START - 1;
    int column = 3;
    table_ = new QTableWidget(row, column, this);
    table_->clear();
    QStringList header;
    header << tr("Description") << tr("Shortcut") << "";
    table_->setHorizontalHeaderLabels(header);
    for (int i = 0; i < row; ++i) {
      for (int j = 0; j < column; ++j) {
        if (j == 0) {
          QTableWidgetItem* item = new QTableWidgetItem;
          table_->setItem(i, j, item);
          item->setFlags(item->flags() & ~Qt::ItemIsEditable);
          item->setText(helper_->getShortcutDescription(i + 1));
        } else if (j == 1) {
          FQTermShortcutTableWidget* stw = new FQTermShortcutTableWidget(table_);
          stw->setReadOnly(true);
          stw->setText(helper_->getShortcutText(i + 1));
          table_->setCellWidget(i, j, stw);
        }else {
          QPushButton* btn = new QPushButton(tr("default"), table_);
          table_->setCellWidget(i, j, btn);
          FQ_VERIFY(connect(btn, SIGNAL(clicked()), signalMapper, SLOT(map())));
         signalMapper->setMapping(btn, i);
        }
      }
    }
    table_->resizeColumnsToContents();
    int tableWidth = table_->horizontalHeader()->length();
    if (table_->horizontalScrollBar() && table_->horizontalScrollBar()->isVisible()) {
      tableWidth += table_->horizontalScrollBar()->width();
    }
    QPushButton* okBtn = new QPushButton(tr("OK"), this);
    FQ_VERIFY(connect(okBtn, SIGNAL(clicked()), this, SLOT(okBtnClicked())));
    QPushButton* applyBtn = new QPushButton(tr("Apply"), this);
    FQ_VERIFY(connect(applyBtn, SIGNAL(clicked()), this, SLOT(applyBtnClicked())));
    QPushButton* cancelBtn = new QPushButton(tr("Cancel"), this);
    FQ_VERIFY(connect(cancelBtn, SIGNAL(clicked()), this, SLOT(cancelBtnClicked())));
    QPushButton* resetBtn = new QPushButton(tr("Reset All"), this);
    FQ_VERIFY(connect(resetBtn, SIGNAL(clicked()), this, SLOT(resetBtnClicked())));
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    QGridLayout* layout = new QGridLayout(this);
    QLabel* label = new QLabel(tr("Press key/combines on Shortcut column.\nNote Del is reserved for clear shortcut setting."));
    layout->addWidget(label, 0, 0, 1, -1);
    layout->addWidget(table_, 1, 0, 1, -1);
    layout->addWidget(okBtn, 2, 0);
    layout->addWidget(applyBtn, 2, 1);
    layout->addWidget(cancelBtn, 2, 2);
    layout->addWidget(resetBtn, 2, 3);
    setLayout(layout);
    int left = 0;
    int right = 0;
    layout->getContentsMargins(&left, NULL, &right, NULL);
    table_->horizontalHeader()->setStretchLastSection(true);
    tableWidth *= 1.1;
    resize(tableWidth + left + right, height());
    FQ_VERIFY(connect(signalMapper, SIGNAL(mapped(int)),this, SLOT(defaultClicked(int))));
  }
}