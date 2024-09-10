EmoticonsWidget::EmoticonsWidget(QWidget *parent) :
    QMenu(parent)
{
    setStyleSheet(Style::getStylesheet(":/ui/emoticonWidget/emoticonWidget.css"));
    setLayout(&layout);
    layout.addWidget(&stack);

    QWidget* pageButtonsContainer = new QWidget;
    QHBoxLayout* buttonLayout = new QHBoxLayout;
    pageButtonsContainer->setLayout(buttonLayout);

    layout.addWidget(pageButtonsContainer);

    const int maxCols = 5;
    const int maxRows = 3;
    const int itemsPerPage = maxRows * maxCols;

    const QList<QStringList>& emoticons = SmileyPack::getInstance().getEmoticons();
    int itemCount = emoticons.size();
    int pageCount = ceil(float(itemCount) / float(itemsPerPage));
    int currPage = 0;
    int currItem = 0;
    int row = 0;
    int col = 0;

    // create pages
    buttonLayout->addStretch();
    for (int i = 0; i < pageCount; i++)
    {
        QGridLayout* pageLayout = new QGridLayout;
        pageLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding), maxRows, 0);
        pageLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum), 0, maxCols);

        QWidget* page = new QWidget;
        page->setLayout(pageLayout);
        stack.addWidget(page);

        // page buttons are only needed if there is more than 1 page
        if (pageCount > 1)
        {
            QRadioButton* pageButton = new QRadioButton;
            pageButton->setProperty("pageIndex", i);
            pageButton->setCursor(Qt::PointingHandCursor);
            pageButton->setChecked(i == 0);
            buttonLayout->addWidget(pageButton);

            connect(pageButton, &QRadioButton::clicked, this, &EmoticonsWidget::onPageButtonClicked);
        }
    }
    buttonLayout->addStretch();

    for (const QStringList& set : emoticons)
    {
        QPushButton* button = new QPushButton;
        button->setIcon(SmileyPack::getInstance().getAsIcon(set[0]));
        button->setToolTip(set.join(" "));
        button->setProperty("sequence", set[0]);
        button->setCursor(Qt::PointingHandCursor);
        button->setFlat(true);

        connect(button, &QPushButton::clicked, this, &EmoticonsWidget::onSmileyClicked);

        qobject_cast<QGridLayout*>(stack.widget(currPage)->layout())->addWidget(button, row, col);

        col++;
        currItem++;

        // next row
        if (col >= maxCols)
        {
            col = 0;
            row++;
        }

        // next page
        if (currItem >= itemsPerPage)
        {
            row = 0;
            currItem = 0;
            currPage++;
        }
    }

    // calculates sizeHint
    layout.activate();
}