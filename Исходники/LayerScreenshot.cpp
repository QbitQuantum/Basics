void LayerScreenshot::computeGeometryOrient(
    const sp<const DisplayDevice>& hw, LayerMesh* mesh, int orient) const
{
    const Layer::State& s(drawingState());

    int hw_w = hw->getWidth();
    int hw_h = hw->getHeight();

    uint32_t flags = Transform::ROT_0;
    switch ((4 - orient) % 4) {
        case DisplayState::eOrientation90:
            flags = Transform::ROT_90;
            break;
        case DisplayState::eOrientation180:
            flags = Transform::ROT_180;
            break;
        case DisplayState::eOrientation270:
            flags = Transform::ROT_270;
            break;
        default:
            XLOGE("[%s] invalid orientation: %d", __func__, orient);
            break;
    }

    Transform orientTransform;
    if (orient & DisplayState::eOrientationSwapMask) {
        orientTransform.set(flags, hw_h, hw_w);
    } else {
        orientTransform.set(flags, hw_w, hw_h);
    }

    const Transform tr(hw->getTransform() * s.transform * orientTransform);

    if (mesh) {
        tr.transform(mesh->mVertices[0], 0, 0);
        tr.transform(mesh->mVertices[1], 0, hw_h);
        tr.transform(mesh->mVertices[2], hw_w, hw_h);
        tr.transform(mesh->mVertices[3], hw_w, 0);
        for (size_t i=0 ; i<4 ; i++) {
            mesh->mVertices[i][1] = hw_h - mesh->mVertices[i][1];
        }
    }
}