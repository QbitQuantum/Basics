void SinglePlayerScene::onContactSeparate(cocos2d::PhysicsContact &contact)
{
    auto nodeA = contact.getShapeA()->getBody()->getNode();
    auto nodeB = contact.getShapeB()->getBody()->getNode();

    if (nodeA == _takyan || nodeB == _takyan) {
        auto otherNode = nodeA == _takyan ? nodeB : nodeA;

        if (otherNode == _kicker && !m_game->isOver())
        {
            auto takyanBody = _takyan->getPhysicsBody();
            Vec2 v = takyanBody->getVelocity();
            float limitY = takyanBody->getMass() * 1.0f;
            if (v.y < limitY) {
                v.y = MAX(limitY, v.y * 2.5f);
            }
            float limitX = takyanBody->getMass() * 1.0f;
            if (v.x < -limitX || v.x > limitX) {
                v.x = limitX * (v.x < 0 ? -1 : 1);
            }

            if (m_scoreCanAcquire == 3)
            {
                Vec2 zero;
                float distance = zero.distance(v);
                v.x = 0;
                v.y = distance;
            }

            takyanBody->setVelocity(v);
        }
        else if (otherNode == _floorBounds && m_game->isPracticeMode())
        {
            m_game->setScore(0);

            auto takyanBody = _takyan->getPhysicsBody();
            Vec2 velocity;

            velocity.y = takyanBody->getMass() * 2.50f;
            takyanBody->setVelocity(velocity);
        }
    }
}