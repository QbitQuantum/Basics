Pose getDirTransform(Pose transformation) {
    Matrix4d dirTransformation = transformation.asMatrix();
    dirTransformation.invert();
    dirTransformation.transpose();
    Pose dirTransform(dirTransformation);
    return dirTransform;
}