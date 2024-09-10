void GraphicsView::paintGL()
{
    if(!d->scene){
        return;
    }

    d->shader->bind();

    // clear
    qglClearColor(d->backgroundColor);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // setup camera (if necessary)
    if(camera()->changed()){
        glMatrixMode(GL_MODELVIEW);

        Vector3f f = camera()->direction();
        Vector3f s = f.cross(camera()->upVector());
        Vector3f u = s.cross(f);

        Eigen::Matrix<float, 4, 4> transform;
        transform <<  s.x(),  s.y(),  s.z(), 0.0f,
                      u.x(),  u.y(),  u.z(), 0.0f,
                     -f.x(), -f.y(), -f.z(), 0.0f,
                       0.0f,   0.0f,   0.0f, 1.0f;
        d->modelViewTransform = GraphicsTransform(transform);

        d->modelViewTransform *= GraphicsTransform::translation(-camera()->position());
        glLoadMatrixf(d->modelViewTransform.data());

        camera()->setChanged(false);
    }

    // draw items
    GraphicsPainter painter;

    QList<GraphicsItem *> nonOpaqueItems;

    foreach(GraphicsItem *item, scene()->items()){
        if(!item->isVisible())
            continue;

        if(!item->isOpaque()){
            nonOpaqueItems.append(item);
        }
        else{
            glPushMatrix();

            GraphicsTransform transform = item->transform();
            glMultMatrixf(transform.data());

            painter.setMaterial(item->material());
            item->paint(&painter);

            glPopMatrix();
        }
    }

    if(!nonOpaqueItems.isEmpty()){
        glEnable(GL_BLEND);

        foreach(GraphicsItem *item, nonOpaqueItems){
            glPushMatrix();

            GraphicsTransform transform = item->transform();
            glMultMatrixf(transform.data());

            painter.setMaterial(item->material());
            item->paint(&painter);

            glPopMatrix();
        }