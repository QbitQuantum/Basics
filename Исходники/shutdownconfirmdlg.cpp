ShutdownConfirmDlg::ShutdownConfirmDlg(QWidget *parent, const ShutdownDialogAction &action)
    : QDialog(parent)
    , m_ui(new Ui::confirmShutdownDlg)
    , m_timeout(15)
    , m_action(action)
{
    m_ui->setupUi(this);

    initText();
    QIcon warningIcon(style()->standardIcon(QStyle::SP_MessageBoxWarning));
    m_ui->warningLabel->setPixmap(warningIcon.pixmap(32));

    if (m_action == ShutdownDialogAction::Exit)
        m_ui->neverShowAgainCheckbox->setVisible(true);
    else
        m_ui->neverShowAgainCheckbox->setVisible(false);

    // Cancel Button
    QPushButton *cancelButton = m_ui->buttonBox->button(QDialogButtonBox::Cancel);
    cancelButton->setFocus();
    cancelButton->setDefault(true);

    // Always on top
    setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
    move(Utils::Misc::screenCenter(this));

    m_timer.setInterval(1000); // 1sec
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(updateSeconds()));

    Utils::Gui::resize(this);
}