void GalaGV::showOwn(bool show)
{
    mData->showOwn = show;

    if(!mData->own.contains(mData->gala)){
        QList<ODPlanet> l =mDB->loadOwnPlanis(mData->gala);
        QHash<QString,QGraphicsEllipseItem*> hash;
        for (int var = 0; var < l.size(); ++var) {
            const ODPlanet & p = l.at(var);
            QGraphicsEllipseItem *item = makeMarkerItem(p.cords,p.sys,Own,Qt::green,Mark);
            item->setFlags(QGraphicsItem::ItemIsSelectable);
            item->setToolTip(p.sysname + "("+ p.name+")");
            hash.insert(p.index,item);
            scene()->addItem(item);
        }
        mData->own.insert(mData->gala,hash);
    }
    if(show){
        showItems(mData->own.value(mData->gala));
    }else {
        hideItems(mData->own.value(mData->gala));
    }
}