void VcsEventWidgetPrivate::diffToPrevious()
{
    KDevelop::VcsEvent ev = m_logModel->eventForIndex( m_contextIndex );
    KDevelop::VcsRevision prev = KDevelop::VcsRevision::createSpecialRevision(KDevelop::VcsRevision::Previous);
    KDevelop::VcsJob* job = m_iface->diff( m_url, prev, ev.revision() );

    VcsDiffWidget* widget = new VcsDiffWidget( job );
    widget->setRevisions( prev, ev.revision() );
    QDialog* dlg = new QDialog( q );

    widget->connect(widget, &VcsDiffWidget::destroyed, dlg, &QDialog::deleteLater);

    dlg->setWindowTitle( i18n("Difference To Previous") );

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok);
    auto mainWidget = new QWidget;
    QVBoxLayout *mainLayout = new QVBoxLayout;
    dlg->setLayout(mainLayout);
    mainLayout->addWidget(mainWidget);
    QPushButton *okButton = buttonBox->button(QDialogButtonBox::Ok);
    okButton->setDefault(true);
    okButton->setShortcut(Qt::CTRL | Qt::Key_Return);
    dlg->connect(buttonBox, &QDialogButtonBox::accepted, dlg, &QDialog::accept);
    dlg->connect(buttonBox, &QDialogButtonBox::rejected, dlg, &QDialog::reject);
    mainLayout->addWidget(widget);
    mainLayout->addWidget(buttonBox);

    dlg->show();
}