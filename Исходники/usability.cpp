/// @brief constructor
///
/// @param parent parent widget
ScrollScene::ScrollScene (QWidget * parent, ResultsTab *resultsTab)
    : QGraphicsScene (parent)
    , resultsTab (resultsTab)
    , testing (false)
    , text1 (new QGraphicsTextItem ("Scroll until the red circle is centered.  Press SPACE to begin."))
    , text2 (new QGraphicsTextItem ("Scroll until the red circle is centered.  Press SPACE to begin."))
{
    // set the text font
    text1->setFont (QFont ("Arial", 18, QFont::Bold));
    text2->setFont (QFont ("Arial", 18, QFont::Bold));
    QRectF r = text1->boundingRect ();
    const size_t NCIRCLES = 100;
    text1->setPos (-r.width () / 2, -4 * RADIUS);
    text2->setPos (-r.width () / 2, NCIRCLES * RADIUS * 2);
    // add it
    addItem (text1);
    addItem (text2);
    // set background of client area
    setBackgroundBrush (Qt::white);
    circles.resize (NCIRCLES);
    for (size_t i = 0; i < circles.size (); ++i)
    {
        QGraphicsEllipseItem *c = new QGraphicsEllipseItem (0);
        c->setRect (-RADIUS, -RADIUS, RADIUS, RADIUS);
        int y = i * RADIUS * 2;
        c->setPos (0, y);
        addItem (c);
        circles[i] = c;
    }
}