    void CChatWidget::addMsg(const QString& vMsg, const QString& vSenderName, EMsgSendRecv vSendRecv)
    {
        QLabel* pMsgItem = new QLabel(m_pRecordWidget);
        QGridLayout* pMsgLayout = new QGridLayout(pMsgItem);
        pMsgItem->setLayout(pMsgLayout);
        QString strTime = QTime::currentTime().toString("HH:mm:ss");

        Qt::Alignment align = (vSendRecv == eSend) ? Qt::AlignRight : Qt::AlignLeft;
        pMsgLayout->addWidget(new QLabel(strTime, pMsgItem), 0, 0, 1, 10, align);
        pMsgLayout->addWidget(new QLabel(vMsg, pMsgItem), 1, 0, 1, 8, align);
        pMsgLayout->addWidget(new QLabel(vSenderName, pMsgItem), 1, 9, 1, 1, align);
        pMsgItem->setFixedHeight(60);

        m_pRecordWidget->setFixedHeight(m_pRecordWidget->height() + pMsgItem->height());
        m_pRecordWidget->layout()->addWidget(pMsgItem);

        m_psbRecord->setMaximumHeight(this->height());
        m_psbRecord->setSliderPosition(m_psbRecord->maximum());
    }