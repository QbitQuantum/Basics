      void  PerspectiveCamera::getPickRay(int x, int y, int w, int h, Vec3f& rayOrigin, Vec3f& rayDir) const
      {
        // note that getDirection and getUpVector do not return a reference but a copy of a Vec3f
        Vec3f camDir(getDirection());
        Vec3f upVec(getUpVector());

        rayOrigin = getPosition();
        rayDir = getFocusDistance() * camDir
               + getWindowSize()[0] * (x - 0.5f * w) / w * (camDir ^ upVec)
               + getWindowSize()[1] * (y - 0.5f * h) / h * upVec;
        rayDir.normalize();
      }