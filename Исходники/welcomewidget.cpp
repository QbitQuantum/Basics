void WelcomeWidget::UpdateRecentProjects(
    const QVector<RecentProject> &recent_projects) {
  ui->tableWidgetRecent->clearContents();
  ui->tableWidgetRecent->setRowCount(recent_projects.count());
  int row = 0;
  QSignalMapper *mapper = new QSignalMapper;
  for (const RecentProject &recent_project : recent_projects) {
    QTableWidgetItem *item_name = new QTableWidgetItem(recent_project.name());
    QTableWidgetItem *item_path = new QTableWidgetItem(recent_project.path());
    QToolButton *erase = new QToolButton;
    erase->setStyleSheet("border: 0;");
    erase->setCursor(QCursor(Qt::PointingHandCursor));
    erase->setIcon(QIcon(":/icons/images/remove.png"));
    erase->setIconSize(QSize(12, 12));
    connect(erase, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(erase, row);
    QFont font = item_name->font();
    font.setBold(true);
    item_name->setFont(font);
    item_name->setToolTip(recent_project.name());
    item_path->setToolTip(recent_project.path());
    ui->tableWidgetRecent->setIndexWidget(
          ui->tableWidgetRecent->model()->index(row, 0), erase);
    ui->tableWidgetRecent->setItem(row, 1, item_name);
    ui->tableWidgetRecent->setItem(row, 2, item_path);
    ++row;
  }
  connect(mapper, SIGNAL(mapped(int)),
          parent_, SLOT(RemoveRecentProject(int)));
}