SQLOpenProjectDialog::SQLOpenProjectDialog(const QString & host, unsigned int port, const QString & dbname, const QString & user, const QString & password,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SQLOpenProjectDialog)
{
    ui->setupUi(this);
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    m_Host=host;
    m_Port=port;
    m_DBName=dbname;
    m_User=user;
    m_Password=password;

    db.setHostName(m_Host);
    db.setPort(m_Port);
    db.setDatabaseName(m_DBName);
    db.setUserName(m_User);
    db.setPassword(m_Password);

    bool ok=db.open();


    std::cout << db.lastError().databaseText().toStdString() << std::endl;


    if(ok){
    	QSqlRelationalTableModel *model = new QSqlRelationalTableModel(this,db);
    	model->setTable("Project");
    	model->setEditStrategy(QSqlTableModel::OnRowChange);
    	model->select();
    	ui->existingProjectsTableView->setModel(model);
    }else{

    }

    m_Accepted=false;
    m_Project=0;
}