DialogRecepti::DialogRecepti(QWidget *parent) :    QDialog(parent),    ui(new Ui::DialogRecepti)
{
    ui->setupUi(this);

    ui->listWidget->setSelectionMode(QAbstractItemView::SingleSelection);

    connect(ui->btnOpenFile,SIGNAL(clicked()),this,SLOT(onOpenFile()));
    connect(ui->btnExit,SIGNAL(clicked()),this,SLOT(onExit()));

    char * fn = new char[40];
    strcpy(fn,"/sdcard/recepti/recepti.bet");
    dict = iniparser_load(fn);
    if(dict == NULL)
    {
        QMessageBox::information(this,"iniparser library",QString("Failed to load dictionary from file:\n%1").arg(fn));
        return;
    }

    int n = iniparser_getnsec(dict);
    //QMessageBox::information(this,QString("iniparser"),QString("%1 sections found from file: %2").arg(n).arg(fn));
    if(n>0)
    {
        for(int i =0 ; i<n ; i++)
        {
            QString str(iniparser_getsecname(dict,i));
            ui->listWidget->addItem(str.toUpper());
        }
        ui->listWidget->item(0)->setSelected(true);
    }
}