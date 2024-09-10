void tst_QGraphicsLayout::sizeHintOfHiddenLayout()
{
    QGraphicsScene scene;
    QGraphicsWidget *window = new QGraphicsWidget(0, Qt::Window);
    scene.addItem(window);
    TestLayout *lout = new TestLayout(window);
    lout->setContentsMargins(1,2,2,1);
    QGraphicsWidget *w = new QGraphicsWidget;
    w->setPreferredSize(20, 20);
    w->setMaximumSize(50, 50);
    lout->addItem(w);
    window->setLayout(lout);

    for (int pass = 0; pass < 3; ++pass) {
        QCOMPARE(lout->sizeHint(Qt::MinimumSize), QSizeF(3,3));
        QCOMPARE(lout->sizeHint(Qt::PreferredSize), QSizeF(23,23));
        QCOMPARE(lout->sizeHint(Qt::MaximumSize), QSizeF(53,53));
        window->setVisible(pass % 2);
    }
}