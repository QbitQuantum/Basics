void SmoothedTransform::Update(float constant, float squaredSnapThreshold)
{
    if (smoothingMask_ && node_)
    {
        Vector3 position = node_->GetPosition();
        Quaternion rotation = node_->GetRotation();

        if (smoothingMask_ & SMOOTH_POSITION)
        {
            // If position snaps, snap everything to the end
            float delta = (position - targetPosition_).LengthSquared();
            if (delta > squaredSnapThreshold)
                constant = 1.0f;

            if (delta < M_EPSILON || constant >= 1.0f)
            {
                position = targetPosition_;
                smoothingMask_ &= ~SMOOTH_POSITION;
            }
            else
                position = position.Lerp(targetPosition_, constant);

            node_->SetPosition(position);
        }

        if (smoothingMask_ & SMOOTH_ROTATION)
        {
            float delta = (rotation - targetRotation_).LengthSquared();
            if (delta < M_EPSILON || constant >= 1.0f)
            {
                rotation = targetRotation_;
                smoothingMask_ &= ~SMOOTH_ROTATION;
            }
            else
                rotation = rotation.Slerp(targetRotation_, constant);

            node_->SetRotation(rotation);
        }
    }

    // If smoothing has completed, unsubscribe from the update event
    if (!smoothingMask_)
    {
        UnsubscribeFromEvent(GetScene(), E_UPDATESMOOTHING);
        subscribed_ = false;
    }
}