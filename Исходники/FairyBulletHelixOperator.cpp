void BulletHelixOperator::operateBulletEventSystem(Real timeElapsed)
{
    BulletEventSystem::BulletSystemVecotor::iterator it =  m_parent->getActiveBulletSystem().begin();
    while(it != m_parent->getActiveBulletSystem().end())
    {
        BulletSystem* pBulletSystem = *it;
        if(pBulletSystem && pBulletSystem->getIsCreated())
        {
            // 步骤：[6/2/2010 陈军龙]
            //      1.计算朝向
            //      2.将时间映射到曲线函数Sin （映射公式： (2 * PI) / (1 / Frequency) = x / Age  ）
            //      3.计算绕螺旋的旋转轴的旋转偏移量
            //        （绕任意轴旋转公式：v' = (v - (v 。n) 。n) * cosx + (v * n) * sinx + (v 。n)。n
            //        其中的 。代表点乘 * 代表叉乘，v是要旋转的向量，n是旋转轴，x是旋转的角度）
            //      4.根据到目标的百分比设置振幅，更新子弹位置
            static Ogre::Vector3 startpos = pBulletSystem->getCurrentPosition();
            Ogre::Vector3 direction = pBulletSystem->getTargetPosition() - startpos;
            direction.normalise();

            Real fCumulateTime = pBulletSystem->getAge();
            Real sinvalue = Ogre::Math::Sin(fCumulateTime * Ogre::Math::TWO_PI * m_frequency);
            Real cosvalue = Ogre::Math::Cos(fCumulateTime * Ogre::Math::TWO_PI * m_frequency);
            Ogre::Vector3 absoffset, vdelta;
            vdelta = Ogre::Vector3::UNIT_Y;//此次设置为Y轴，也可以设置为其它
            // v' = (v - (v 。n) 。n) * cosx + (v * n) * sinx + (v 。n)。n
            absoffset = (vdelta - (vdelta.dotProduct(direction)) * direction) * cosvalue
                        + (vdelta.crossProduct(direction)) * sinvalue
                        + (vdelta.dotProduct(direction)) *direction;

            Real oridistance = startpos.distance(pBulletSystem->getTargetPosition());
            Real curdistance = pBulletSystem->getCurrentPosition().distance(pBulletSystem->getTargetPosition());
            Real percent = Ogre::Math::RealEqual(oridistance, 0) ? 1 : curdistance/oridistance;

            TransformInfo info;
            info = pBulletSystem->getTransformInfo();
            Ogre::Vector3 vBulletPosition = info.mPosition;
            vBulletPosition += (m_amplitude * absoffset * percent);

            info.mPosition = vBulletPosition;
            pBulletSystem->setTransformInfo(info);
            pBulletSystem->setPosition(info.mPosition);
        }
        it ++;
    }
}