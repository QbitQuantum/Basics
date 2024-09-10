void DirectionSelector::VerifyDirection()
{
    if (_direction.x * _direction.x + _direction.y * _direction.y >= 1.0f ||
        (_direction.x == 0.0f && _direction.y == 0.0f))
    {
        XMVECTOR vec = XMLoadFloat2(&_direction);
        vec = XMVector2Normalize(vec) * (1.0f - EPSILON);
        XMStoreFloat2(&_direction, vec);
    }
}