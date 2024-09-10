void
BestIntervalDialog::findClicked()
{
    const RideFile *ride = context->ride ? context->ride->ride() : NULL;
    if (!ride) {
        QMessageBox::critical(this, tr("Select Activity"), tr("No activity selected!"));
        return;
    }

    int maxIntervals = (int) countSpinBox->value();
    double windowSizeSecs = (hrsSpinBox->value() * 3600.0
                             + minsSpinBox->value() * 60.0
                             + secsSpinBox->value());

    if (windowSizeSecs == 0.0) {
        QMessageBox::critical(this, tr("Bad Interval Length"),
                              tr("Interval length must be greater than zero!"));
        return;
    }

    QList<BestInterval> results;
    findBests(ride, Specification(), windowSizeSecs, maxIntervals, results);

    // clear the table
    clearResultsTable(resultsTable);

    // populate the table
    resultsTable->setRowCount(results.size());
    int row = 0;
    foreach (const BestInterval &interval, results) {

        double secs = interval.start;
        double mins = floor(secs / 60);
        secs = secs - mins * 60.0;
        double hrs = floor(mins / 60);
        mins = mins - hrs * 60.0;

        // check box
        QCheckBox *c = new QCheckBox;
        c->setCheckState(Qt::Checked);
        resultsTable->setCellWidget(row, 0, c);

        // start time
        QString start = "%1:%2:%3";
        start = start.arg(hrs, 0, 'f', 0);
        start = start.arg(mins, 2, 'f', 0, QLatin1Char('0'));
        start = start.arg(round(secs), 2, 'f', 0, QLatin1Char('0'));

        QTableWidgetItem *t = new QTableWidgetItem;
        t->setText(start);
        t->setFlags(t->flags() & (~Qt::ItemIsEditable));
        resultsTable->setItem(row, 1, t);

        // name
        int x = windowSizeSecs; // int is more help here
        QString name = "Best %2%3 #%1 (%4w)";
        name = name.arg(row + 1);
        // best n mins
        if (x < 60) {
            // whole seconds
            name = name.arg(x);
            name = name.arg("sec");
        } else if (x >= 60 && !(x%60)) {
            // whole minutes
            name = name.arg(x/60);
            name = name.arg("min");
        } else {
            double secs = x;
            double mins = ((int) secs) / 60;
            secs = secs - mins * 60.0;
            double hrs = ((int) mins) / 60;
            mins = mins - hrs * 60.0;
            QString tm = "%1:%2:%3";
            tm = tm.arg(hrs, 0, 'f', 0);
            tm = tm.arg(mins, 2, 'f', 0, QLatin1Char('0'));
            tm = tm.arg(secs, 2, 'f', 0, QLatin1Char('0'));

            // mins and secs
            name = name.arg(tm);
            name = name.arg("");
        }
        name = name.arg(round(interval.avg));

        QTableWidgetItem *n = new QTableWidgetItem;
        n->setText(name);
        n->setFlags(n->flags() | (Qt::ItemIsEditable));
        resultsTable->setItem(row, 2, n);

        // hidden columns - start, stop
        QString strt = QString("%1").arg(interval.start); // can't use secs as it gets modified
        QTableWidgetItem *st = new QTableWidgetItem;
        st->setText(strt);
        resultsTable->setItem(row, 3, st);

        QString stp = QString("%1").arg(interval.start + x);
        QTableWidgetItem *sp = new QTableWidgetItem;
        sp->setText(stp);
        resultsTable->setItem(row, 4, sp);

        row++;
    }