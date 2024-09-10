TToolBox::TToolBox(QWidget *parent) : QToolBox(parent), m_lastIndex(0)
{
    setFrameStyle(QFrame::StyledPanel);
    connect(this, SIGNAL(currentChanged(int)), this, SLOT(changeIcon(int)));
    createIcon();
}