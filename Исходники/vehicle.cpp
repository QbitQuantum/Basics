void Vehicle::FixedUpdate(float timeStep)
{
    float newSteering = 0.0f;
    float accelerator = 0.0f;

    // Read controls
    if (controls_.buttons_ & CTRL_LEFT)
        newSteering = -1.0f;
    if (controls_.buttons_ & CTRL_RIGHT)
        newSteering = 1.0f;
    if (controls_.buttons_ & CTRL_FORWARD)
        accelerator = 1.0f;
    if (controls_.buttons_ & CTRL_BACK)
        accelerator = -0.5f;

    // When steering, wake up the wheel rigidbodies so that their orientation is updated
    if (newSteering != 0.0f)
    {
        frontLeftBody_->Activate();
        frontRightBody_->Activate();
        steering_ = steering_ * 0.95f + newSteering * 0.05f;
    }
    else
        steering_ = steering_ * 0.8f + newSteering * 0.2f;

    // Set front wheel angles
    Quaternion steeringRot(0, steering_ * MAX_WHEEL_ANGLE, 0);
    frontLeftAxis_->SetOtherAxis(steeringRot * Vector3::LEFT);
    frontRightAxis_->SetOtherAxis(steeringRot * Vector3::RIGHT);

    Quaternion hullRot = hullBody_->GetRotation();
    if (accelerator != 0.0f)
    {
        // Torques are applied in world space, so need to take the vehicle & wheel rotation into account
        Vector3 torqueVec = Vector3(ENGINE_POWER * accelerator, 0.0f, 0.0f);

        frontLeftBody_->ApplyTorque(hullRot * steeringRot * torqueVec);
        frontRightBody_->ApplyTorque(hullRot * steeringRot * torqueVec);
        rearLeftBody_->ApplyTorque(hullRot * torqueVec);
        rearRightBody_->ApplyTorque(hullRot * torqueVec);
    }

    // Apply downforce proportional to velocity
    Vector3 localVelocity = hullRot.Inverse() * hullBody_->GetLinearVelocity();
    hullBody_->ApplyForce(hullRot * Vector3::DOWN * Abs(localVelocity.z_) * DOWN_FORCE);
}