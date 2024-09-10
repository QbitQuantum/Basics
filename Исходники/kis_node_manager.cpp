bool KisNodeManager::Private::activateNodeImpl(KisNodeSP node)
{
    Q_ASSERT(view);
    Q_ASSERT(view->canvasBase());
    Q_ASSERT(view->canvasBase()->globalShapeManager());
    Q_ASSERT(imageView);
    if (node && node == q->activeNode()) {
        return false;
    }

    // Set the selection on the shape manager to the active layer
    // and set call KoSelection::setActiveLayer( KoShapeLayer* layer )
    // with the parent of the active layer.
    KoSelection *selection = view->canvasBase()->globalShapeManager()->selection();
    Q_ASSERT(selection);
    selection->deselectAll();

    if (!node) {
        selection->setActiveLayer(0);
        imageView->setCurrentNode(0);
        maskManager.activateMask(0);
        layerManager.activateLayer(0);
    } else {

        KoShape * shape = view->document()->shapeForNode(node);
        Q_ASSERT(shape);

        selection->select(shape);
        KoShapeLayer * shapeLayer = dynamic_cast<KoShapeLayer*>(shape);

        Q_ASSERT(shapeLayer);
//         shapeLayer->setGeometryProtected(node->userLocked());
//         shapeLayer->setVisible(node->visible());
        selection->setActiveLayer(shapeLayer);

        imageView->setCurrentNode(node);
        if (KisLayerSP layer = dynamic_cast<KisLayer*>(node.data())) {
            maskManager.activateMask(0);
            layerManager.activateLayer(layer);
        } else if (KisMaskSP mask = dynamic_cast<KisMask*>(node.data())) {
            maskManager.activateMask(mask);
            // XXX_NODE: for now, masks cannot be nested.
            layerManager.activateLayer(static_cast<KisLayer*>(node->parent().data()));
        }

    }
    return true;
}