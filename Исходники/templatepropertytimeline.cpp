void TemplatePropertyTimeline<Camera>::setCurrentSettingAsKeyvalue(float time, bool forceKeyValue) {

    time = floor(time*10000)/10000;

    tgt::Camera cam = property_->get();
/*    Camera* value = new CameraNode(cam->getPosition(), cam->getFocus(), cam->getUpVector(), cam->getStrafe());
    CameraNode* animatedValue = getPropertyAt(time); */
    Camera value = cam;
    Camera animatedValue = getPropertyAt(time);

    if ((value.getPosition() != animatedValue.getPosition())
        ||(value.getFocus() != animatedValue.getFocus())
        ||(value.getUpVector() != animatedValue.getUpVector()))
    {
        const PropertyKeyValue<Camera>* kv = timeline_->newKeyValue(time);
        if (!kv) {
            kv = new PropertyKeyValue<Camera>(value,time);
        }
        this->changeValueOfKeyValue(value,kv);
    }
    else {
        if (forceKeyValue){
            newKeyValue(time);
        }
    }
}