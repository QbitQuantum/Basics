SQLConfigWindow::SQLConfigWindow()
{
    setAttribute(Qt::WA_DeleteOnClose, true);

    QVBoxLayout *v = new QVBoxLayout(this);

    QLabel *desc = new QLabel(tr("<b><span style='color:red'>Don't touch anything if you've no clue what SQL is!</span></b><br /><br />For any change to have effect, you need to restart the server."
                                 "<br />If you change the settings without knowledge of what you are doing, you'll probably end up without any users stored anymore.<br/><br/>SQLite is the "
                                 "only system fully supported by default. PostGreSQL needs an external installation, and you then just have to put the .dlls in that are located in PostGreSQL's bin folder in the server folder. "
                                 "MySQL needs the user to get the right DLLs, the MySQL driver and to install a MySQL database too (it is advised to be on linux to do this as this is far less complicated)."));
    desc->setWordWrap(true);
    v->addWidget(desc);

    QSettings s("config", QSettings::IniFormat);

    b = new QComboBox();
    b->addItem("SQLite");
    b->addItem("PostGreSQL");
    b->addItem("MySQL");
    v->addLayout(new QSideBySide(new QLabel(tr("SQL Database type: ")), b));
    if (s.value("sql_driver").toInt() == SQLCreator::PostGreSQL) {
        b->setCurrentIndex(1);
    } else if (s.value("sql_driver").toInt() == SQLCreator::MySQL) {
        b->setCurrentIndex(2);
    }

    name = new QLineEdit();
    name->setText(s.value("sql_db_name").toString());
    v->addLayout(new QSideBySide(new QLabel(tr("Database name: ")), name));
    
    schema = new QLineEdit();
    schema->setText(s.value("sql_db_schema", "").toString());
    v->addLayout(new QSideBySide(new QLabel(tr("Schema: ")), schema));

    user = new QLineEdit();
    user->setText(s.value("sql_db_user").toString());
    v->addLayout(new QSideBySide(new QLabel(tr("User: "******"sql_db_pass").toString());
    v->addLayout(new QSideBySide(new QLabel(tr("Password: "******"sql_db_host").toString());
    v->addLayout(new QSideBySide(new QLabel(tr("Host: ")), host));

    port = new QSpinBox();
    port->setRange(0, 65535);
    port->setValue(s.value("sql_db_port").toInt());
    v->addLayout(new QSideBySide(new QLabel(tr("Port: ")), port));

    doVacuum = new QCheckBox("Do VACUUM on start if possible (recommended).");
    doVacuum->setChecked(s.value("sql_do_vacuum", true).toBool());
    v->addWidget(doVacuum);

    QPushButton *exporting = new QPushButton(tr("&Export"));
    connect(exporting, SIGNAL(clicked()), SLOT(exportDatabase()));

    QPushButton *apply = new QPushButton(tr("&Apply"));
    connect(apply, SIGNAL(clicked()), this, SLOT(apply()));

    v->addLayout(new QSideBySide(exporting, apply));

    connect(b, SIGNAL(activated(int)), SLOT(changeEnabled()));
    changeEnabled();
}