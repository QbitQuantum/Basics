KUndo2Command* KoCreateShapeStrategy::createCommand()
{
    Q_D(KoShapeRubberSelectStrategy);
    KoCreateShapesTool *parent = static_cast<KoCreateShapesTool*>(d_ptr->tool);
    KoShapeFactoryBase *factory = KoShapeRegistry::instance()->value(parent->shapeId());
    if (! factory) {
        warnFlake << "Application requested a shape that is not registered" << parent->shapeId();
        return 0;
    }

    const KoProperties *props = parent->shapeProperties();
    KoShape *shape;
    if (props)
        shape = factory->createShape(props, parent->canvas()->shapeController()->resourceManager());
    else
        shape = factory->createDefaultShape(parent->canvas()->shapeController()->resourceManager());
    if (shape->shapeId().isEmpty())
        shape->setShapeId(factory->id());
    QRectF rect = d->selectedRect();
    shape->setPosition(rect.topLeft());
    QSizeF newSize = rect.size();
    // if the user has dragged when creating the shape,
    // resize the shape to the dragged size
    if (newSize.width() > 1.0 && newSize.height() > 1.0)
        shape->setSize(newSize);

    KUndo2Command * cmd = parent->canvas()->shapeController()->addShape(shape);
    if (cmd) {
        KoSelection *selection = parent->canvas()->shapeManager()->selection();
        selection->deselectAll();
        selection->select(shape);
    }
    return cmd;
}