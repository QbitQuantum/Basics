void QMessageWidgets::initUI()
{
    QGridLayout *gridLay = getLayout();
    QFrame      *hline = new QFrame(getCenterPanel());
    m_lbmsg   = new QLabel(this);
    m_lbmsg->setWordWrap(true);
    gridLay->setContentsMargins(5,2,2,10);
    hline->setFrameShape(QFrame::HLine);
    hline->setFrameShadow(QFrame::Sunken);
    gridLay->addWidget(hline,0,0,1,1);
    gridLay->addWidget(m_lbmsg,1,0,1,1);

    setTitleStyle("font: 75 12pt \"Aharoni\";");
}