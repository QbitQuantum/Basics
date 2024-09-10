Security8021xAuthWidget::Security8021xAuthWidget(Knm::Connection* connection, const QStringList &secrets, QWidget * parent)
: SettingWidget(*new Security8021xAuthWidgetPrivate, parent)
{
    Q_D(Security8021xAuthWidget);
    d->connection = connection;
    d->setting = static_cast<Knm::Security8021xSetting *>(connection->setting(Knm::Setting::Security8021x));

    d->layout = new QFormLayout(this);
    this->setLayout(d->layout);

    if (secrets.contains(QLatin1String("password"))) {
        QLabel *label = new QLabel(this);
        label->setText(i18n("Password:"******"setting", "password");
        d->layout->addRow(label, lineEdit);
    }
    if (secrets.contains(QLatin1String("private-key-password"))) {
        QLabel *label = new QLabel(this);
        label->setText(i18n("Private Key Password:"******"setting", "private-key-password");
        d->layout->addRow(label, lineEdit);
    }
    if (secrets.contains(QLatin1String("phase2-private-key-password"))) {
        QLabel *label = new QLabel(this);
        label->setText(i18n("Phase 2 Private Key Password:"******"setting", "phase2-private-key-password");
        d->layout->addRow(label, lineEdit);
    }

    for (int i = 0; i < d->layout->rowCount(); i++)
    {
        KLineEdit *le = qobject_cast<KLineEdit*>(d->layout->itemAt(i, QFormLayout::FieldRole)->widget());
        if (le && le->text().isEmpty()) {
            le->setFocus(Qt::OtherFocusReason);
            break;
        }
    }

    QCheckBox *showPasswords = new QCheckBox(this);
    showPasswords->setText(i18n("&Show password"));
    d->layout->setWidget(d->layout->rowCount(), QFormLayout::FieldRole, showPasswords);
    connect(showPasswords, SIGNAL(toggled(bool)), this, SLOT(showPasswordsToggled(bool)));
    d->layout->addItem(new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding));
}