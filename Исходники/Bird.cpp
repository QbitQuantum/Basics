void Bird::Land(float timeStep)
{
    Vector3 targetDelta = target_ - GetPosition();
    if (targetDelta.Length() < 0.5f){
        if (!touchDown_){
            touchDown_ = true;
            animCtrl_->StopAll(0.1f);
            animCtrl_->Play("Resources/Models/Land.ani", 0, false, 0.1f);
        }
        Quaternion rotation = rootNode_->GetWorldRotation();
        Vector3 eulerRotation = rotation.EulerAngles();
        Quaternion aimRotation = Quaternion(0.0f, eulerRotation.y_, 0.0f);
        if (first_) aimRotation = Quaternion(0.0f, rootNode_->GetDirection().x_ > 0.0f? 90.0f : -90.0f, 0.0f);
        rootNode_->SetRotation(rotation.Slerp(aimRotation, 5.0f*timeStep));

        if (targetDelta.Length() < 0.2f || targetDelta.y_ > 0.0f) {
            SetState(BirdState::Standing);
        }
    }
    velocity_ += 23.0f * timeStep * targetDelta.Normalized() * Clamp( targetDelta.Length()*0.5f, 2.0f, 4.0f ) - Finchy::Scale(velocity_, Vector3(0.023f, 0.23f, 0.023f));
    velocity_ *= Clamp( 0.2f + targetDelta.Length() * 0.666f, 0.2f, 0.95f );
    velocity_.x_ = Clamp(velocity_.x_, -targetDelta.Length(), targetDelta.Length());
    velocity_.y_ = Clamp(velocity_.y_, -targetDelta.Length(), targetDelta.Length());
}