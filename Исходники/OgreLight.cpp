    //-----------------------------------------------------------------------
    bool Light::isInLightRange(const Ogre::AxisAlignedBox& container) const
    {
        bool isIntersect = true;
        //Check the 2 simple / obvious situations. Light is directional or light source is inside the container
        if ((mLightType != LT_DIRECTIONAL) && (container.intersects(mDerivedPosition) == false))
        {
            //Check that the container is within the sphere of the light
            isIntersect = Math::intersects(Sphere(mDerivedPosition, mRange),container);
            //If this is a spotlight, do a more specific check
            if ((isIntersect) && (mLightType == LT_SPOTLIGHT) && (mSpotOuter.valueRadians() <= Math::PI))
            {
                //Create a rough bounding box around the light and check if
                Quaternion localToWorld = Vector3::NEGATIVE_UNIT_Z.getRotationTo(mDerivedDirection);

                Real boxOffset = Math::Sin(mSpotOuter * 0.5) * mRange;
                AxisAlignedBox lightBoxBound;
                lightBoxBound.merge(Vector3::ZERO);
                lightBoxBound.merge(localToWorld * Vector3(boxOffset, boxOffset, -mRange));
                lightBoxBound.merge(localToWorld * Vector3(-boxOffset, boxOffset, -mRange));
                lightBoxBound.merge(localToWorld * Vector3(-boxOffset, -boxOffset, -mRange));
                lightBoxBound.merge(localToWorld * Vector3(boxOffset, -boxOffset, -mRange));
                lightBoxBound.setMaximum(lightBoxBound.getMaximum() + mDerivedPosition);
                lightBoxBound.setMinimum(lightBoxBound.getMinimum() + mDerivedPosition);
                isIntersect = lightBoxBound.intersects(container);
                
                //If the bounding box check succeeded do one more test
                if (isIntersect)
                {
                    //Check intersection again with the bounding sphere of the container
                    //Helpful for when the light is at an angle near one of the vertexes of the bounding box
                    isIntersect = isInLightRange(Sphere(container.getCenter(), 
                        container.getHalfSize().length()));
                }
            }
        }
        return isIntersect;
    }