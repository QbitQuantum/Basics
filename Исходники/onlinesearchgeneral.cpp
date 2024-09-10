OnlineSearchQueryFormGeneral::OnlineSearchQueryFormGeneral(QWidget *parent)
        : OnlineSearchQueryFormAbstract(parent),
      configGroupName(QStringLiteral("Search Engine General"))
{
    QFormLayout *layout = new QFormLayout(this);
    layout->setMargin(0);

    QLabel *label = new QLabel(i18n("Free text:"), this);
    KLineEdit *lineEdit = new KLineEdit(this);
    layout->addRow(label, lineEdit);
    lineEdit->setClearButtonEnabled(true);
    lineEdit->setFocus(Qt::TabFocusReason);
    queryFields.insert(OnlineSearchAbstract::queryKeyFreeText, lineEdit);
    label->setBuddy(lineEdit);
    connect(lineEdit, &KLineEdit::returnPressed, this, &OnlineSearchQueryFormGeneral::returnPressed);

    label = new QLabel(i18n("Title:"), this);
    lineEdit = new KLineEdit(this);
    layout->addRow(label, lineEdit);
    lineEdit->setClearButtonEnabled(true);
    queryFields.insert(OnlineSearchAbstract::queryKeyTitle, lineEdit);
    label->setBuddy(lineEdit);
    connect(lineEdit, &KLineEdit::returnPressed, this, &OnlineSearchQueryFormGeneral::returnPressed);

    label = new QLabel(i18n("Author:"), this);
    lineEdit = new KLineEdit(this);
    layout->addRow(label, lineEdit);
    lineEdit->setClearButtonEnabled(true);
    queryFields.insert(OnlineSearchAbstract::queryKeyAuthor, lineEdit);
    label->setBuddy(lineEdit);
    connect(lineEdit, &KLineEdit::returnPressed, this, &OnlineSearchQueryFormGeneral::returnPressed);

    label = new QLabel(i18n("Year:"), this);
    lineEdit = new KLineEdit(this);
    layout->addRow(label, lineEdit);
    lineEdit->setClearButtonEnabled(true);
    queryFields.insert(OnlineSearchAbstract::queryKeyYear, lineEdit);
    label->setBuddy(lineEdit);
    connect(lineEdit, &KLineEdit::returnPressed, this, &OnlineSearchQueryFormGeneral::returnPressed);

    label = new QLabel(i18n("Number of Results:"), this);
    numResultsField = new QSpinBox(this);
    layout->addRow(label, numResultsField);
    numResultsField->setMinimum(3);
    numResultsField->setMaximum(100);
    numResultsField->setValue(20);
    label->setBuddy(numResultsField);

    loadState();
}