void CameraApplication::MoveCamera(Entity* cameraEntity, float frameTime)
{
    if (!cameraEntity)
        return;

    Placeable* placeable = cameraEntity->Component<Placeable>();
    if (!placeable)
        return;
    
    InputAPI* input = framework->Input();

    bool changed = false;

    Transform t = placeable->transform.Get();

    float3 rotDelta = float3::zero;

    if (inputContext_->IsMouseButtonDown(Urho3D::MOUSEB_RIGHT))
    {
        rotDelta.x -= input->GetMouseMoveY() * cRotateSpeed;
        rotDelta.y -= input->GetMouseMoveX() * cRotateSpeed;
    }
    else if (inputContext_->GetNumTouches() > 0)
    {
        // Find a touch point that is not on top of the movement joystick button.
        for (int ti=0, len=input->GetNumTouches(); ti<len; ++ti)
        {
            Urho3D::TouchState *touch = input->GetTouch(ti);
            if (!touch->touchedElement_.Get())
            {
                rotDelta -= (float3(static_cast<float>(touch->delta_.y_), static_cast<float>(touch->delta_.x_), 0.f) * cRotateSpeed);
                break;
            }
        }
    }

    if (!rotDelta.Equals(float3::zero))
    {
        RotateChanged.Emit(rotDelta);

        t.rot.x += rotDelta.x;
        t.rot.y += rotDelta.y;
        t.rot.x = Clamp(t.rot.x, -90.0f, 90.0f);
        changed = true;
    }

    float3 moveVector = float3::zero;
    // Note right-handed coordinate system
    if (inputContext_->IsKeyDown(Urho3D::KEY_W))
        moveVector += float3(0.0f, 0.0f, -1.0f);
    if (inputContext_->IsKeyDown(Urho3D::KEY_S))
        moveVector += float3(0.0f, 0.0f, 1.0f);
    if (inputContext_->IsKeyDown(Urho3D::KEY_A))
        moveVector += float3(-1.0f, 0.0f, 0.0f);
    if (inputContext_->IsKeyDown(Urho3D::KEY_D))
        moveVector += float3(1.0f, 0.0f, 0.0f);
    if (inputContext_->IsKeyDown(Urho3D::KEY_SPACE))
        moveVector += float3(0.0f, 1.0f, 0.0f);
    if (inputContext_->IsKeyDown(Urho3D::KEY_C))
        moveVector += float3(0.0f, -1.0f, 0.0f);

    if (!moveVector.Equals(lastMoveVector_))
    {
        lastMoveVector_ = moveVector;
        MoveChanged.Emit(moveVector);
    }

    if (inputContext_->IsKeyPressed(Urho3D::KEY_SHIFT))
        moveVector *= 2;

    if (!moveVector.Equals(float3::zero))
    {
        movementHeld_ = Clamp(movementHeld_ + (frameTime * 4.f), 0.f, 1.0f);
        t.pos += t.Orientation() * (cMoveSpeed * frameTime * moveVector * movementHeld_);
        changed = true;
    }
    else
        movementHeld_ = 0.f;

    // If some other camera (like avatar) is active, do not actually move, only transmit the move signals
    if (changed && cameraEntity == lastCamera_)
        placeable->transform.Set(t);
}