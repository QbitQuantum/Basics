void RunningScriptsWidget::setRunningScripts(const QStringList& list) {
    setUpdatesEnabled(false);
    QLayoutItem* widget;
    while ((widget = ui->scrollAreaWidgetContents->layout()->takeAt(0)) != NULL) {
        delete widget->widget();
        delete widget;
    }
    QHash<QString, int> hash;
    const int CLOSE_ICON_HEIGHT = 12;
    for (int i = 0; i < list.size(); i++) {
        if (!hash.contains(list.at(i))) {
            hash.insert(list.at(i), 1);
        }
        QWidget* row = new QWidget(ui->scrollAreaWidgetContents);
        row->setLayout(new QHBoxLayout(row));

        QUrl url = QUrl(list.at(i));
        QLabel* name = new QLabel(url.fileName(), row);
        if (hash.find(list.at(i)).value() != 1) {
            name->setText(name->text() + "(" + QString::number(hash.find(list.at(i)).value()) + ")");
        }
        ++hash[list.at(i)];
        QPushButton* closeButton = new QPushButton(row);
        closeButton->setFlat(true);
        closeButton->setIcon(
            QIcon(QPixmap(Application::resourcesPath() + "images/kill-script.svg").scaledToHeight(CLOSE_ICON_HEIGHT)));
        closeButton->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred));
        closeButton->setStyleSheet("border: 0;");
        closeButton->setCursor(Qt::PointingHandCursor);

        connect(closeButton, SIGNAL(clicked()), &_signalMapper, SLOT(map()));
        _signalMapper.setMapping(closeButton, url.toString());

        row->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed));

        row->layout()->setContentsMargins(4, 4, 4, 4);
        row->layout()->setSpacing(0);

        row->layout()->addWidget(name);
        row->layout()->addWidget(closeButton);

        row->setToolTip(url.toString());

        QFrame* line = new QFrame(row);
        line->setFrameShape(QFrame::HLine);
        line->setStyleSheet("color: #E1E1E1; margin-left: 6px; margin-right: 6px;");

        ui->scrollAreaWidgetContents->layout()->addWidget(row);
        ui->scrollAreaWidgetContents->layout()->addWidget(line);
    }


    ui->noRunningScriptsLabel->setVisible(list.isEmpty());
    ui->reloadAllButton->setVisible(!list.isEmpty());
    ui->stopAllButton->setVisible(!list.isEmpty());

    ui->scrollAreaWidgetContents->updateGeometry();
    setUpdatesEnabled(true);
    Application::processEvents();
    repaint();
}