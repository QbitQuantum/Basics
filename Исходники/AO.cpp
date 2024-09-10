Vector CAOGenerator::RenderSceneFromPosition(Vector vecPosition, Vector vecDirection, CConversionFace* pRenderFace)
{
    TUnimplemented();

    CRenderingContext c(SMAKRenderer());

    c.UseFrameBuffer(&m_oRenderFB);

    // Bring it away from its poly so that the camera never clips around behind it.
    // Adds .001 because of a bug where GL for some reason won't show the faces unless I do that.
    Vector vecEye = vecPosition + (vecDirection + Vector(.001f, .001f, .001f)) * 0.1f;

    c.SetViewport(Rect(m_iRPVX, m_iRPVY, m_iRPVW, m_iRPVH));

    c.SetProjection(Matrix4x4::ProjectPerspective(120.0f, 1, 0.01f, 100.0f));
    c.SetView(Matrix4x4::ConstructCameraView(vecEye, vecDirection, Vector(0, 1, 0)));

    c.ClearColor();
    c.ClearDepth();

    for (size_t i = 0; i < m_aiSceneMaterials.size(); i++)
    {
        TAssert(i < SMAKWindow()->GetMaterials().size());
        if (i >= SMAKWindow()->GetMaterials().size())
            break;

        if (!m_aiSceneMaterialVerts[i])
            continue;

        c.UseMaterial(SMAKWindow()->GetMaterials()[i]);

        c.BeginRenderVertexArray(m_aiSceneMaterials[i]);
        c.SetPositionBuffer((size_t)0, 5*sizeof(float));
        c.SetTexCoordBuffer((size_t)3*sizeof(float), 5*sizeof(float));
        c.EndRenderVertexArray(m_aiSceneMaterialVerts[i]);
    }

    c.Finish();

#ifdef AO_DEBUG
    DebugRenderSceneLookAtPosition(vecPosition, vecDirection, pRenderFace);
    glFinish();
#endif

    c.ReadPixels(m_iRPVX, m_iRPVY, m_iRPVW, m_iRPVH, m_pvecPixels);

    Vector vecShadowColor;
    float flTotal = 0;

    for (size_t p = 0; p < m_iRPVW*m_iRPVH*m_iPixelDepth; p++)
    {
        float flColumn = fmod((float)p / (float)m_iPixelDepth, (float)m_iRPVW);

        Vector vecUV(flColumn / m_iRPVW, (float)(p / m_iPixelDepth / m_iRPVW) / m_iRPVH, 0);
        Vector vecUVCenter(0.5f, 0.5f, 0);

        // Weight the pixel based on its distance to the center.
        // With the huge FOV that we work with, polygons to the
        // outside are huge on the screen.
        float flWeight = (0.5f-(vecUV - vecUVCenter).Length())*2.0f;
        if (flWeight <= 0.1)
            continue;

        // Pixels in the center of the screen are much, much more important.
        flWeight = SLerp(flWeight, 0.2f);

        Vector vecPixel(m_pvecPixels[p].x, m_pvecPixels[p].y, m_pvecPixels[p].z);

        vecShadowColor += vecPixel * flWeight;
        flTotal += flWeight;
    }

    vecShadowColor /= flTotal;

    return vecShadowColor;
}