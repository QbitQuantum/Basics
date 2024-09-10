void QTableManager::EUpdate(QgraphicsItemTable *table, qreal Vx, qreal Vy)
    {
        QRectF *up = new QRectF(table->GetUpRect());
        QRectF *down = new QRectF(table->GetDownRect());
        QRectF *right = new QRectF(table->GetRightRect());
        QRectF *left = new QRectF(table->GetLeftRect());


        //QPointF  sbottom = sec->bottomRight()
        for ( int i = 0 ; i<ProjectData->NodeCount();i++){

            QLineF line = ProjectData->getNode(i)->link->line();

            QPointF *point  = new QPointF(line.x1(),line.y1());
            QPointF *point2 = new QPointF(line.x2(),line.y2());
           qreal xbottom = 0 ;
           qreal ybottom  = 0 ;

            if (ProjectData->getNode(i)->start==table){

                            xbottom = point->x();
                            ybottom = point->y();

                          //  ProjectData->getNode(i)->link->setLine(xbottom,ybottom,point2->x(),point2->y());
                        }
            if (ProjectData->getNode(i)->end==table){
                            xbottom = point2->x();
                            ybottom = point2->y();
                            //xbottom = (bottom.x()*xbottom)/(bottom.x()+Vx);
                          //  ybottom = (bottom.y()*ybottom)/(bottom.y()+Vy);
                           // ProjectData->getNode(i)->link->setLine(point->x(),point->y(),point2->x()+Vx,point2->y()+Vy);
                            }
            if ((xbottom!=0 || ybottom !=0)){
                if (right->contains(*point)||right->contains(*point2) ){
                    xbottom+=Vx;
                    // y media.
                }
                if (up->contains(*point)|| up->contains(*point2)){
                    // media x

                }
                if (down->contains(*point)|| down->contains(*point2)){
                    // media x
                    ybottom +=Vy;
                }
               if (left->contains(*point)||left->contains(*point2) ){
                   // media y.
            }
               if (ProjectData->getNode(i)->end==table)
            ProjectData->getNode(i)->link->setLine(point->x(),point->y(),point2->x()+Vx/2,point2->y()+Vy/2);
            else
            ProjectData->getNode(i)->link->setLine(xbottom,ybottom,point2->x(),point2->y());
            }
}
}