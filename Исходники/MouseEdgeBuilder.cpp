bool MouseEdgeBuilder::eventFilter(QObject *widget, QEvent *e) {

    GlMainWidget *glMainWidget = static_cast<GlMainWidget *>(widget);

    if (e->type() == QEvent::MouseButtonPress) {
        QMouseEvent * qMouseEv = static_cast<QMouseEvent *>(e);

        SelectedEntity selectedEntity;
        GlGraphInputData *inputData=glMainWidget->getScene()->getGlGraphComposite()->getInputData();
        Graph * _graph = inputData->getGraph();

        LayoutProperty* mLayout = inputData->getElementLayout();

        if (qMouseEv->buttons()==Qt::LeftButton) {
            if (!_started) {
                bool result=glMainWidget->pickNodesEdges(qMouseEv->x(), qMouseEv->y(), selectedEntity);

                if (result && (selectedEntity.getEntityType() == SelectedEntity::NODE_SELECTED)) {
                    _started=true;
                    initObserver(_graph);
                    _source=node(selectedEntity.getComplexEntityId());
                    _curPos=_startPos=mLayout->getNodeValue(_source);
                    return true;
                }

                return false;
            }
            else {
                bool result = glMainWidget->pickNodesEdges(qMouseEv->x(),qMouseEv->y(),selectedEntity);

                if (result && (selectedEntity.getEntityType() == SelectedEntity::NODE_SELECTED)) {
                    Observable::holdObservers();
                    _started=false;
                    clearObserver();
                    // allow to undo
                    _graph->push();
                    addLink(widget,_source,node(selectedEntity.getComplexEntityId()));
                    Observable::unholdObservers();

                }
                else {
                    Coord point(glMainWidget->width() - qMouseEv->x(), qMouseEv->y(), 0);
                    _bends.push_back(glMainWidget->getScene()->getGraphCamera().viewportTo3DWorld(glMainWidget->screenToViewport(point)));
                    glMainWidget->redraw();
                }
            }

            return true;
        }

        if (qMouseEv->buttons()==Qt::MidButton) {
            _bends.clear();
            _started=false;
            _source=node();
            clearObserver();
            glMainWidget->draw();
            return true;
        }
    }

    if  (e->type() == QEvent::MouseMove) {
        QMouseEvent * qMouseEv = static_cast<QMouseEvent *>(e);

        if (!_started) {
            SelectedEntity selectedEntity;
            bool hoveringOverNode = glMainWidget->pickNodesEdges(qMouseEv->x(), qMouseEv->y(), selectedEntity) && selectedEntity.getEntityType() == SelectedEntity::NODE_SELECTED;

            if (!hoveringOverNode) {
                glMainWidget->setCursor(QCursor(Qt::ArrowCursor));
                return false;
            }
            else {
                glMainWidget->setCursor(QCursor(Qt::CrossCursor));
            }
        }
        else {
            SelectedEntity selectedEntity;

            if(glMainWidget->pickNodesEdges(qMouseEv->x(), qMouseEv->y(), selectedEntity) && selectedEntity.getEntityType() == SelectedEntity::NODE_SELECTED) {
                glMainWidget->setCursor(QCursor(Qt::CrossCursor));
            }
            else {
                glMainWidget->setCursor(QCursor(Qt::ArrowCursor));
            }

            Coord point(glMainWidget->width() - qMouseEv->x(), qMouseEv->y(), 0);
            point = glMainWidget->getScene()->getGraphCamera().viewportTo3DWorld(glMainWidget->screenToViewport(point));
            _curPos.set(point[0], point[1], point[2]);
            glMainWidget->redraw();
        }

        return true;
    }

    return false;
}