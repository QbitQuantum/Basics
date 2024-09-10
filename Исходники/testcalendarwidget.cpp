/* FIXME make this less of a hack. */
QRect TestCalendarWidget::visualRect(QString const &item) const
{
    TestWidgetsLog() << item << "my geometry is" << geometry();

    QRect ret;

    QAbstractItemView *view = q->findChild<QAbstractItemView*>();
    QtUiTest::ListWidget *calendarView
        = qtuitest_cast<QtUiTest::ListWidget*>(view);

    if (!calendarView) {
        return ret;
    }

    ret = calendarView->visualRect(item);
    if (!ret.isNull()) {
        ret.moveTopLeft( q->mapFromGlobal( view->mapToGlobal(ret.topLeft()) ) );
        TestWidgetsLog() << item << "is a visible day at" << ret;
        return ret;
    }

    QToolButton *yearButton = 0;
    QToolButton *monthButton = 0;
    QSpinBox *yearSpin = q->findChild<QSpinBox*>();
    QMenu *monthMenu = 0;

    QList<QToolButton*> blist = q->findChildren<QToolButton*>();
    foreach(QToolButton *b, blist) {
        if (!monthButton && (monthMenu = b->menu())) {
            monthButton = b;
        }
        if (!b->menu()) {
            yearButton = b;
        }
    }
    TestWidgetsLog() << "monthButton" << monthButton << "yearButton" << yearButton;
    TestWidgetsLog() << "item" << item << "monthMenu" << monthMenu;

    if (yearButton && yearButton->isVisible() && yearButton->text() == item) {
        QPoint p = q->mapFromGlobal( yearButton->mapToGlobal(QPoint(yearButton->width()+5, yearButton->height()/2)) );
        ret = QRect(p.x() - 2, p.y() - 2, 5, 5);
        TestWidgetsLog() << "click near yearbutton";
    } else if (yearSpin && yearSpin->isVisible() && yearSpin->value() == item.toInt()) {
        TestWidgetsLog() << "confirm spinbox";
        QPoint p = q->mapFromGlobal( yearSpin->mapToGlobal(QPoint(yearSpin->width()+5, yearSpin->height()/2)) );
        ret = QRect(p.x() - 2, p.y() - 2, 5, 5);
    } else if (monthButton && monthButton->isVisible() && monthButton->text() == item) {
        QPoint p = q->mapFromGlobal( monthButton->mapToGlobal(QPoint(-5, monthButton->height()/2)) );
        ret = QRect(p.x() - 2, p.y() - 2, 5, 5);
        TestWidgetsLog() << "click near monthbutton";
    } else if (monthMenu && monthMenu->isVisible()
            && qtuitest_cast<QtUiTest::ListWidget*>(monthMenu)
            && qtuitest_cast<QtUiTest::ListWidget*>(monthMenu)->list().contains(item)) {
        ret = qtuitest_cast<QtUiTest::ListWidget*>(monthMenu)->visualRect(item);
        ret.moveTopLeft( q->mapFromGlobal( monthMenu->mapToGlobal(ret.topLeft()) ) );
        TestWidgetsLog() << "click on monthmenu";
    } else {
        do {
            QStringList items = list();
            if (items.contains(item)) {
                ret = QRect(-1, -1, 1, 1);
                ret.moveTopLeft( q->mapFromGlobal(QPoint(-1,-1)) );
                break;
            }
            foreach (QString s, items) {
                if (!s.startsWith(GetListRegExp)) continue;
                QRegExp re(s.mid(GetListRegExp.length()));
                if (re.exactMatch(item)) {
                    ret = QRect(-1, -1, 1, 1);
                    ret.moveTopLeft( q->mapFromGlobal(QPoint(-1,-1)) );
                    break;
                }
            }
            if (!ret.isNull()) break;
        } while(0);
    }

    TestWidgetsLog() << "returning rect" << ret;

    return ret;
}