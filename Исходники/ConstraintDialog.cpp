ConstraintTable::ConstraintTable(QWidget * parent, ConstraintCanvas * c)
    : Q3Table(c->elements.count(), 4, parent)
{
    setSorting(true);
    setSelectionMode(NoSelection);
    setRowMovingEnabled(FALSE);

    horizontalHeader()->setLabel(0, TR("visible"));
    horizontalHeader()->setLabel(1, " ");
    horizontalHeader()->setLabel(2, TR("element"));
    horizontalHeader()->setLabel(3, TR("constraint"));
    setColumnStretchable(0, FALSE);
    setColumnStretchable(1, FALSE);

    int row;
    bool v = c->indicate_visible;
    Q3ValueList<BrowserNode *> & hv = c->hidden_visible;
    BrowserNodeList & elts = c->elements;
    BrowserNode * bn;
    QString yes = TR("  yes");
    QString empty;

    elts.sort();

    for (bn = elts.first(), row = 0; bn != 0; bn = elts.next(), row += 1) {
        if ((v) ? hv.findIndex(bn) != -1 : hv.findIndex(bn) == -1)
            setText(row, 0, yes);

        setPixmap(row, 1, *(bn->pixmap(0)));

        TableItem * ti;

        ti = new TableItem(this, Q3TableItem::Never, bn->full_name(TRUE));
        ti->setReplaceable(FALSE);
        setItem(row, 2, ti);

        QString s = toUnicode(bn->constraint());
        int n = s.count('\n');

        ti = new TableItem(this, Q3TableItem::Never, s);
        ti->setReplaceable(FALSE);
        setItem(row, 3, ti);

        if (n != 0) {
            // note : adjustRow(row) does nothing
            setRowHeight(row, rowHeight(row) * (n + 1));
        }
    }

    adjustColumn(0);
    adjustColumn(1);
    setColumnStretchable(2, TRUE);
    setColumnStretchable(3, TRUE);

    connect(this, SIGNAL(pressed(int, int, int, const QPoint &)),
            this, SLOT(button_pressed(int, int, int, const QPoint &)));
}