bool CallbackAxisPointsAbstract::threePointsAreCollinear (const QTransform &transform)
{
  return (transform.determinant() == 0);
}