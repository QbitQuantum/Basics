void SpatialNode::RotateAround(const Vector3& point, const Quaternion& delta, TransformSpace space)
{
    SpatialNode* parentNode = SpatialParent();
    Vector3 parentSpacePoint;
    Quaternion oldRotation = rotation;

    switch (space)
    {
    case TS_LOCAL:
        parentSpacePoint = Transform() * point;
        rotation = (rotation * delta).Normalized();
        break;

    case TS_PARENT:
        parentSpacePoint = point;
        rotation = (delta * rotation).Normalized();
        break;

    case TS_WORLD:
        if (!parentNode)
        {
            parentSpacePoint = point;
            rotation = (delta * rotation).Normalized();
        }
        else
        {
            parentSpacePoint = parentNode->WorldTransform().Inverse() * point;
            Quaternion worldRotation = WorldRotation();
            rotation = rotation * worldRotation.Inverse() * delta * worldRotation;
        }
        break;
    }

    Vector3 oldRelativePos = oldRotation.Inverse() * (position - parentSpacePoint);
    position = rotation * oldRelativePos + parentSpacePoint;

    OnTransformChanged();
}