void
IntElLine1PhF :: computeTransformationMatrixAt(GaussPoint *gp, FloatMatrix &answer)
{
    // Transformation matrix to the local coordinate system
    FloatArray G;
    this->computeCovarBaseVectorAt(gp, G);
    G.normalize();

    answer.resize(2, 2);
    answer.at(1, 1) =  G.at(1);
    answer.at(2, 1) = -G.at(2);
    answer.at(1, 2) =  G.at(2);
    answer.at(2, 2) =  G.at(1);

}