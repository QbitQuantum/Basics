void NuTo::CollidableWallBase::VisualizationStatic(NuTo::Visualize::UnstructuredGrid& rVisualizer) const
{

    double size = 1.;
    if (*mBoxes.begin() == mOutsideBox)
        size = 2.;

    Eigen::Matrix<double, 4, 3> corners;

    // get some vector != mDirection
    Eigen::Vector3d random;
    random << 1, 0, 0;
    if (std::abs(random.dot(mDirection)) == 1)
    {
        random << 0, 1, 0;
    }

    Eigen::Vector3d transversal = random.cross(mDirection);
    Eigen::Vector3d transversal2 = transversal.cross(mDirection);

    //   normalize to size/2;
    transversal.normalize();
    transversal2.normalize();

    transversal *= size / 2;
    transversal2 *= size / 2;

    corners.row(0) = (mPosition + transversal + transversal2).transpose();
    corners.row(1) = (mPosition + transversal - transversal2).transpose();
    corners.row(2) = (mPosition - transversal - transversal2).transpose();
    corners.row(3) = (mPosition - transversal + transversal2).transpose();


    std::vector<int> cornerIndex(4);
    for (int i = 0; i < 4; ++i)
    {
        cornerIndex[i] = rVisualizer.AddPoint(corners.row(i));
    }
    int insertIndex = rVisualizer.AddCell(cornerIndex, eCellTypes::QUAD);

    rVisualizer.SetCellData(insertIndex, "Direction", mDirection);
}