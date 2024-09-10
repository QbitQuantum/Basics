    Vector3 GridSource::getIntersectionStart(const Ray &ray, Real maxDistance) const
    {
        AxisAlignedBox box((Real)0, (Real)0, (Real)0, (Real)mWidth / mPosXScale, (Real)mHeight / mPosYScale, (Real)mDepth / mPosZScale);
        
        // Inside the grid
        if (box.intersects(ray.getOrigin()))
        {
            return ray.getOrigin();
        }
        
        // Outside the grid, ray intersects it
        std::pair<bool, Real> intersection = ray.intersects(box);
        if (intersection.first)
        {
            Vector3 direction = ray.getDirection().normalisedCopy();
            return ray.getOrigin() + direction * intersection.second;
        }

        // Outside the grid, ray doesn't intersect it
        return ray.getOrigin();
    }