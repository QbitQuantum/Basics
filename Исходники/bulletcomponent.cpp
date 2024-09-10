void BulletComponent::update(float delta)
{
    EnemyComponent *enemy = target->getComponent<EnemyComponent>();

    if(enemy != nullptr) {
        destination = target->getPosition();
    }
    QVector3D dir = -(this->getEntity()->getPosition() - destination);
    if(dir.length() < 10) {
        if(enemy != nullptr) {
            enemy->takeDamage(damage);
            QVector3D v = getEntity()->getPosition();
            v.setX(v.x() / 768);
            v.setY(v.y() / 624);
            v.setZ(0);

            FMODManager::getInstance()->setCurrentEvent("event:/hit");
            FMODManager::getInstance()->setEventInstancePosition(v);
            FMODManager::getInstance()->setEventInstanceVolume(0.4);
            FMODManager::getInstance()->setParameterValue("pitch", 0.3 + (qrand() % 200) * 0.001);
            FMODManager::getInstance()->startEventInstance();
        }

        this->getEntity()->release();
    } else {
        dir.normalize();
        this->getEntity()->setPosition(this->getEntity()->getPosition() + dir * speed * delta);
    }
}