void Worm::MoveInDirection(Vector2& direction, float distance)
{
   direction.Normalize();
   Vector2 newPoint = Vector2( m_head->GetPosition() + (direction * distance) );	

   m_head->SetPosition(newPoint);
   m_tail->moveTo(newPoint, distance);
}