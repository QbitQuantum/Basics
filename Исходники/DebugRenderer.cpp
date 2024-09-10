void DebugRenderer::AddSphereSector(const Sphere& sphere, const Quaternion& rotation, float angle,
    bool drawLines, const Color& color, bool depthTest)
{
    if (angle <= 0.0f)
        return;
    else if (angle >= 360.0f)
    {
        AddSphere(sphere, color, depthTest);
        return;
    }

    static const unsigned numCircleSegments = 8;
    static const unsigned numLines = 4;
    static const float arcStep = 45.0f;

    const unsigned uintColor = color.ToUInt();
    const float halfAngle = 0.5f * angle;
    const unsigned numArcSegments = static_cast<unsigned>(Ceil(halfAngle / arcStep)) + 1;

    // Draw circle
    for (unsigned j = 0; j < numCircleSegments; ++j)
    {
        AddLine(
            sphere.center_ + rotation * sphere.GetLocalPoint(j * 360.0f / numCircleSegments, halfAngle),
            sphere.center_ + rotation * sphere.GetLocalPoint((j + 1) * 360.0f / numCircleSegments, halfAngle),
            uintColor);
    }

    // Draw arcs
    const unsigned step = numCircleSegments / numLines;
    for (unsigned i = 0; i < numArcSegments - 1; ++i)
    {
        for (unsigned j = 0; j < numCircleSegments; j += step)
        {
            const float nextPhi = i + 1 == numArcSegments - 1 ? halfAngle : (i + 1) * arcStep;
            AddLine(
                sphere.center_ + rotation * sphere.GetLocalPoint(j * 360.0f / numCircleSegments, i * arcStep),
                sphere.center_ + rotation * sphere.GetLocalPoint(j * 360.0f / numCircleSegments, nextPhi),
                uintColor);
        }
    }

    // Draw lines
    if (drawLines)
    {
        for (unsigned j = 0; j < numCircleSegments; j += step)
        {
            AddLine(sphere.center_,
                sphere.center_ + rotation * sphere.GetLocalPoint(j * 360.0f / numCircleSegments, halfAngle),
                uintColor);
        }
    }
}