    InstancePort::InstancePort(QString name, Port * p, Rect * parent):Port(name)
    {
        childport_ = p;
        Rect *r = p->get();
        if(r){
            Layer * l = rules->getLayer(r->layer());
            routeLayer_ = l;
            this->setRect(r->layer(), r->x1(), r->y1(),r->width(),r->height());

        }
    }