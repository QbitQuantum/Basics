MatrixXf LinkedStructure::pseudoInverse()
{
  // Simple math that represents the mathematics
  // explained on the website to computing the
  // pseudo inverse. this is exactly the math
  // discussed in the tutorial!!!
    MatrixXf j = jacobian();
    MatrixXf jjtInv = (j * j.transpose());
    jjtInv = jjtInv.inverse();

    return (j.transpose() * jjtInv);
}