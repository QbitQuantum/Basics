    void SegmentShape2D::SetDirection(Vector2 value)
    {
        if (value != Vector2::Zero)
            value.Normalize();

        if (GetDirection() != value)
        {
            direction = value;
            revision = -1;
        }
    }