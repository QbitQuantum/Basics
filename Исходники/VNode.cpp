void
VNode::addRandomizedChildren(const Vector2& startPoint, const Vector2& targetPoint)
{
    static const float fudgeFactor = 0.3f;
    Vector2 orientation = targetPoint - startPoint;
    orientation.Normalize();
    orientation.X = MathUtil::RandomFloatInRange( orientation.X - fudgeFactor, orientation.X + fudgeFactor );
    orientation.Y = MathUtil::RandomFloatInRange( orientation.Y - fudgeFactor, orientation.Y + fudgeFactor );

    // n times...
    m_children.push_back( new VNode(startPoint, orientation) );
}