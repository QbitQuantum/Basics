/*!
  \class RWidgetResizer
  Create a new RReportWidget resize manager. A resize manager show 8 circle on
  widget that user can drag them to resize the widget
*/
QReportWidgetResizer::QReportWidgetResizer(QGraphicsScene *parent) :
    QObject(),
    parentScene(parent),
    //_parent( 0 ),
    m_scale(1)
{
    resizerTL = new QReportResizeHandle(0, 0, CIRCLER);
    resizerT  = new QReportResizeHandle(0, 0, CIRCLER);
    resizerTR = new QReportResizeHandle(0, 0, CIRCLER);
    resizerL  = new QReportResizeHandle(0, 0, CIRCLER);
    resizerR  = new QReportResizeHandle(0, 0, CIRCLER);
    resizerBL = new QReportResizeHandle(0, 0, CIRCLER);
    resizerB  = new QReportResizeHandle(0, 0, CIRCLER);
    resizerBR = new QReportResizeHandle(0, 0, CIRCLER);

    /*parent->addItem( resizerTL );
    parent->addItem( resizerT  );
    parent->addItem( resizerTR );
    parent->addItem( resizerL  );
    parent->addItem( resizerR  );
    parent->addItem( resizerBL );
    parent->addItem( resizerB  );
    parent->addItem( resizerBR );*/

    handles.append(resizerTL);
    handles.append(resizerT);
    handles.append(resizerTR);
    handles.append(resizerL);
    handles.append(resizerR);
    handles.append(resizerBL);
    handles.append(resizerB);
    handles.append(resizerBR);

    resizerTL->setPen(QPen(Qt::black));

    setVisible(false);

    resizerTL->setCursor(Qt::SizeFDiagCursor);
    resizerT->setCursor(Qt::SizeVerCursor);
    resizerTR->setCursor(Qt::SizeBDiagCursor);
    resizerL->setCursor(Qt::SizeHorCursor);
    resizerR->setCursor(Qt::SizeHorCursor);
    resizerBL->setCursor(Qt::SizeBDiagCursor);
    resizerB->setCursor(Qt::SizeVerCursor);
    resizerBR->setCursor(Qt::SizeFDiagCursor);

    resizerT->setResizeDirection(::Top);
    resizerL->setResizeDirection(::Left);
    resizerR->setResizeDirection(::Right);
    resizerB->setResizeDirection(::Bottom);

    resizerTR->setResizeDirection(::Top    | ::Right);
    resizerTL->setResizeDirection(::Top    | ::Left);
    resizerBR->setResizeDirection(::Bottom | ::Right);
    resizerBL->setResizeDirection(::Bottom | ::Left);

    for (int i = 0; i < handles.count(); i++) {
        /*QRadialGradient gradient( CIRCLER, CIRCLER, 270);
        gradient.setColorAt(0, QColor::fromRgb(128, 128, 255) );
        gradient.setColorAt(1, QColor::fromRgb(255, 255, 255) );
        handles.at( i )->setBrush( QBrush(gradient) );*/

        handles.at(i)->setBrush(QBrush(Qt::white));
        parent->addItem(handles.at(i));

        connect(handles.at(i), SIGNAL(moving(QPointF)),
                this,          SLOT(handleMoving(QPointF)));

        connect(handles.at(i), SIGNAL(moved()),
                this,          SIGNAL(resized()));

    }//for
}