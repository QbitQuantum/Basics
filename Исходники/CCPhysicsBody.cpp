void PhysicsBody::update(float delta)
{
    if (_node != nullptr)
    {
        for (auto shape : _shapes)
        {
            shape->update(delta);
        }
        
        Node* parent = _node->getParent();
        Node* scene = &_world->getScene();
        
        Vec2 position = parent != scene ? parent->convertToNodeSpace(scene->convertToWorldSpace(getPosition())) : getPosition();
        float rotation = getRotation();
        for (; parent != scene; parent = parent->getParent())
        {
			rotation -= parent->getRotation();
        }
        
        _positionResetTag = true;
        _rotationResetTag = true;
        _node->setPosition(position);
        _node->setRotation(rotation);
        _positionResetTag = false;
        _rotationResetTag = false;
        
        // damping compute
        if (_isDamping && _dynamic && !isResting())
        {
            _info->getBody()->v.x *= cpfclamp(1.0f - delta * _linearDamping, 0.0f, 1.0f);
            _info->getBody()->v.y *= cpfclamp(1.0f - delta * _linearDamping, 0.0f, 1.0f);
            _info->getBody()->w *= cpfclamp(1.0f - delta * _angularDamping, 0.0f, 1.0f);
        }
    }
}