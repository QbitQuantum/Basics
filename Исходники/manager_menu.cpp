manager_menu::manager_menu(QWidget *parent, QString db_login) :
    menu_base(parent),
    ui(new Ui::manager_menu)
{
    ui->setupUi(this);
    n_human_picker = new new_human_picker();
    a_new_subject = new add_new_subject();
    a_new_job = new add_new_job();
    ch_job = new change_job();
    ad_positions = new administrate_position();
    exp_position = new expire_position();
    ass_human_to_position = new assign_human_to_position();
    exp_human_on_position = new expire_human_on_position();
    learn_man_menu = new learning_manager_menu();

    //connects
    connect(n_human_picker,SIGNAL(restore_main_menu()),this,SLOT(restore_menu()));
    connect(a_new_subject,SIGNAL(restore_main_menu()),this,SLOT(restore_menu()));
    connect(a_new_job,SIGNAL(restore_main_menu()),this,SLOT(restore_menu()));
    connect(ch_job,SIGNAL(restore_main_menu()),this,SLOT(restore_menu()));
    connect(ad_positions,SIGNAL(restore_main_menu()),this,SLOT(restore_menu()));
    connect(exp_position,SIGNAL(restore_main_menu()),this,SLOT(restore_menu()));
    connect(ass_human_to_position,SIGNAL(restore_main_menu()),this,SLOT(restore_menu()));
    connect(exp_human_on_position,SIGNAL(restore_main_menu()),this,SLOT(restore_menu()));
    connect(learn_man_menu,SIGNAL(restore_main_menu()),this,SLOT(restore_menu()));

    connect(this,SIGNAL(show_add_new_job_dialog()),a_new_job,SLOT(show_add_new_job_dialog()));
    connect(this,SIGNAL(show_change_job_dialog()),ch_job,SLOT(show_change_job_dialog()));
    connect(this,SIGNAL(show_administrating_positions_dialog()),ad_positions,SLOT(show_administrating_positions_dialog()));
    connect(this,SIGNAL(show_expire_position_dialog()),exp_position,SLOT(show_expire_position_dialog()));
    connect(this,SIGNAL(show_assign_human_to_position_dialog()),ass_human_to_position,SLOT(show_assign_human_to_position_dialog()));
    connect(this,SIGNAL(show_expire_human_on_position_dialog()),exp_human_on_position,SLOT(show_expire_human_on_position_dialog()));


    //Get the staff id

    if(db_login.length()) {
        QString qtext("SELECT sl.id_human, fio(last_name, first_name, patronymic) AS fio "
                      "FROM staff_logins sl "
                      "LEFT JOIN people_workers p ON sl.id_human=p.id_human "
                      "WHERE sl.db_login =?;");

        QSqlQuery query;
        query.prepare(qtext);
        query.addBindValue(db_login);
        query.exec();
        if (query.lastError().type()!=QSqlError::NoError){
            QMessageBox msg;
            qDebug() << query.lastError().text();
            msg.setText(query.lastError().text());
            msg.exec();
            return;
        }
        if(query.next()) {
            staff_id = query.value(0).toInt();
            QString fio = query.value(1).toString();
            this->setWindowTitle(fio);
        }
        query.finish();
    }
    else {
        staff_id=0;
    }
}