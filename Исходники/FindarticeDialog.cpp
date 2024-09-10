void FindArticeDialog::CreateVirtualKeyboard()
{
    glKeyboard = new QGridLayout();
    signalMapper = new QSignalMapper(this);
    QStringList slButtonText;
    slButtonText <<"А"<<"Б"<<"В"<<"Г"<<"Д"<<"Е"<<"Ж"<<"З"<<"И"<<"Й"<<"К"<<"Л"<<"М"<<"Н"<<"О";
    slButtonText <<"П"<<"Р"<<"С"<<"Т"<<"У"<<"Ф"<<"Х"<<"Ц"<<"Ч"<<"Ш"<<"Щ"<<"Ъ"<<"Ы"<<"Ь"<<"Э"<<"Ю"<<"Я";

    slButtonText<<"Пробел"<<"<-"<<"Очистить";

    int row, col;
    QWidget *prevTabOrder = ui->tvArticle;
    for (int i= 0;i<slButtonText.size();i++)
    {
        QPushButton *b = new QPushButton(this);
        b->setText(slButtonText.at(i));
        col=i%10; row=i/10;
        b->setProperty("row",row);
        b->setProperty("col",col);
        b->setObjectName("QPushButton_"+QString::number(row)+"_"+QString::number(col));
        b->installEventFilter(this);
        setTabOrder(prevTabOrder,b);
        prevTabOrder = b;
        connect(b, SIGNAL(clicked()), signalMapper, SLOT(map()));
        signalMapper->setMapping(b, b->text());
        glKeyboard->addWidget(b,row,col);
        if(b->text()=="Очистить")
        {
            b->setShortcut(QKeySequence("Del"));
        }
        else
            if(b->text()=="<-")
            {
                b->setShortcut(QKeySequence("Backspace"));
            }
            else
            {
                b->setShortcut(QKeySequence(b->text()));
            }

    }

    connect(signalMapper, SIGNAL(mapped(const QString &)),
                 this, SLOT(VirtualKeyPressed(const QString &)));

    ui->groupBox_2->setLayout(glKeyboard);

    QPushButton* FirstButton = ui->groupBox_2->findChild<QPushButton *>("QPushButton_0_0");
    if (FirstButton)
    {
        FirstButton->setFocus();
    }

}