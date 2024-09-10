PacMan::PacMan(int width, int height, QColor color, int layer , double startX, double startY, double endX, double endY, int startSec, int endSec)
 : width(width) , height(height) , color(color) , layer(layer) , startX(startX) , startY(startY) , endX(endX) , endY(endY) , startSec(startSec) , endSec(endSec)
{
    moveScale= 1;

    QGraphicsRectItem * rect = new QGraphicsRectItem(this);

    rect->setRect ( -width/2 , -height/2 , width , height );
    rect->setBrush (QBrush(color));
    liveSec = endSec - startSec;

    setZValue(layer);
}