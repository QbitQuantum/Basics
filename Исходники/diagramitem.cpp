//! [0]
DiagramItem::DiagramItem(DiagramType diagramType, QMenu *contextMenu,
             QGraphicsItem *parent)
    : QGraphicsPolygonItem(parent)
{
    myDiagramType = diagramType;
    myContextMenu = contextMenu;

    QPainterPath path;
    switch (myDiagramType) {
        case StartEnd:
            path.moveTo(200, 50);
            path.arcTo(150, 0, 50, 50, 0, 90);
            path.arcTo(50, 0, 50, 50, 90, 90);
            path.arcTo(50, 50, 50, 50, 180, 90);
            path.arcTo(150, 50, 50, 50, 270, 90);
            path.lineTo(200, 25);
            myPolygon = path.toFillPolygon();
            break;
        case Conditional:
            myPolygon << QPointF(-100, 0) << QPointF(0, 100)
                      << QPointF(100, 0) << QPointF(0, -100)
                      << QPointF(-100, 0);
            break;
        case Step:
            myPolygon << QPointF(-100, -100) << QPointF(100, -100)
                      << QPointF(100, 100) << QPointF(-100, 100)
                      << QPointF(-100, -100);
            break;
        case Oval:
            path.moveTo(-50,50);
            path.arcTo(0, -50, 100, 100, 270,180);
            path.lineTo(-50,-50);
            path.arcTo(-100, -50, 100, 100, 90, 180);
            myPolygon = path.toFillPolygon();
            break;
        case Hexagon:
            myPolygon << QPointF(-100, 0) << QPointF(-50, 100)
                      << QPointF(50, 100) << QPointF(100, 0)
                      << QPointF(50, -100) << QPointF(-50,-100) << QPointF(-100,0);
            break;
        case Pentagon:
            myPolygon << QPointF(100, 50) << QPointF(100, -100)
                      << QPointF(-100, -100) << QPointF(-100, 50)
                      << QPointF(0,100) << QPointF(100,50);
            break;
        default:
            myPolygon << QPointF(-120, -80) << QPointF(-70, 80)
                      << QPointF(120, 80) << QPointF(70, -80)
                      << QPointF(-120, -80);
            break;
    }
    setPolygon(myPolygon);
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
}