// called after all nodes added. This function calculates the node velocities
void RNSpline::BuildSpline()
{
	if (NodeCount == 2)
	{
		Node[0].Velocity = GetStartVelocity(0);
		Node[NodeCount-1].Velocity = GetEndVelocity(NodeCount-1);
		return;
	}
	else if (NodeCount < 2)
		return;

	for (int i = 1; i < NodeCount-1; ++i)
	{
		CVector3D Next = Node[i+1].Position - Node[i].Position;
		CVector3D Previous = Node[i-1].Position - Node[i].Position;
		Next.Normalize();
		Previous.Normalize();

		// split the angle (figure 4)
		Node[i].Velocity = Next - Previous;
		Node[i].Velocity.Normalize();
	}
	// calculate start and end velocities
	Node[0].Velocity = GetStartVelocity(0);
	Node[NodeCount-1].Velocity = GetEndVelocity(NodeCount-1);
}