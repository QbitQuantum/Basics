void
TodaysPlanWorkoutDownload::refreshClicked()
{
    // reset download information
    status->setText("");
    downloads = fails = 0;
    download->show();
    close->show();
    files->clear(); // delete existing entries
    QString error;

    // check period - download is only possible for future workouts !
    if (from->date() < QDate::currentDate()) {
        QMessageBox::warning(this, tr("Today's Plan Workout Download"), QString(tr("You can only download future workouts, 'From' will be adjusted to current date")));
        from->setDate(QDate::currentDate());
    }
    if (from->date() > to->date()) {
        QMessageBox::warning(this, tr("Today's Plan Workout Download"), QString(tr("Invalid date range, please check your input.")));
        return;
    }

    QList<TodaysPlanWorkoutListEntry*> workouts = getFileList(error, from->dateTime(), to->dateTime());
    if (error != "") {
        QMessageBox::warning(this, tr("Today's Plan Workout Download"), QString(tr("The following error occured: %1").arg(error)));
        return;
    }


    foreach(TodaysPlanWorkoutListEntry *item, workouts) {

       QTreeWidgetItem *add = new QTreeWidgetItem(files->invisibleRootItem());
       add->setFlags(add->flags() | Qt::ItemIsEditable);

       // selector
       QCheckBox *checkBox = new QCheckBox("", this);
       checkBox->setChecked(true);
       files->setItemWidget(add, 0, checkBox);

       add->setText(1, item->planDate.toString(tr("dd MMM yyyy")));
       add->setText(2, item->description);
       add->setText(3, QString::number(item->tScore));
       add->setText(4, time_to_string_minutes(item->duration));

       // interval action
       add->setText(5, tr("Download"));

       // hide away the id
       add->setText(6, QString("%1").arg(item->workoutId));
    }