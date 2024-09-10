void TwitterPostWidget::initUi()
{
    TwitterApiPostWidget::initUi();

    KPushButton *btn = buttons().value("btnResend");

    if(btn){
        QMenu *menu = new QMenu(btn);
        QAction *resend = new QAction(i18n("Manual ReSend"), menu);
        connect( resend, SIGNAL(triggered(bool)), SLOT(slotResendPost()) );
        QAction *repeat = new QAction(i18n("Retweet"), menu);
        repeat->setToolTip(i18n("Retweet post using API"));
        connect( repeat, SIGNAL(triggered(bool)), SLOT(repeatPost()) );
        // If person protects their acc, we will use simple adding RT before message
        if (!currentPost().author.isProtected)
            menu->addAction(repeat);
        menu->addAction(resend);
        btn->setMenu(menu);
    }
}