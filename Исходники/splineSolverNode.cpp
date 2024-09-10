void splineSolverNode::gsOrthonormalize( MVector &normal, MVector &tangent )
{
    // Gram-Schmidt Orthonormalization
    normal.normalize();
    MVector proj = normal * ( tangent * normal ); // normal * dotProduct(tangent,normal)
    tangent = tangent - proj;
    tangent.normalize();

}