TabbedMainWindow::TabbedMainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::TabbedMainWindow)
{
    clustertab = new ClusterTab();
    //anothertab = new ClusterTab();
    ui->setupUi(this);
    //ui->tabWidgetClusters->addTab(clustertab, tr("Tab1"));

    for (int i = 0; i < clusterNamesF.count(); i++) {
        ClusterTab * tab = new ClusterTab();
        myList.append(tab->listWidget);
        myList2.append(tab->listWidget2);
        tab->listWidget->setStyleSheet("QListView::item:selected:active { background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(58, 58, 58, 255), stop:1 rgba(90, 90, 90, 255)) } QListView::item:hover { background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #FAFBFE, stop: 1 #DCDEF1); }");
        tab->listWidget2->setStyleSheet("QListView::item:selected:active { background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(58, 58, 58, 255), stop:1 rgba(90, 90, 90, 255)) } QListView::item:hover { background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #FAFBFE, stop: 1 #DCDEF1); }");
        tab->listWidget->setSelectionMode(QAbstractItemView::MultiSelection);
        tab->listWidget2->setSelectionMode(QAbstractItemView::MultiSelection);
        tab->setHostname(Variables::hostNamesF[i]);
        tab->setClusterName(Variables::clusterNamesF[i]);
        tab->setUsernamePassword(Variables::usernamePasswordsF[i]);
        ui->tabWidgetClusters->addTab(tab, Variables::clusterNamesF[i]);
        //ui->tabWidgetClusters->addTab(new ClusterTab(), QString::fromStdString("Tab") + QString::fromStdString(std::to_string(i+1)));
    }
    QStringList queryTypeList, queryParameter1;
    queryParameter1 << "Equals" << "Contains" << "Begins with" << "Ends with" << "Is Empty" << "Is not Empty";
    queryTypeList << "Firstname" << "Middlename" << "Lastname" << "UserID" << "Is in Cluster" << "Telephone Number";
    ui->comboBoxQueryType->addItems(queryTypeList);
    ui->comboBoxQueryParameter->addItems(queryParameter1);
}