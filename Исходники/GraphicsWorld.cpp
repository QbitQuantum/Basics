void GraphicsWorld::DebugDrawLight(const float3x4 &t, int lightType, float range, float spotAngle, const Color &clr, bool depthTest)
{
    float3 translate, scale;
    Quat rotate;
    t.Decompose(translate, rotate, scale);
    float3 lightDirection = rotate * float3(0.0f, 0.0f, 1.0f);
    switch (lightType)
    {
        // Point
    case 0:
        DebugDrawCircle(Circle(translate, float3(1.f, 0.f, 0.f), range), 8, clr, depthTest);
        DebugDrawCircle(Circle(translate, float3(0.f, 1.f, 0.f), range), 8, clr, depthTest);
        DebugDrawCircle(Circle(translate, float3(0.f, 0.f, 1.f), range), 8, clr, depthTest);
        break;
        
        // Spot
    case 1:
        {
            float3 endPoint = translate + range * lightDirection;
            float coneRadius = range * sinf(DegToRad(spotAngle));
            Circle spotCircle(endPoint, -lightDirection, coneRadius);
            
            DebugDrawCircle(Circle(endPoint, -lightDirection, coneRadius), 8, clr, depthTest);
            for (int i = 1; i <= 8; ++i)
                DebugDrawLine(translate, spotCircle.GetPoint(i * 2.f * 3.14f / 8), clr, depthTest);
        }
        break;
        
        // Directional
    case 2:
        {
            const float cDirLightRange = 10.f;
            float3 endPoint = translate + cDirLightRange * lightDirection;
            float3 offset = rotate * float3(1.f, 0.f, 0.f);
            DebugDrawLine(translate, endPoint, clr, depthTest);
            DebugDrawLine(translate + offset, endPoint + offset, clr, depthTest);
            DebugDrawLine(translate - offset, endPoint - offset, clr, depthTest);
        }
        break;
    }
}