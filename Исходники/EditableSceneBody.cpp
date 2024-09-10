void EditableSceneBodyImpl::dragForcedPosition(const SceneWidgetEvent& event)
{
    if(dragProjector.dragTranslation(event)){
        Position T;
        T.translation() = dragProjector.position().translation();
        T.linear() = targetLink->R();
        setForcedPosition(T);
    }
}