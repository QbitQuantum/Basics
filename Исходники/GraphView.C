void GraphView::paintEvent(QPaintEvent*){
    QPixmap backbuffer;
    backbuffer.convertFromImage (image);
    QPainter paint(&backbuffer);
    if(disc){
        for(int i = 0; i < disc->numEdge; i++){
            int x1,y1,x2,y2;
            getPoint(x1, y1, disc->verts[disc->edges[i].vert1]);
            getPoint(x2, y2, disc->verts[disc->edges[i].vert2]);
            drawEdge(paint,x1,y1,x2,y2);
        }
        for(int i = 0; i < disc->numVert; i++){
            int x,y;
            getPoint(x, y, disc->verts[i]);
            drawCrossHair(paint,x,y);
        }
    }
    paint.end();
    bitBlt(this,0,0,&backbuffer,0,0,width(),height(),CopyROP,FALSE);
}