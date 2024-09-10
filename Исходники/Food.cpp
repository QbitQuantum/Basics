void Food::Initilize(Position * position)
{
								this->position = position;
								drawing = CreateBitmap(position);
								CollisionDetection::Instance()->Add(this);
}