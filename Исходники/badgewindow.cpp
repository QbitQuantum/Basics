void BadgeWindow::timer()
{
    DialogTimer dialogTimer;

    bool saveRequest;
    QString taskName;
    QTime elapsedTime;

    saveRequest = dialogTimer.getTaskInfo(taskName, elapsedTime);

    if (saveRequest) {
        DialogTask dialog;
        QSqlRelationalTableModel *taskModel;

        taskModel = new QSqlRelationalTableModel();

        taskModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
        taskModel->setTable("task");
        qDebug() << "Day" << QDate::currentDate().toString("yyyy-MM-dd") << endl;
        taskModel->setFilter("day='" + QDate::currentDate().toString("yyyy-MM-dd") + "'");
        //taskModel.setEditStrategy(QSqlTableModel::OnFieldChange);
        taskModel->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
        taskModel->setHeaderData(1, Qt::Horizontal, QObject::tr("Date"));
        taskModel->setHeaderData(2, Qt::Horizontal, QObject::tr("Elapsed"));
        //taskModel->setHeaderData(3, Qt::Horizontal, QObject::tr("Attivita'"));
        taskModel->setRelation(3, QSqlRelation("attivita", "id", "attivita"));

        taskModel->select();

        // TODO: if current date don't exist create it


        dialog.openTask("Task", "Elapsed", taskModel, QDate::currentDate(), "task", elapsedTime, taskName);

        delete taskModel;
    }
}