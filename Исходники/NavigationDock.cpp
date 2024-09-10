void NavigationDock::setActiveNode(NodeId id) {
    for(int i = 0; i < _model->rowCount(); ++i) {
        QVariant data = _model->data(_model->index(i));
        if(data.canConvert<const Node*>()) {
            const Node* node = data.value<const Node*>();
            if(node && node->getId() == id) {
                QItemSelectionModel* selectModel = _view->selectionModel();
                selectModel->select(_model->index(i), QItemSelectionModel::ClearAndSelect);
            }
        }
    }
}