void Camera::getViewing(Matrix &result,
                        UInt32  OSG_CHECK_ARG(width ),
                        UInt32  OSG_CHECK_ARG(height))
{
    if (getBeacon() == NULL)
    {
        SWARNING << "Camera::setup: no beacon!" << std::endl;
        return;
    }

    getBeacon()->getToWorld(result);
    result.invert();
}