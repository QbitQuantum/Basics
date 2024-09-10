void Arrow::Tick(float deltaTime)
{
    Super::Tick(deltaTime);
    UpdateWorldPos();
    
    Vector3 shippos = mPlayer->GetPosition();
    Vector3 checkpos = mCheckpointPos;
    Vector3 direction = checkpos - shippos;
    direction.Normalize();
    if( direction.x == 1 && direction.y == 0 && direction.z == 0)
    {
        SetRotation(Quaternion::Identity);
    }
    else
    {
        Vector3 axis = Cross(Vector3::UnitX,direction);
        float angle = Math::Acos(Dot(Vector3::UnitX,direction));
        axis.Normalize();
        Quaternion rotation(axis, angle);
        SetRotation(rotation);
        
    }
}