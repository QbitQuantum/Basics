void CBlendingAnimationsView::OnAnimationStartslump()
{
	SetTimer(3, 1, 0);
	KillTimer(2);
	KillTimer(1);
}