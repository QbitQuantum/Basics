QWidget* ToolAction::createWidget( QWidget *parent )
{
    QToolBar *toolBar = qobject_cast< QToolBar * >( parent );
    if ( !toolBar )
        return 0;

    QToolButton *button = new QToolButton( toolBar );
    button->setAutoRaise( true );
    button->setFocusPolicy( Qt::NoFocus );
    button->setIconSize( toolBar->iconSize() );
    button->setToolButtonStyle( toolBar->toolButtonStyle() );
    button->setPopupMode( QToolButton::DelayedPopup );
    button->setMenu( new QMenu( button ) );
    button->setCheckable( true );
    connect(toolBar, &QToolBar::iconSizeChanged, button, &QToolButton::setIconSize);
    connect(toolBar, &QToolBar::toolButtonStyleChanged, button, &QToolButton::setToolButtonStyle);
    connect(button, &QToolButton::triggered, toolBar, &QToolBar::actionTriggered);
    connect( button->menu(), &QMenu::triggered, this, &ToolAction::slotNewDefaultAction );

    m_buttons.append( button );

    if ( !m_actions.isEmpty() )
    {
        button->setDefaultAction( m_actions.first() );
        foreach ( QAction *action, m_actions )
        {
            button->menu()->addAction( action );
            if ( action->isChecked() )
                button->setDefaultAction( action );
        }