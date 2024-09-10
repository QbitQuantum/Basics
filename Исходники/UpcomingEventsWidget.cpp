UpcomingEventsListWidget::UpcomingEventsListWidget( QGraphicsWidget *parent )
    : Plasma::ScrollWidget( parent )
    , m_sigmap( new QSignalMapper( this ) )
{
    // The widgets are displayed line by line with only one column
    m_layout = new QGraphicsLinearLayout( Qt::Vertical );
    QGraphicsWidget *content = new QGraphicsWidget( this );
    content->setLayout( m_layout );
    setWidget( content );
    connect( m_sigmap, SIGNAL(mapped(QObject*)), this, SIGNAL(mapRequested(QObject*)) );
}