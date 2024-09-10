void CGraphicBuildingTile::display(QList<QString> _toDisplay)
{
    QDialog* infoDialog = new QDialog;//(dynamic_cast<QWidget*>(this->parent()));
    QVBoxLayout* newLayout = new QVBoxLayout();
    int q=0;
    QScrollArea* scrolArea = new QScrollArea(dynamic_cast<QWidget*>(this->parent()));
    for(int i=0;i<_toDisplay.count();i++)
    {   QLabel* newLabel = new QLabel(_toDisplay.at(i));
        newLabel->setFixedWidth(280);
        newLabel->setMinimumHeight(22);
        newLabel->setStyleSheet("border: 1px solid black");
        newLayout->addWidget(newLabel);
        q++;
    }
    QPalette pal;
    pal.setColor(QPalette::Background,QColor(230,200,167));
    infoDialog->setFixedWidth(330);
    infoDialog->setMinimumHeight(30+22*q);
    infoDialog->setLayout(newLayout);
    infoDialog->setAutoFillBackground(true);
    infoDialog->setPalette(pal);
    infoDialog->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint | Qt::Dialog);
    scrolArea->setWidget(infoDialog);
    scrolArea->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint | Qt::Dialog);
    scrolArea->setMaximumHeight(infoDialog->size().height()+2);
    scrolArea->setWindowTitle(QString("Info about"));
    scrolArea->show();
}