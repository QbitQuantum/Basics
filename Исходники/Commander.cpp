void CPlayer::Update(float dt)
{
	CCommander::Update(dt);
	Select(dt);
	Move(dt);
}