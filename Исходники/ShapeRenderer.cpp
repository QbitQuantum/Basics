void CShapeRenderer::DrawCone(const CMat4& mat, float fButtomRadius, float fTopRadius, float fHeight, CColor coneColor, CColor bottomColor, CColor topColor, bool bSolid) const
{
    DrawCircle(mat, fButtomRadius, bottomColor, bSolid);
    CMat4 translateMat;
    translateMat.SetTranslate(CVec3(0, fHeight, 0));
    CMat4 topMat = mat * translateMat;
    DrawCircle(topMat, fTopRadius, topColor, bSolid);
    if (bSolid)
    {
        CVec3 center(mat[12], mat[13], mat[14]);
        CVec3 upDirection = mat.GetUpVec3();
        upDirection = upDirection * fHeight;
        CVec3 topCenter = center + upDirection;
        CVertexPC point;
        point.position = topCenter;
        point.color = coneColor;
        std::vector<unsigned short> indicesData;
        std::vector<CVertexPC> vertexData;
        vertexData.push_back(point);
        static const float fStepRadians = DegreesToRadians(15);
        for (float fRadian = 0; fRadian <= MATH_PI_DOUBLE; fRadian += fStepRadians)
        {
            CVec3 pos(fButtomRadius * sinf(fRadian), 0, fButtomRadius * cosf(fRadian));
            pos *= mat;
            point.position = pos;
            vertexData.push_back(point);
            if (vertexData.size() >= 3)
            {
                unsigned short index = (unsigned short)vertexData.size();
                indicesData.push_back(0);
                indicesData.push_back(index - 2);
                indicesData.push_back(index - 1);
            }
        }
        CRenderManager::GetInstance()->RenderTriangle(vertexData, indicesData, true);
    }
    else
    {
        CVertexPC startPos, endPos;
        startPos.color = coneColor;
        endPos.color = coneColor;
        CVec3 topPoint(fTopRadius, fHeight, 0);
        CVec3 buttomPoint(fButtomRadius, 0, 0);
        startPos.position = topPoint * mat;
        endPos.position = buttomPoint * mat;
        CRenderManager::GetInstance()->RenderLine(startPos, endPos, 1.0f, true);
        topPoint.X() *= -1;
        buttomPoint.X() *= -1;
        startPos.position = topPoint * mat;
        endPos.position = buttomPoint * mat;
        CRenderManager::GetInstance()->RenderLine(startPos, endPos, 1.0f, true);
        topPoint = CVec3(0, fHeight, fTopRadius);
        buttomPoint = CVec3(0, 0, fButtomRadius);
        startPos.position = topPoint * mat;
        endPos.position = buttomPoint * mat;
        CRenderManager::GetInstance()->RenderLine(startPos, endPos, 1.0f, true);
        topPoint.Z() *= -1;
        buttomPoint.Z() *= -1;
        startPos.position = topPoint * mat;
        endPos.position = buttomPoint * mat;
        CRenderManager::GetInstance()->RenderLine(startPos, endPos, 1.0f, true);
    }
}