QRibbonSection::QRibbonSection(QWidget *parent, const QString &_title, const QString &_name) : QWidget(parent)
{
    action = NULL;
    col = 0;
    row = 0;
    colBase = 0;
    _index = -1;

    if (&_name) { this->setObjectName(_name); }

    QHBoxLayout *slayout = new QHBoxLayout();
    slayout->setContentsMargins(2,0,2,0);
    slayout->setSpacing(2);
    this->setLayout(slayout);

    //QLabel *lab_line = new QLabel("X", this);
    QFrame *line = new QFrame(this);
    line->setFrameStyle(QFrame::VLine | QFrame::Plain);
    line->setFixedWidth(3);
    line->setContentsMargins(0,3,0,5);
    line->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QString sheet = line->styleSheet();
    sheet.append("QFrame { color: #c0c0c0; }");
    line->setStyleSheet(sheet);

    QWidget *wvbox = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout();
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(0);
    wvbox->setLayout(layout);

    buttons = new QWidget(wvbox);
    QGridLayout *blayout = new QGridLayout();
    blayout->setContentsMargins(0,0,0,0);
    blayout->setSpacing(2);
    buttons->setLayout(blayout);

    QHBoxLayout *lfooter = new QHBoxLayout();
    lfooter->setContentsMargins(0,0,0,0);
    QWidget *footer = new QWidget(wvbox);
    footer->setLayout(lfooter);

    if (&title == 0) {
        title = new QLabel("", footer);
    } else {
        title = new QLabel(_title, footer);
    }
    title->setAlignment(Qt::AlignCenter);
    QFont titleFont = title->font();
    titleFont.setPointSize(titleFont.pointSize()*0.98f);
    title->setFont(titleFont);

    {
        QIcon *dtl = new QIcon(":/icons/QRibbonDetails.svg");
        details = new QRibbonButton(*dtl, "", footer);
        delete dtl;
    }
    details->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    QFont f;
    QFontMetrics metrics(f);
    QSize is = QSize(metrics.boundingRect("^").width(), metrics.boundingRect("X").height());
    is = QSize(is.width()*2, is.height());
    details->setIconSize(is);
    details->setMaximumSize(is);
    details->setVisible(false);
    QObject::connect(details, SIGNAL(clicked()), this, SLOT(activateDetails()));


    lfooter->addWidget(title, 1);
    lfooter->addWidget(details);

    layout->addWidget(buttons, 1);
    layout->addWidget(footer);

    slayout->addWidget(wvbox, 1);
    slayout->addWidget(line, 1);
}