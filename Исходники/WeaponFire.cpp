void WeaponFire::Update(float deltaTime, Terrain* terrain)
{
    GameObject::Update(deltaTime, terrain);

    gTimer += deltaTime;

    if (gTimer >= gTimerStop)
    {
        SetState( Dead );
        return;
    }

    if (gOwner)
    {
        XMFLOAT3 pipePos;
        if (gOwner->GetJointPosition("Pipe", pipePos));
        {
            MoveTo(pipePos);
        }

        XMFLOAT4 quat = gOwner->GetQuaternation();

        if (IsOfType<Weapon>(gOwner))
        {
            XMFLOAT4 offsetQuat = ((Weapon*)gOwner)->GetWeaponOffsetRotation();

            XMVECTOR quatV			= XMLoadFloat4(&quat);
            XMVECTOR offsetQuatV	= XMLoadFloat4(&offsetQuat);

            quatV = XMQuaternionMultiply(quatV, offsetQuatV);

            XMStoreFloat4(&quat, quatV);

        }

        SetRotation(quat);
    }

    float progress = gTimer / gTimerStop;
    float diff = gMaxScale - gMinScale;
    float scale = gMinScale + progress * diff;

    SetScale(scale);
}