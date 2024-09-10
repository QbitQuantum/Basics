Float	Quat::GetAngle() const
{
	Float	_w=w;
	if (_w<-1.f) _w=-1.f;
	else if (_w>1.f) _w=1.f;
	Float	s=Sqrt(1.f-_w*_w);

	return s>Float_Eps ? ACos(_w)*2.f : 0.f;
}