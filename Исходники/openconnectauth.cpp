void OpenconnectAuthWidget::validatePeerCert(const QString &fingerprint,
                                             const QString &peerCert, const QString &reason, bool *accepted)
{
    Q_D(OpenconnectAuthWidget);

    const QString host = QLatin1String(openconnect_get_hostname(d->vpninfo));
    const QString port = QString::number(openconnect_get_port(d->vpninfo));
    const QString key = QString("certificate:%1:%2").arg(host,  port);
    const QString value = d->secrets.value(key);

#if !OPENCONNECT_CHECK_VER(5,0)
#define openconnect_check_peer_cert_hash(v,d) strcmp(d, fingerprint.toUtf8().data())
#endif

    if (openconnect_check_peer_cert_hash(d->vpninfo, value.toUtf8().data())) {
        QWidget *widget = new QWidget();
        QVBoxLayout *verticalLayout;
        QHBoxLayout *horizontalLayout;
        QLabel *icon;
        QLabel *infoText;
        QTextBrowser *certificate;

        verticalLayout = new QVBoxLayout(widget);
        horizontalLayout = new QHBoxLayout(widget);
        icon = new QLabel(widget);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(icon->sizePolicy().hasHeightForWidth());
        icon->setSizePolicy(sizePolicy);
        icon->setMinimumSize(QSize(48, 48));
        icon->setMaximumSize(QSize(48, 48));

        horizontalLayout->addWidget(icon);

        infoText = new QLabel(widget);
        infoText->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout->addWidget(infoText);

        verticalLayout->addLayout(horizontalLayout);

        certificate = new QTextBrowser(widget);
        certificate->setTextInteractionFlags(Qt::TextSelectableByMouse);
        certificate->setOpenLinks(false);

        verticalLayout->addWidget(certificate);

        icon->setPixmap(QIcon::fromTheme("dialog-information").pixmap(KIconLoader::SizeLarge));
        infoText->setText(i18n("Check failed for certificate from VPN server \"%1\".\n"
                               "Reason: %2\nAccept it anyway?", openconnect_get_hostname(d->vpninfo),reason));
        infoText->setWordWrap(true);
        certificate->setText(peerCert);

        QPointer<QDialog> dialog = new QDialog(this);
        dialog.data()->setWindowModality(Qt::WindowModal);
        dialog->setLayout(new QVBoxLayout);
        QDialogButtonBox* buttons = new QDialogButtonBox(QDialogButtonBox::Ok|QDialogButtonBox::Cancel, dialog);
        connect(buttons, &QDialogButtonBox::accepted, dialog.data(), &QDialog::accept);
        connect(buttons, &QDialogButtonBox::rejected, dialog.data(), &QDialog::reject);
        dialog->layout()->addWidget(widget);
        dialog->layout()->addWidget(buttons);
        if(dialog.data()->exec() == QDialog::Accepted) {
            *accepted = true;
        } else {
            *accepted = false;
        }
        if (dialog) {
            dialog.data()->deleteLater();
        }
        widget->deleteLater();
    } else {
        *accepted = true;
    }
    if (*accepted) {
        d->secrets.insert(key, QString(fingerprint));
    }
    d->mutex.lock();
    d->workerWaiting.wakeAll();
    d->mutex.unlock();
}