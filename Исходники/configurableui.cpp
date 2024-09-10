ConfLineEdit::ConfLineEdit(QWidget *parent, const QString &name, const QString &placeholderText,
                           const QVariant &value, QString &mask, const QString &parameterName)
    : BaseConfComponent(parameterName, parent)
{
    lineEdit = new QLineEdit();
    connect(lineEdit, SIGNAL(textChanged(QString)), this, SLOT(lineEditTextChanged(QString)));
    lineEdit->setText(value.toString());
    if (name.length() != 0)
    {
        lineEdit->setObjectName(name);
    } else {
        QMessageBox::warning(parent, STRS::incorrectName, QtUtils::stringFormat(STRS::specifyName, STRS::lineEdit));
    }

    lineEdit->setPlaceholderText(placeholderText);

    QRegExpValidator* validator = new QRegExpValidator(QRegExp(mask), this);
    lineEdit->setValidator(validator);

    getLayout()->addWidget(lineEdit);
    setLayout(getLayout());
}