void ShrinkToFitShapeContainer::unwrapShape(KoShape *shape)
{
    Q_ASSERT(shape->parent() == this);

    removeShape(shape);
    shape->setParent(parent());

    QSet<KoShape*> delegates = toolDelegates();
    delegates.remove(shape);
    setToolDelegates(delegates);

    shape->setPosition(position());
    shape->setSize(size());
    shape->rotate(rotation());
    shape->setSelectable(true);
}