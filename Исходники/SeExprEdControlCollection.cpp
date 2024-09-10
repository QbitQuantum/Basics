    SeExprEdAddDialog::SeExprEdAddDialog(int& count,QWidget* parent)
        :QDialog(parent)
    {
        QVBoxLayout *verticalLayout;
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(3);
        verticalLayout->setMargin(3);
        setLayout(verticalLayout);
        QHBoxLayout *horizontalLayout = new QHBoxLayout();

        horizontalLayout->addWidget(new QLabel("Variable"));
        // TODO would be nice to unique this over multiple sessions
        variableName = new QLineEdit(QString("$var%1").arg(count++));

        horizontalLayout->addWidget(variableName);
        verticalLayout->addLayout(horizontalLayout);

        tabWidget = new QTabWidget();

        // Curve
        {
            QWidget* curveTab = new QWidget();
            QFormLayout* curveLayout = new QFormLayout(curveTab);
            curveLayout->setWidget(0,QFormLayout::LabelRole,new QLabel("Lookup"));
            curveLookup=new QLineEdit("$u");
            curveLayout->setWidget(0,QFormLayout::FieldRole,curveLookup);
            tabWidget->addTab(curveTab, QString("Curve"));
        }

        // Color Curve
        {
            QWidget* colorCurveTab = new QWidget();
            QFormLayout* colorCurveLayout = new QFormLayout(colorCurveTab);
            colorCurveLayout->setWidget(0,QFormLayout::LabelRole,new QLabel("Lookup"));
            colorCurveLookup=new QLineEdit("$u");
            colorCurveLayout->setWidget(0,QFormLayout::FieldRole,colorCurveLookup);
            tabWidget->addTab(colorCurveTab, QString("Color Curve"));
        }

        // Integer
        {
            QWidget* intTab = new QWidget();
            QFormLayout* intFormLayout = new QFormLayout(intTab);
            intFormLayout->setWidget(0, QFormLayout::LabelRole, new QLabel("Default"));
            intFormLayout->setWidget(1, QFormLayout::LabelRole, new QLabel("Min"));
            intFormLayout->setWidget(2, QFormLayout::LabelRole, new QLabel("Max"));
            intDefault = new QLineEdit("0");
            intFormLayout->setWidget(0, QFormLayout::FieldRole, intDefault);
            intMin = new QLineEdit("0");
            intFormLayout->setWidget(1, QFormLayout::FieldRole, intMin);
            intMax = new QLineEdit("10");
            intFormLayout->setWidget(2, QFormLayout::FieldRole, intMax);
            tabWidget->addTab(intTab, QString("Int"));
        }

        // Float
        {
            QWidget* floatTab = new QWidget();
            QFormLayout* floatFormLayout = new QFormLayout(floatTab);
            floatFormLayout->setWidget(0, QFormLayout::LabelRole, new QLabel("Default"));
            floatFormLayout->setWidget(1, QFormLayout::LabelRole, new QLabel("Min"));
            floatFormLayout->setWidget(2, QFormLayout::LabelRole, new QLabel("Max"));
            floatDefault = new QLineEdit("0");
            floatFormLayout->setWidget(0, QFormLayout::FieldRole, floatDefault);
            floatMin = new QLineEdit("0");
            floatFormLayout->setWidget(1, QFormLayout::FieldRole, floatMin);
            floatMax = new QLineEdit("1");
            floatFormLayout->setWidget(2, QFormLayout::FieldRole, floatMax);

            tabWidget->addTab(floatTab, QString("Float"));
        }

        // Vector
        {
            QWidget* vectorTab = new QWidget();
            QFormLayout* vectorFormLayout = new QFormLayout(vectorTab);
            vectorFormLayout->setWidget(0, QFormLayout::LabelRole, new QLabel("Default"));
            vectorFormLayout->setWidget(1, QFormLayout::LabelRole, new QLabel("Min"));
            vectorFormLayout->setWidget(2, QFormLayout::LabelRole, new QLabel("Max"));
            vectorDefault0 = new QLineEdit("0");
            vectorDefault1 = new QLineEdit("0");
            vectorDefault2 = new QLineEdit("0");
            QHBoxLayout* compLayout=new QHBoxLayout();
            compLayout->addWidget(vectorDefault0);
            compLayout->addWidget(vectorDefault1);
            compLayout->addWidget(vectorDefault2);
            vectorFormLayout->setLayout(0, QFormLayout::FieldRole, compLayout);
            vectorMin = new QLineEdit("0");
            vectorFormLayout->setWidget(1, QFormLayout::FieldRole, vectorMin);
            vectorMax = new QLineEdit("1");
            vectorFormLayout->setWidget(2, QFormLayout::FieldRole, vectorMax);

            tabWidget->addTab(vectorTab, QString("Vector"));
        }

        // Color
        {
            QWidget* colorTab = new QWidget();
            QFormLayout* colorLayout = new QFormLayout(colorTab);
            colorWidget=new QPushButton();
            colorWidget->setFixedWidth(30);
            colorWidget->setFixedWidth(30);
            colorLayout->setWidget(0,QFormLayout::LabelRole,new QLabel("Color"));
            colorLayout->setWidget(0,QFormLayout::FieldRole,colorWidget);
            color=Qt::red;
            QPixmap colorPix(30,30);
            colorPix.fill(color);
            colorWidget->setIcon(QIcon(colorPix));
            tabWidget->addTab(colorTab, QString("Color"));

            connect(colorWidget,SIGNAL(clicked()),this,SLOT(colorChooseClicked()));
        }

        // Color Swatch
        {
            QWidget* swatchTab = new QWidget();
            QFormLayout* swatchLayout = new QFormLayout(swatchTab);
            swatchLookup=new QLineEdit("$u");
            swatchLayout->setWidget(0,QFormLayout::LabelRole,new QLabel("Lookup"));
            swatchLayout->setWidget(0,QFormLayout::FieldRole,swatchLookup);
            rainbowPaletteBtn = new QRadioButton("Rainbow");
            rainbowPaletteBtn->setChecked(true);
            grayPaletteBtn = new QRadioButton("Shades of Gray");
            swatchLayout->setWidget(1,QFormLayout::LabelRole,new QLabel("Colors"));
            swatchLayout->setWidget(1,QFormLayout::FieldRole,rainbowPaletteBtn);
            swatchLayout->setWidget(2,QFormLayout::LabelRole,new QLabel(""));
            swatchLayout->setWidget(2,QFormLayout::FieldRole,grayPaletteBtn);
            tabWidget->addTab(swatchTab, QString("Swatch"));
        }

        // String literal
        {
            QWidget* stringTab = new QWidget();
            QFormLayout* stringLayout = new QFormLayout(stringTab);
            stringTypeWidget=new QComboBox();
            stringTypeWidget->addItem("string");
            stringTypeWidget->addItem("file");
            stringTypeWidget->addItem("directory");
            stringDefaultWidget=new QLineEdit();
            stringNameWidget=new QLineEdit("str1");

            stringLayout->setWidget(0,QFormLayout::LabelRole,new QLabel("String Name"));
            stringLayout->setWidget(0,QFormLayout::FieldRole,stringNameWidget);
            stringLayout->setWidget(1,QFormLayout::LabelRole,new QLabel("String Type"));
            stringLayout->setWidget(1,QFormLayout::FieldRole,stringTypeWidget);
            stringLayout->setWidget(2,QFormLayout::LabelRole,new QLabel("String Default"));
            stringLayout->setWidget(3,QFormLayout::FieldRole,stringDefaultWidget);

            tabWidget->addTab(stringTab, QString("String"));
        }

#ifdef SEEXPR_USE_ANIMLIB
        // Anim Curve
        {
            QWidget* curveTab = new QWidget();
            QFormLayout* curveLayout = new QFormLayout(curveTab);
            curveLayout->setWidget(0,QFormLayout::LabelRole,new QLabel("Lookup"));
            curveLayout->setWidget(1,QFormLayout::LabelRole,new QLabel("Link"));
            animCurveLookup=new QLineEdit("$frame");
            animCurveLink=new QLineEdit("");
            curveLayout->setWidget(0,QFormLayout::FieldRole,animCurveLookup);
            curveLayout->setWidget(1,QFormLayout::FieldRole,animCurveLink);
            tabWidget->addTab(curveTab, QString("AnimCurve"));
        }
#endif

        verticalLayout->addWidget(tabWidget);

        QDialogButtonBox* buttonBox = new QDialogButtonBox();
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        QObject::connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

        tabWidget->setCurrentIndex(0);

    }