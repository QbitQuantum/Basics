    /**
     * Parameters are in radians.
     * Example front vectors:
     *   Yaw 0:(0,0,1), pi/2:(-1,0,0)
     */
    void setOrientation(float yaw, float pitch)
    {
        using std::sin;
        using std::cos;

        front.x = cos(yaw) * cos(pitch);
        front.y = sin(yaw) * cos(pitch);
        front.z = sin(pitch);

        up.x = -cos(yaw) * sin(pitch);
        up.y = -sin(yaw) * sin(pitch);
        up.z = cos(pitch);

        /*DSFMOD_TRACE("Front:" << front.x << "," << front.y << "," << front.z << " Up:"
                     << up.x << "," << up.y << "," << up.z);*/
    }