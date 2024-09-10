UserLicense::UserLicense(QWidget *parent)
    : ContentWidget(parent)
{
    setTitle(tr("End User License Agreement"));

    TranslucentFrame* widget = new TranslucentFrame;
    widget->setObjectName("copyrightWidget");
    QVBoxLayout *layout =new QVBoxLayout();

    m_body = new TipsLabel;
    m_body->setWordWrap(true);

    layout->addWidget(m_body);

    widget->setLayout(layout);
    setContent(widget);

    m_body->setText(getLicense(":/systeminfo/license/deepin-end-user-license-agreement_%1.txt", "title"));
}