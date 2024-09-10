SkPath PlatformContextSkia::currentPathInLocalCoordinates() const
{
    SkPath localPath = m_path;
    const SkMatrix& matrix = m_canvas->getTotalMatrix();
    SkMatrix inverseMatrix;
    matrix.invert(&inverseMatrix);
    localPath.transform(inverseMatrix);
    return localPath;
}