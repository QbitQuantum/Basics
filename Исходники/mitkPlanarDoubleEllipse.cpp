bool mitk::PlanarDoubleEllipse::SetControlPoint(unsigned int index, const Point2D& point, bool createIfDoesNotExist)
{
  switch (index)
  {
    case 0:
    {
      Point2D centerPoint = this->GetControlPoint(0);
      Vector2D vector = point - centerPoint;

      Superclass::SetControlPoint(0, point, createIfDoesNotExist);
      Superclass::SetControlPoint(1, this->GetControlPoint(1) + vector, createIfDoesNotExist);
      Superclass::SetControlPoint(2, this->GetControlPoint(2) + vector, createIfDoesNotExist);
      Superclass::SetControlPoint(3, this->GetControlPoint(3) + vector, createIfDoesNotExist);

      break;
    }

    case 1:
    {
      Vector2D vector = point - this->GetControlPoint(1);

      Superclass::SetControlPoint(1, point, createIfDoesNotExist);

      Point2D centerPoint = this->GetControlPoint(0);
      Vector2D outerMajorVector = point - centerPoint;

      Vector2D outerMinorVector;
      outerMinorVector[0] = outerMajorVector[1];
      outerMinorVector[1] = -outerMajorVector[0];

      if (!m_ConstrainCircle)
      {
        outerMinorVector.Normalize();
        outerMinorVector *= centerPoint.EuclideanDistanceTo(this->GetControlPoint(2));
      }

      Superclass::SetControlPoint(2, centerPoint + outerMinorVector, createIfDoesNotExist);

      Vector2D innerMajorVector = outerMajorVector;

      if (!m_ConstrainThickness)
      {
        innerMajorVector.Normalize();
        innerMajorVector *= centerPoint.EuclideanDistanceTo(this->GetControlPoint(3) - vector);
      }

      Superclass::SetControlPoint(3, centerPoint - innerMajorVector, createIfDoesNotExist);

      break;
    }

    case 2:
    {
      m_ConstrainCircle = false;
      Superclass::SetControlPoint(2, point, createIfDoesNotExist);

      break;
    }

    case 3:
    {
      m_ConstrainThickness = false;
      Superclass::SetControlPoint(3, point, createIfDoesNotExist);

      break;
    }

    default:
      return false;
  }

  return true;
}