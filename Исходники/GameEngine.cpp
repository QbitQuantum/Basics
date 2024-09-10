void GameEngine::spawnProjectile(Vector3 dir) {
    //Creates a projectile!
    Projectile* obj;
    bool foundProjectile = false;

    for (unsigned int i = 0; i < m_projectiles->size(); i ++) {
        if (!m_projectiles->at(i)->getIsAlive()) {
               obj= m_projectiles->at(i);
               foundProjectile = true;
               break;
        }
    }
    if (!foundProjectile)
        return;

    obj->setIsAlive(true);
    obj->resetLifetime();

    obj->getEmitter()->setPosition(m_camera->center);
    obj->getEmitter()->initParticles();
    obj->getEmitter()->setIsAlive(true);

    //setting up rotation angle for drawing
    Vector3 orthVec = dir.cross(Vector3(5,0,0));
    float angle = -acos(dir.dot(Vector3(1,0,0)) / dir.length()) * 180.0 / 3.14 + 180.0;
    obj->setRotation(orthVec, angle);

    obj->setPosition(m_camera->center);
    obj->setVelocity(dir);
    obj->setIsProjectile();
}