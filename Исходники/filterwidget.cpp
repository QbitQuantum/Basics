FilterWidget::FilterWidget(QWidget *parent)
    : QLineEdit(parent)
    , m_patternGroup(new QActionGroup(this))
{
    setClearButtonEnabled(true);
    connect(this, SIGNAL(textChanged(QString)), this, SIGNAL(filterChanged()));

    QMenu *menu = new QMenu(this);
    m_caseSensitivityAction = menu->addAction(tr("Case Sensitive"));
    m_caseSensitivityAction->setCheckable(true);
    connect(m_caseSensitivityAction, SIGNAL(toggled(bool)), this, SIGNAL(filterChanged()));

    menu->addSeparator();
    m_patternGroup->setExclusive(true);
    QAction *patternAction = menu->addAction("Fixed String");
    patternAction->setData(QVariant(int(QRegExp::FixedString)));
    patternAction->setCheckable(true);
    patternAction->setChecked(true);
    m_patternGroup->addAction(patternAction);
    patternAction = menu->addAction("Regular Expression");
    patternAction->setCheckable(true);
    patternAction->setData(QVariant(int(QRegExp::RegExp2)));
    m_patternGroup->addAction(patternAction);
    patternAction = menu->addAction("Wildcard");
    patternAction->setCheckable(true);
    patternAction->setData(QVariant(int(QRegExp::Wildcard)));
    m_patternGroup->addAction(patternAction);
    connect(m_patternGroup, SIGNAL(triggered(QAction*)), this, SIGNAL(filterChanged()));

    const QIcon icon = QIcon(QPixmap(":/images/find.png"));
    QToolButton *optionsButton = new QToolButton;
#ifndef QT_NO_CURSOR
    optionsButton->setCursor(Qt::ArrowCursor);
#endif
    optionsButton->setFocusPolicy(Qt::NoFocus);
    optionsButton->setStyleSheet("* { border: none; }");
    optionsButton->setIcon(icon);
    optionsButton->setMenu(menu);
    optionsButton->setPopupMode(QToolButton::InstantPopup);

    QWidgetAction *optionsAction = new QWidgetAction(this);
    optionsAction->setDefaultWidget(optionsButton);
    addAction(optionsAction, QLineEdit::LeadingPosition);
}