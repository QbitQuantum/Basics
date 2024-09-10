void tst_qdeclarativelayoutitem::test_resizing()
{
    //Create Layout (must be done in C++)
    QGraphicsView view;
    QGraphicsScene scene;
    QGraphicsWidget *widget = new QGraphicsWidget();
    QGraphicsLinearLayout *layout = new QGraphicsLinearLayout();
    widget->setLayout(layout);
    scene.addItem(widget);
    view.setScene(&scene);
    //Add the QML snippet into the layout
    QDeclarativeEngine engine;
    QDeclarativeComponent c(&engine, QUrl::fromLocalFile(SRCDIR "/data/layoutItem.qml"));
    QDeclarativeLayoutItem* obj = static_cast<QDeclarativeLayoutItem*>(c.create());
    QVERIFY(obj);
    QCOMPARE(obj->minimumSize(), QSizeF(100,100));
    QCOMPARE(obj->preferredSize(), QSizeF(200,200));
    QCOMPARE(obj->maximumSize(), QSizeF(300,300));

    layout->addItem(obj);
    layout->setContentsMargins(0,0,0,0);
    widget->setContentsMargins(0,0,0,0);
    view.show();

    QVERIFY(obj!= 0);

    widget->setGeometry(QRectF(0,0, 400,400));
    QCOMPARE(obj->width(), 300.0);
    QCOMPARE(obj->height(), 300.0);

    widget->setGeometry(QRectF(0,0, 300,300));
    QCOMPARE(obj->width(), 300.0);
    QCOMPARE(obj->height(), 300.0);

    widget->setGeometry(QRectF(0,0, 200,200));
    QCOMPARE(obj->width(), 200.0);
    QCOMPARE(obj->height(), 200.0);

    widget->setGeometry(QRectF(0,0, 100,100));
    QCOMPARE(obj->width(), 100.0);
    QCOMPARE(obj->height(), 100.0);

    widget->setGeometry(QRectF(0,0, 40,40));
    QCOMPARE(obj->width(), 100.0);
    QCOMPARE(obj->height(), 100.0);

    widget->setGeometry(QRectF(0,0, 412,112));
    QCOMPARE(obj->width(), 300.0);
    QCOMPARE(obj->height(), 112.0);
}