CoreConnectionStatusWidget::CoreConnectionStatusWidget(CoreConnection *connection, QWidget *parent)
    : QWidget(parent),
    _coreConnection(connection)
{
    ui.setupUi(this);
    ui.lagLabel->hide();
    ui.sslLabel->hide();
    update();

    connect(coreConnection(), SIGNAL(progressTextChanged(QString)), ui.messageLabel, SLOT(setText(QString)));
    connect(coreConnection(), SIGNAL(progressValueChanged(int)), ui.progressBar, SLOT(setValue(int)));
    connect(coreConnection(), SIGNAL(progressRangeChanged(int, int)), ui.progressBar, SLOT(setRange(int, int)));
    connect(coreConnection(), SIGNAL(progressRangeChanged(int, int)), this, SLOT(progressRangeChanged(int, int)));

    connect(coreConnection(), SIGNAL(stateChanged(CoreConnection::ConnectionState)), SLOT(connectionStateChanged(CoreConnection::ConnectionState)));
    connect(coreConnection(), SIGNAL(connectionError(QString)), ui.messageLabel, SLOT(setText(QString)));
    connect(coreConnection(), SIGNAL(lagUpdated(int)), SLOT(updateLag(int)));
}