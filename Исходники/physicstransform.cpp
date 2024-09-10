void PhysicsTransform::updateFromPeer(Qt3DCore::QNode *peer){
    Qt3DCore::QTransform *transform = static_cast<Qt3DCore::QTransform *>(peer);
    m_rotation = transform->rotation();
    m_scale = transform->scale3D();
    m_translation = transform->translation();
    updateMatrix();
    m_enabled = transform->isEnabled();
    m_dirty=true;
}