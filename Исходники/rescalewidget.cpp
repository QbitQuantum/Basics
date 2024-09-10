void RescaleWidget::
        updateModel()
{
    bool success1, success2;

    Heightmap::Position last = view_->getPlanePos( mapToParent(dragSource_), &success1);
    Heightmap::Position current = view_->getPlanePos( mapToParent(lastPos_), &success2);

    QPointF d = lastPos_ - dragSource_;
    float dx = d.x() / width();
    float dy = -d.y() / height();
    dx = max(-.1f, min(.1f, dx));
    dy = max(-.1f, min(.1f, dy));
    scalex_ *= exp2f(dx);
    scaley_ *= exp2f(dy);
    scalex_ = max(0.5f, min(1.8f, scalex_));
    scaley_ = max(0.5f, min(1.8f, scaley_));

    if (success1 && success2)
    {
        float r = DIRECT_RESCALING ? 4 : .1;
        float dt = r*(current.time - last.time)*view_->model->xscale/view_->model->_pz;
        float ds = r*(current.scale - last.scale)*view_->model->zscale/view_->model->_pz;

        Tools::Commands::pCommand cmd( new Tools::Commands::ZoomCameraCommand(view_->model, dt, ds, 0.f ));
        view_->model->project()->commandInvoker()->invokeCommand( cmd );
    }

    //dragSource_ = event->pos();
    recreatePolygon();
}