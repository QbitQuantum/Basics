void MoeGraphicsContainer::renderChildren(RenderRecorder * p, QRect region){
    updateChildCache();
    foreach(MoeGraphicsObject* graphicsObject, visibleChildren) {
        if(!region.intersects(graphicsObject->realGeometry()))
            continue;

        p->pushOpacity(graphicsObject->opacity());
        p->pushClipRect(graphicsObject->realGeometry());
        p->pushTransform(graphicsObject->localTransform);
        graphicsObject->render(p, graphicsObject->mapFromParent(graphicsObject->realGeometry() & region));
        p->popTransform();
        p->popClipRect();
        p->popOpacity();
    }
}