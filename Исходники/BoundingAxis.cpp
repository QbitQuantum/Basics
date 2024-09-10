void BoundingAxis::_createAxisTicks(const Vector3f& start, const Vector3f& end,
                                    const Vector3f& normal,
                                    const Vector3f& normal2, bool flipTick,
                                    BoundingAxisData& bbAxisData)
{
    size_t currentAxis;
    if (Vector3f(end - start).find_max_index() >
        std::numeric_limits<float>::min())
        currentAxis = Vector3f(end - start).find_max_index();
    else
        currentAxis = Vector3f(end - start).find_min_index();

    const Vector2f range = _computeRange(bbAxisData.volInfo, currentAxis);
    const float rangeLength = range.y() - range.x();

    const float worldSpaceLength = start.distance(end);
    const float dataToWorldScale = worldSpaceLength / rangeLength;
    const float startTickValue = bbAxisData.tickDistance *
                                 std::ceil(range.x() / bbAxisData.tickDistance);
    const float worldSpaceOffset =
        (startTickValue - range.x()) * dataToWorldScale;
    const float worldSpaceTickDistance =
        bbAxisData.tickDistance * dataToWorldScale;

    const int32_t numberOfTick =
        (range.y() - startTickValue) / bbAxisData.tickDistance + 1;
    const Vector3f axisDir = vmml::normalize(end - start);

    Vector3f cross = vmml::normalize(vmml::cross(axisDir, normal));
    size_t tickAxis;
    if (cross.find_max() <= std::numeric_limits<float>::min())
        tickAxis = cross.find_min_index();
    else
        tickAxis = cross.find_max_index();

    for (int32_t i = 0; i < numberOfTick; ++i)
    {
        float tickHeight = 0.014f;
        Vector4f color(1.0, 0.69, 0.69, 1.0);
        const int32_t startTickValueInteger =
            std::round(startTickValue / bbAxisData.factor);
        const int32_t tickDistanceInteger =
            std::round(bbAxisData.tickDistance / bbAxisData.factor);

        if (((startTickValueInteger + tickDistanceInteger * i) %
             (tickDistanceInteger * 5)) == 0)
        {
            tickHeight *= 1.5;
            color = Vector4f(1.0, 1.0, 0.69, 1.0);
        }

        int sign = (0.0f < cross[tickAxis]) - (cross[tickAxis] < 0.0f);
        if (flipTick)
            sign = -sign;

        Vector3f posOnAxis =
            start + axisDir * (worldSpaceOffset + worldSpaceTickDistance * i);
        append3dVector(bbAxisData.vertices, posOnAxis);
        posOnAxis[tickAxis] = posOnAxis[tickAxis] + sign * tickHeight;
        append3dVector(bbAxisData.vertices, posOnAxis);

        for (uint32_t j = 0; j < 2; ++j)
        {
            append3dVector(bbAxisData.normals, normal);
            append3dVector(bbAxisData.normals2, normal2);
            append4dVector(bbAxisData.colors, color);
            bbAxisData.types.push_back(AXIS);
        }

        _nVertices += 2;
    }
}