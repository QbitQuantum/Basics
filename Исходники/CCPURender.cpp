void PUParticle3DModelRender::render( Renderer* renderer, const Mat4 &transform, ParticleSystem3D* particleSystem )
{
    if (!_isVisible)
        return;

    if (_spriteList.empty()) {
        for (unsigned int i = 0; i < particleSystem->getParticleQuota(); ++i) {
            Sprite3D *sprite = Sprite3D::create(_modelFile);
            if (sprite == nullptr)
            {
                CCLOG("failed to load file %s", _modelFile.c_str());
                continue;
            }
            sprite->setTexture(_texFile);
            sprite->setBlendFunc(particleSystem->getBlendFunc());
            sprite->setCullFaceEnabled(false);
            sprite->retain();
            _spriteList.push_back(sprite);
        }
        if (!_spriteList.empty()) {
            const AABB &aabb = _spriteList[0]->getAABB();
            Vec3 corners[8];
            aabb.getCorners(corners);
            _spriteSize = corners[3] - corners[6];
        } else {
            _isVisible = false;
            return;
        }
    }


    const ParticlePool& particlePool = particleSystem->getParticlePool();
    ParticlePool::PoolList activeParticleList = particlePool.getActiveDataList();
    Mat4 mat;
    Mat4 rotMat;
    Mat4 sclMat;
    Quaternion q;
    transform.decompose(nullptr, &q, nullptr);
    unsigned int index = 0;
    for (auto iter : activeParticleList)
    {
        auto particle = static_cast<PUParticle3D *>(iter);
        Mat4::createRotation(q * particle->orientation, &rotMat);
        sclMat.m[0] = particle->width / _spriteSize.x;
        sclMat.m[5]  = particle->height / _spriteSize.y;
        sclMat.m[10] = particle->depth / _spriteSize.z;
        mat = rotMat * sclMat;
        mat.m[12] = particle->position.x;
        mat.m[13] = particle->position.y;
        mat.m[14] = particle->position.z;
        if (_spriteList[index]->getCameraMask() != particleSystem->getCameraMask())
            _spriteList[index]->setCameraMask(particleSystem->getCameraMask());
        _spriteList[index]->setColor(Color3B(particle->color.x * 255, particle->color.y * 255, particle->color.z * 255));
        _spriteList[index]->setOpacity(particle->color.w * 255);
        _spriteList[index]->visit(renderer, mat, Node::FLAGS_DIRTY_MASK);
        ++index;
    }
}