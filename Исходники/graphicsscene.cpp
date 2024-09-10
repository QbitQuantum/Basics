void GraphicsScene::updateConnections(){
    int i = 0;
    while(i<items().size()){
        QGraphicsItem *activeItem = items().at(i);
        if(((CustomItem*)activeItem)->getName() == std::string("Connection")){
            removeItem(activeItem);
        }
        else{
            i++;
        }
    }
    i = 0;
    while(i<items().size()){
        QGraphicsItem *activeItem = items().at(i);
        if(((CustomItem*)activeItem)->getName() == std::string("Dot")){
            Dot *dot = ((Dot*)activeItem);
            if(!dot->isCenter()){
                connectToNearest(dot);
            }
        }
        i++;
    }
    update(QRectF(-50,-50,1000,1000));
}