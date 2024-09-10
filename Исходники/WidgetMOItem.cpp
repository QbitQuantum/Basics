void WidgetMOItem::initializeGui()
{
    clearGui();
    QGridLayout* itemLayout = dynamic_cast<QGridLayout*>(itemWidget->layout());
    QLabel* label;
    if(item)
    {
        ui->groupItem->setTitle(item->name());
        QWidget* curWidget;

        for(int iF=0;iF<item->getNbFields();iF++)
        {
            curWidget = createEditWidget(item, iF, _editable);
            if(curWidget)
            {
                curWidget->setParent(this);
                fieldEditWidget.insert(iF,curWidget);


                // add it to gui
                label = new QLabel(item->getFieldName(iF),this);
                label->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum);
                itemLayout->addWidget(label,iF,0);
                itemLayout->addWidget(curWidget,iF,1);

                // connect change
                QComboBox* combo = dynamic_cast<QComboBox*>(curWidget);
                if(combo)
                    connect(combo,SIGNAL(thiseditTextChanged(const QString &)),
                            this,SLOT(onValueChanged(const QString &)));

                QSpinBox* spinBox = dynamic_cast<QSpinBox*>(curWidget);
                if(spinBox)
                    connect(spinBox,SIGNAL(valueChanged( const QString & )),
                            this,SLOT(onValueChanged(const QString &)));

                QScienceSpinBox* doubleSpinBox = dynamic_cast<QScienceSpinBox*>(curWidget);
                if(doubleSpinBox)
                    connect(doubleSpinBox,SIGNAL(valueChanged( const QString & )),
                            this,SLOT(onValueChanged(const QString &)));

                QCheckBox* checkBox = dynamic_cast<QCheckBox*>(curWidget);
                if(checkBox)
                    connect(checkBox,SIGNAL(stateChanged(int)),
                            this,SLOT(onCheckChanged(int)));

                QLineEdit* lineEdit = dynamic_cast<QLineEdit*>(curWidget);
                if(lineEdit)
                    connect(lineEdit,SIGNAL(editingFinished()),
                            this,SLOT(onLineEditValueChanged()));
            }
        }
    }
}