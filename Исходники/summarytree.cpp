void SummaryTree::addTask()
{
    Task *newTask = new Task;
    newTask->setAnswerFileExtension(settings->getDefaultOutputFileExtension());
    curContest->addTask(newTask);
    newTask->refreshCompilerConfiguration(settings);
    connect(newTask, SIGNAL(problemTitleChanged(QString)),
            this, SLOT(titleChanged(QString)));
    QTreeWidgetItem *newItem = new QTreeWidgetItem(this);
    setCurrentItem(newItem);
    newItem->setFlags(Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    newItem->setText(0, tr("Problem %1").arg(++ addCount));
    editItem(newItem);
}