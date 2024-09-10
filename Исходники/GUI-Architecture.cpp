void MainWindow::setProjectsInMenu() {
    QStandardItem* parent = projectsModel->invisibleRootItem();
    ProjectFactory* pf = &(ProjectFactory::getInstance());
    for (Iterator<Project> it = pf->getIterator(); !(it.isDone()); it.next()) {
        QStandardItem* temp = new QStandardItem(it.current().getId());  // gonna need to manage those items, and delete them at the end of the process
        temp->setFlags(temp->flags() & ~Qt::ItemIsEditable);
        parent->appendRow(temp);
        //parent = temp;
        for(Iterator<Task> it2 = it.current().getIterator(); !(it2.isDone()); it2.next()) {
            QStandardItem* temp2 = new QStandardItem(it2.current().getId());
            temp2->setFlags(temp2->flags() & ~Qt::ItemIsEditable);
            temp->appendRow(temp2);
            if (it2.current().getTaskType()==COMPOSITE) {
                for (Iterator<Task> it3 = dynamic_cast<CompositeTask&>(it2.current()).getIterator(); !(it3.isDone()); it3.next()) {
                    injectSubTaskInModel(temp2,it3.current());
                }
            }
        }
    }
}