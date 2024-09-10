Mat4 Bone::getVertexTransformMatrix(const Mat4& meshGeometryMatrix, const Mat4& globalPositionMatrix)
{
    if (this->linkMode == LinkMode::Additive) {
        // TODO:
        assert(false);
        return Mat4();
    } else {
        this->updateMatrix();

        Mat4 globalInitPosition = transformMatrix * meshGeometryMatrix;

        Mat4 transformLinkMatrixInverse = transformLinkMatrix.inverse();
        Mat4 clusterRelativeInitPosition = transformLinkMatrixInverse * globalInitPosition;

        Mat4 globalCurrentPositionInverse = globalPositionMatrix.inverse();
        Mat4 clusterRelativeCurrentPositionInverse = globalCurrentPositionInverse * getComponent<Transform>()->getWorldMatrix();

        return clusterRelativeCurrentPositionInverse * clusterRelativeInitPosition;
    }
}