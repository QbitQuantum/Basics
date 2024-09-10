    void UnderWaterGodRay::_updateProjector()
    {
        Plane p(Vec3(0, 1, 0), mWaterPosition);
        Vec3 sunDir = Environment::Instance()->GetEvParam()->SunDir;
        Vec3 sunPos = Environment::Instance()->GetEvParam()->SunPos;
        Ray r(sunPos, sunDir);

        RayIntersectionInfo info = r.Intersection(p);

        mEnable = info.iterscetion;

        mProjPosition = sunPos + sunDir * info.distance;

        Vec3 y(0, 1, 0);

        if (sunDir.Dot(y) < 0.001)
            y = Vec3(0, 0, -1);

        Vec3 x = y.Cross(sunDir);
        y = sunDir.Cross(x);
        
        mProjMatrix.MakeRotationAxis(x, y, sunDir);
        mProjMatrix._41 = mProjPosition.x;
        mProjMatrix._42 = mProjPosition.y;
        mProjMatrix._43 = mProjPosition.z;
    }