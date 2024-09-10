// the constructor
CCDIKSolver::CCDIKSolver(Actor* actor, Node* startNode, Node* endNode, bool cloneNodes) : Controller( actor )
{
	mStartNode	= startNode;
	mEndNode	= endNode;

	// if we want to clone the IK chain
	if (cloneNodes) 
	{
		mEndNode_Clone = endNode->Clone(actor);
		Node *tempNode = mEndNode_Clone;

		Node *i = endNode->GetParent();
		while (i != startNode)
		{
			tempNode->SetParent(i->Clone(actor));
			tempNode->GetParent()->AddChild(tempNode);
			tempNode = tempNode->GetParent();
			i = i->GetParent();
		}

		mStartNode_Clone = mStartNode->Clone(actor);
		tempNode->SetParent(mStartNode_Clone);
		mStartNode_Clone->AddChild(tempNode);
		mStartNode_Clone->SetParent(startNode->GetParent());

		// when cloning nodes, one iteration is enough to find the new solution
		mMaxIterations  = 1;
	}
	else
	{
		mEndNode_Clone	 = mEndNode;
		mStartNode_Clone = mStartNode;
		
		// The solver usually doesn't take more than 10 iterations to find the solution if its in reach.
		// Its usually below 5. If this is set higher, then the solver will meerly take longer to realise
		// that it cant reach the goal.
		mMaxIterations  = 10;
	}
	
	mHasSolution	= false;
	mDistThreshold	= 0.1f;
	mDoJointLimits  = true;
	mGoal.Set(0, 0, 0);
}