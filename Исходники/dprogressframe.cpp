void DProgressFrame::slideUsbSeclect() {
    if (m_Active) {
        return;
    }
    else {
        m_Active=true;
    }
    this->layout()->setEnabled(false);
    m_TopShadow->show();
    m_ProcessLabel->setPixmap(QPixmap(""));
    emit changedUsbSeclet();

    int offsetx=frameRect().width(); //inherited from mother
    int offsety=frameRect().height();//inherited from mother
    m_SecondWidget->setGeometry(0, 0, offsetx, offsety);
    offsetx=0;
    //offsety=offsety;

    //re-position the next widget outside/aside of the display area
    QPoint pnext=m_SecondWidget->pos();
    QPoint pnow=m_FirstWidget->pos();
    m_FirstWidget->move(pnow.x(), pnow.y()- offsety + 64+ 36);
    m_SecondWidget->move(pnext.x(), pnext.y() + 64+ 36);
    //make it visible/show
    m_SecondWidget->show();
    m_SecondWidget->raise();
    m_TopShadow->raise();
    //animate both, the now and next widget to the side, using movie framework
    QPropertyAnimation *animnow = new QPropertyAnimation(m_FirstWidget, "pos");
    animnow->setDuration(m_Speed);
    animnow->setEasingCurve(QEasingCurve::OutBack);
    animnow->setStartValue(QPoint(pnow.x(), pnow.y()));
    animnow->setEndValue(QPoint(offsetx+pnow.x(), -offsety+pnow.y() + 64 + 36));

    QPropertyAnimation *animnext = new QPropertyAnimation(m_SecondWidget, "pos");
    animnext->setDuration(m_Speed);
    animnext->setEasingCurve(QEasingCurve::OutBack);
    animnext->setStartValue(QPoint(pnext.x(), offsety+pnext.y()));
    animnext->setEndValue(QPoint(pnext.x(), pnext.y() + 64+ 36));

    m_AnimGroup = new QParallelAnimationGroup;
    m_AnimGroup->addAnimation(animnow);
    m_AnimGroup->addAnimation(animnext);

    connect(m_AnimGroup, SIGNAL(finished()),this,SLOT(slideUsbDone()));

    m_Active=true;
    m_AnimGroup->start();
}