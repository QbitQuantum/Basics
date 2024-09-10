ReportList::ReportList(BoxType type, bool sortByScore, QWidget *parent)
    : QMainWindow(parent)
{
    this->sort = sortByScore;
    printAction = new QAction("&Print...", this);
    QMenu* fileMenu = menuBar()->addMenu("&File");
    fileMenu->addAction(printAction);
    connect(printAction, SIGNAL(triggered()), this, SLOT(print()));

    QWidget* central = new QWidget();
    this->setCentralWidget(central);

    QHBoxLayout* mainLayout = new QHBoxLayout();
    central->setLayout(mainLayout);

    this->reports = new QStackedWidget();
    int size = 0;

    if(type == employee)
    {
        employeeData = DataInterface::getEmployees();
        if(sortByScore)
        {
            this->setWindowTitle("Employee View - Sorted By Average Score");
            qSort(employeeData.begin(), employeeData.end());
        } else
        {
            this->setWindowTitle("Employee View");
        }

        size = employeeData.size();
        for(int i = 0; i < size; i++)
        {
            EmployeeReportBox* box = new EmployeeReportBox(employeeData.at(i), i, size);
            reports->addWidget(box);
        }
    } else if(type == employer)
    {
        this->setWindowTitle("Employer View");
        employerData = DataInterface::getEmployers();
        size = employerData.size();
        for(int i = 0; i < size; i++)
        {
            EmployerReportBox* box = new EmployerReportBox(employerData.at(i), i, size);
            reports->addWidget(box);
        }
    } else
    {
        QMessageBox::information(this, "Failed To Read Data", "Failed to read the data from the file.");
        return;
    }


    QScrollBar *scrollBar = new QScrollBar(Qt::Vertical);
    scrollBar->setRange(0, size - 1);
    scrollBar->setValue(0);
    scrollBar->setFocusPolicy(Qt::WheelFocus);


    connect(scrollBar, SIGNAL(valueChanged(int)), this, SLOT(moveToBox(int)));

    this->setFixedHeight(370);

    reports->setCurrentIndex(0);

    mainLayout->addWidget(reports);
    mainLayout->addWidget(scrollBar);

}