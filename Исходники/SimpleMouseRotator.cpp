void SimpleMouseRotator::rotate(int x, int y)
{
    // Account for change of original axes
    Quaternion<float> previousRotation(viewpoint->getRotation());
    previousRotation.inverse();
    Vector3<float> xAxis;
    Vector3<float> yAxis;
    QuatUtil::rotateVector(previousRotation, verticalAxis, xAxis);
    QuatUtil::rotateVector(previousRotation, horizontalAxis, yAxis);

    Quaternion<float> rotationChange(0.0f, 0.0f, 0.0f, 1.0f);
    Quaternion<float> xQuat;
    xQuat.set(yAxis, (float)toRadians(angle));
    if (previousX > x)
    {
        xQuat.inverse();
    }
    xQuat.normalize();
    int xDelta = static_cast<int>(std::abs(static_cast<float>(previousX - x)));
    for (int i = 0; i < xDelta; ++i)
    {
        rotationChange.multiply(xQuat);
    }
    Quaternion<float> yQuat;
    yQuat.set(xAxis, (float)toRadians(angle));
    if (previousY > y)
    {
        yQuat.inverse();
    }
    yQuat.normalize();
    int yDelta = static_cast<int>(std::abs(static_cast<float>(previousY - y)));
    for (int j = 0; j < yDelta; ++j)
    {
        rotationChange.multiply(yQuat);
    }
    rotationChange.normalize();
    previousX = x;
    previousY = y;
    Quaternion<float> r(viewpoint->getRotation());
    r.multiply(rotationChange);
    r.normalize();
    viewpoint->setRotation(r);
}