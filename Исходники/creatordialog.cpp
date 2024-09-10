creatordialog::creatordialog(QString main_table,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::creatordialog)
{
    ui->setupUi(this);
    level=0;

    path=dir.absolutePath();

    relation=false;
    count=false;
    ui->pushButton_add->setVisible(false);
    ui->pushButton_delete->setVisible(false);

    table_constructor=main_table;
    this->setWindowTitle("Kreator relacji");
    ui->stackedWidget->setCurrentIndex(0);

    QImage image(path + "/obrazy/sigma_LOGO_3D.png");
    ui->logo_label->setPixmap(QPixmap::fromImage(image.scaled(200,200,Qt::KeepAspectRatio,Qt::FastTransformation)));

    ui->pushButton->setIcon(QIcon(path + "/obrazy/arrow_right.png"));
    ui->pushButton->setIconSize(QSize(40, 40));

    ui->pushButton_delete->setIcon(QIcon(path + "/obrazy/delete_row.png"));
    ui->pushButton_delete->setIconSize(QSize(20, 20));

    ui->pushButton_add->setIcon(QIcon(path + "/obrazy/add_row.png"));
    ui->pushButton_add->setIconSize(QSize(20, 20));

    ui->checkBox_2->setVisible(true);
    relational_table="";
    relational_table_2="";

    table=main_table;

    if(main_table=="Daneosobowe") {
        ui->checkBox->setText("Maszyny");
        ui->checkBox_2->setVisible(false);
    }
    else if(main_table=="Czesci") {
        ui->checkBox->setText("Maszyny");
        ui->checkBox_2->setVisible(false);
    }
    else if(main_table=="Maszyny") {
        ui->checkBox->setText("Części");
        ui->checkBox_2->setText("Dane osobowe");
    }

    else if(main_table=="Maszyny_has_Daneosobowe") {
        relation=true;
        relational_table_2=main_table;
        on_pushButton_clicked();
    }
    else if(main_table=="Maszyny_has_Czesci") {
        relation=true;
        relational_table_2=main_table;
        on_pushButton_clicked();
    }

    if(relation) {
        ui->pushButton_add->setVisible(true);
        ui->pushButton_delete->setVisible(true);
    }

    connect(this, SIGNAL(rejected()), this, SLOT(closing_creator_dialog()));
}