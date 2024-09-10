TextEditor::TextEditor(QWidget *parent): QPlainTextEdit(parent) {
    connect(this, SIGNAL(textChanged()),            this, SLOT(UpdateDocumentStatus()));

    LineCountArea = new LineNumberArea(this);
    connect(this, SIGNAL(blockCountChanged(int)),   this, SLOT(UpdateLineNumberAreaWidth(int)));
    connect(this, SIGNAL(updateRequest(QRect,int)), this, SLOT(UpdateLineNumberArea(QRect,int)));
    UpdateLineNumberAreaWidth(0);

//    connect(this, SIGNAL(cursorPositionChanged()),
//            this, SLOT(Highlight_Current_Line()));
    connect(this, SIGNAL(cursorPositionChanged()),
            this, SLOT(bracketValidate()));

    setFont(QFont("Monaco", 12));

    setTabSize(4);

    Size = 0;
    Counter = 0;
    Start = 0;
    End = 0;

    // Setup autocomplete
    minCompleterLength = 1;

    c = new QCompleter(this);
//            c->setModelSorting(QCompleter::CaseInsensitivelySortedModel);
    c->setCompletionMode(QCompleter::PopupCompletion);
    c->setCaseSensitivity(Qt::CaseInsensitive);
    c->setWrapAround(false);
    c->setWidget(this);
    c->popup()->setObjectName("autocomplete");

    completerModel = new QStringListModel(getWords(), c);
    c->setModel(completerModel);

    connect(this, SIGNAL(textChanged()),
            this, SLOT(updateCompleterModel()));

    QTextOption option = document()->defaultTextOption();

    bool on = false;
    if (on) {
        option.setFlags(option.flags() | QTextOption::ShowTabsAndSpaces);
    } else {
        option.setFlags(option.flags() & ~QTextOption::ShowTabsAndSpaces);
    }
    option.setFlags(option.flags() | QTextOption::AddSpaceForLineAndParagraphSeparators);
    document()->setDefaultTextOption(option);

    setTabsAsSpaces(true);

    bracketMismatchFormat = currentCharFormat();
    bracketMismatchFormat.setBackground(QColor(255, 223, 223));

    bracketMatchFormat = currentCharFormat();
    bracketMatchFormat.setBackground(QColor(158, 209, 255));
}