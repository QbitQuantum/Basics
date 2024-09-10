/*
 * While the pannedWidget is populated, sizePosChanged() signal should be
 * emitted only once for each actual change in pannedWidget's size.
 *
 * See NB#143428
 */
void Ut_MPannableViewport::sizePosChangedAfterPopulatingPannedWidget()
{
    QGraphicsWidget *mainWidget = new QGraphicsWidget();
    QGraphicsLinearLayout *layout = new QGraphicsLinearLayout(Qt::Vertical);
    QGraphicsWidget *childWidget;

    //Settle initial layout position
    subject->adjustSize();

    mainWidget->setLayout(layout);

    subject->setWidget(mainWidget);

    QSignalSpy spyRange(subject,
                   SIGNAL(rangeChanged(QRectF)));
    QSignalSpy spyViewportSize(subject,
                   SIGNAL(viewportSizeChanged(QSizeF)));
    QSignalSpy spyPosition(subject,
                   SIGNAL(positionChanged(QPointF)));


    for (int i = 0; i < 30; i++) {
        childWidget = new QGraphicsWidget;

        childWidget->setMinimumSize(100, 200);
        childWidget->setPreferredSize(100, 200);

        layout->addItem(childWidget);
    }

    // Force layout to work.
    subject->adjustSize();

    // Check consecutive signals (if any), are different from each other.
    // We don't want to send out the very same event twice.
    for (int i = 1; i < spyRange.size(); i++) {
        QVERIFY(spyRange.at(i) != spyRange.at(i - 1));
    }
    for (int i = 1; i < spyPosition.size(); i++) {
        QVERIFY(spyPosition.at(i) != spyPosition.at(i - 1));
    }
    for (int i = 1; i < spyViewportSize.size(); i++) {
        QVERIFY(spyViewportSize.at(i) != spyViewportSize.at(i - 1));
    }
}