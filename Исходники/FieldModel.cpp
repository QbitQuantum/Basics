int FieldModel::getIndexOfAssociatedLine(const Pose2D& robotPose, const Vector2<>& start, const Vector2<>& end) const
{
  Vector2<> startOnField = robotPose * start;
  Vector2<> endOnField = robotPose * end;
  Vector2<> dirOnField = endOnField - startOnField;
  dirOnField.normalize();
  Vector2<> orthogonalOnField(dirOnField.y, -dirOnField.x);
  float sqrLineAssociationCorridor = sqr(parameters.lineAssociationCorridor);
  Vector2<> intersection, orthogonalProjection;

  int index = -1;
  for(unsigned int i=0; i<fieldLines.size(); ++i)
  {
    const FieldLine& fieldLine = fieldLines[i];
    if(getSqrDistanceToLine(fieldLine.start, fieldLine.dir, fieldLine.length, startOnField) > sqrLineAssociationCorridor ||
       getSqrDistanceToLine(fieldLine.start, fieldLine.dir, fieldLine.length, endOnField) > sqrLineAssociationCorridor)
      continue;
    if(!intersectLineWithLine(startOnField, orthogonalOnField, fieldLine.start, fieldLine.dir, intersection))
      continue;
    if(getSqrDistanceToLine(startOnField, dirOnField, intersection) > sqrLineAssociationCorridor)
      continue;
    if(!intersectLineWithLine(endOnField, orthogonalOnField, fieldLine.start, fieldLine.dir, intersection))
      continue;
    if(getSqrDistanceToLine(startOnField, dirOnField, intersection) > sqrLineAssociationCorridor)
      continue;
    if(index != -1) // ambiguous?
    {
      index = -1;
      break;
    }
    index = i;
  }
  return index;
}