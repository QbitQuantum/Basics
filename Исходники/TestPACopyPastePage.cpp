void TestPACopyPastePage::addShape( KoPAPageBase * page )
{
    KoPathShape * path = new KoPathShape();
    path->lineTo( QPointF( 10, 0 ) );
    path->lineTo( QPointF( 10, 10 ) );
    path->setPosition( m_pos );
    m_pos += QPointF( 1.0, 1.0 );

    QList<KoShape*> shapes = page->shapes();
    if ( !shapes.isEmpty() ) {
        KoShapeLayer* layer = dynamic_cast<KoShapeLayer*>( shapes.last() );
        layer->addShape( path );
    }
}