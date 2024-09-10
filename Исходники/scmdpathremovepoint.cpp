void SCmdPathRemovePoint::redo()
{
    QVector<SEditPoint*>* editPoints = _manager->getEditPoints();
    SEditPoint* editPoint = editPoints->at(_numPoint);
    _scene->removeItem(editPoint);
    delete editPoint;
    editPoints->remove(_numPoint);

    _graphicsItem->path()->removePoint(_numPoint);
    _graphicsItem->recomputeGeometry();
}