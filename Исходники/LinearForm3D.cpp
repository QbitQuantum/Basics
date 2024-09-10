/*******************************************************************************

  Purpose - 

 *******************************************************************************/
Vector3D LinearForm3D::collideToVector(LinearForm3D other)
{
    /* find the vector that occurs when both planes collide */
    Vector3D n = createNormalVector();
    n.cross(n, other.createNormalVector());

    return n;
}