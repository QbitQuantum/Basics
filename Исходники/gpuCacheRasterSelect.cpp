//------------------------------------------------------------------------------
//
void RasterSelect::processTriangles(
    const SubNode::Ptr rootNode,
    double seconds,
    size_t /* numTriangles */,
    VBOProxy::VBOMode vboMode
)
{
    M3dView view = fSelectInfo.view();

    MMatrix projMatrix;
    view.projectionMatrix(projMatrix);
    MMatrix modelViewMatrix;
    view.modelViewMatrix(modelViewMatrix);

    unsigned int x, y, w, h;
    view.viewport(x, y, w, h);
    double viewportX = static_cast<int>(x);   // can be less than 0
    double viewportY = static_cast<int>(y);   // can be less than 0
    double viewportW = w;
    double viewportH = h;

    fSelectInfo.selectRect(x, y, w, h);
    double selectX = static_cast<int>(x);  // can be less than 0
    double selectY = static_cast<int>(y);  // can be less than 0
    double selectW = w;
    double selectH = h;

    MMatrix selectAdjustMatrix;
    selectAdjustMatrix[0][0] = viewportW / selectW;
    selectAdjustMatrix[1][1] = viewportH / selectH;
    selectAdjustMatrix[3][0] = ((viewportX + viewportW/2.0) - (selectX + selectW/2.0)) / 
        viewportW * 2.0 * selectAdjustMatrix[0][0];
    selectAdjustMatrix[3][1] = ((viewportY + viewportH/2.0) - (selectY + selectH/2.0)) /
        viewportH * 2.0 * selectAdjustMatrix[1][1];

    MMatrix localToPort = modelViewMatrix * projMatrix * selectAdjustMatrix;

    {
        Frustum frustum(localToPort.inverse());
        MMatrix xform(modelViewMatrix);
        
        DrawShadedState state(frustum, seconds, vboMode);
        DrawShadedTraversal traveral(state, xform, false, Frustum::kUnknown);
        rootNode->accept(traveral);
    }
}