TileSelectionWidget::TileSelectionWidget(QWidget *parent_)
{
    setParent(parent_);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    setAutoFillBackground(true);
    QPalette pal(palette());
    pal.setColor(QPalette::Background, QColor(157, 150, 150));
    setPalette(pal);
    container = new QWidget(this);
    container->setStyleSheet("background:transparent;");
    tileSetPixmap.load("res/img/tileset.png");
    tileSetLabel = new QLabel(container);
    tileSetLabel->setPixmap(tileSetPixmap);
    tileSetLabel->resize(tileSetPixmap.size());
    cursor = new QLabel(container);
    cursor->setPixmap(QPixmap("res/img/GUI/tileSelector.png"));
    container->resize(tileSetLabel->size() + QSize(80, 80));
    tileSetLabel->move(40, 40);
    cursor->move(40, 40);
    setWidget(container);
    select(0, 0);
    leftButtonDown = false;
}