Vec2 ParallaxNode::absolutePosition()
{
    Vec2 ret = _position;
    Node *cn = this;
    while (cn->getParent() != nullptr)
    {
        cn = cn->getParent();
        ret = ret + cn->getPosition();
    }
    return ret;
}