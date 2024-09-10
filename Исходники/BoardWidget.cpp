BoardWidget::BoardWidget(Board& b, QWidget *parent)
    : PieceWidget(10,9,parent), board(b)
{
    pList =0;
    gettingMove = false;
    editMode = false;
    renderMode = false;

    /* setup cursors */

#define createCursor(bitmap,name) \
    static QBitmap bitmap = QBitmap::fromData(QSize(bitmap##_width, bitmap##_height), \
    (unsigned char *) bitmap##_bits);        \
    static QBitmap bitmap##Mask = QBitmap::fromData(QSize(bitmap##Mask_width, bitmap##Mask_height), \
    (unsigned char *) bitmap##Mask_bits);    \
    name = new QCursor(bitmap, bitmap##Mask, bitmap##_x_hot, bitmap##_y_hot);

    createCursor(Arrow1, arrow[1]);
    createCursor(Arrow2, arrow[2]);
    createCursor(Arrow3, arrow[3]);
    createCursor(Arrow4, arrow[4]);
    createCursor(Arrow5, arrow[5]);
    createCursor(Arrow6, arrow[6]);

    setCursor(Qt::CrossCursor);

    //  boardColor   = new QColor("lightblue");
    boardColor   = new QColor(palette().color(backgroundRole()));
    redColor     = new QColor("red");
    yellowColor  = new QColor("yellow");
    redHColor    = new QColor("orange");
    yellowHColor = new QColor("green");

    initPieces();
    updatePosition();
}