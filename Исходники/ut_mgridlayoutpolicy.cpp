void Ut_MGridLayoutPolicy::testHeightForWidthInSubLayout()
{
    QFETCH(bool, useMLayout);
    QFETCH(bool, useInnerMLayout);
    QFETCH(bool, putInnerWidgetInWidget);

    QGraphicsWidget *form = new QGraphicsWidget;


    MGridLayoutPolicy *mpolicy = NULL;
    QGraphicsGridLayout *qlayout = NULL;

    if (useMLayout) {
        MLayout *mlayout = new MLayout(form);
        mlayout->setContentsMargins(0, 0, 0, 0);
        mpolicy = new MGridLayoutPolicy(mlayout);
        mpolicy->setSpacing(0);
    } else {
        qlayout = new QGraphicsGridLayout(form);
        qlayout->setContentsMargins(0, 0, 0, 0);
        qlayout->setSpacing(0);
    }

    QGraphicsWidget *topSpacer = createSpacer();
    QGraphicsWidget *leftSpacer = createSpacer();
    QGraphicsWidget *rightSpacer = createSpacer();
    leftSpacer->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
    rightSpacer->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);

    QGraphicsWidget *square = new SquareWidget;

    QGraphicsLayout *innerLayout = NULL;
    if (useInnerMLayout) {
        innerLayout = new MLayout();
        MLinearLayoutPolicy *policy = new MLinearLayoutPolicy(static_cast<MLayout *>(innerLayout), Qt::Horizontal);
        policy->addItem(square);
    } else {
        innerLayout = new QGraphicsLinearLayout(Qt::Horizontal);
        static_cast<QGraphicsLinearLayout *>(innerLayout)->addItem(square);
    }
    innerLayout->setContentsMargins(0,0,0,0);

    QGraphicsLayoutItem *innerItem;
    if (putInnerWidgetInWidget) {
        QGraphicsWidget *innerWidget = new QGraphicsWidget;
        innerWidget->setLayout(innerLayout);
        innerItem = innerWidget;
    } else {
        innerItem = innerLayout;
    }

    if (useMLayout) {
        mpolicy->addItem(topSpacer, 0, 1);
        mpolicy->addItem(leftSpacer, 1, 0);
        mpolicy->addItem(rightSpacer, 1, 2);
        mpolicy->addItem(innerItem, 1, 1);
    } else {
        qlayout->addItem(topSpacer, 0, 1);
        qlayout->addItem(leftSpacer, 1, 0);
        qlayout->addItem(rightSpacer, 1, 2);
        qlayout->addItem(innerItem, 1, 1);
    }


    QCOMPARE(form->preferredSize(), QSizeF(500,500));
    QCOMPARE(form->effectiveSizeHint(Qt::PreferredSize, QSizeF(100,-1)), QSizeF(100,100));

    delete form;
}