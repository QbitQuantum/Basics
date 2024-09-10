//This will set the formation
void FormationBhvr::SetFormation(TimeValue t)
{
	INode *node;
	Matrix3 tempMatrix;


	//Make sure that the leader is not part of the follower array..
	RemoveLeaderFromFormation(t);


	INode *leader =  GetLeader(t);

	if(leader==NULL)
		return;
	Matrix3 leaderPosition = GetCurrentMatrix(leader,t);
	leaderPosition.NoScale(); //kill any scale if we have it 
	leaderPosition.Invert();  //it's inverted...


	int numDelegates = GetFollowerCount(t);	

	//zero out the formation matrix that's used for saving it out.
	pblock->ZeroCount(follower_matrix1);
	pblock->ZeroCount(follower_matrix2);
	pblock->ZeroCount(follower_matrix3);
	pblock->ZeroCount(follower_matrix4);

	for(int i =0;i<numDelegates;i++)
	{

		node = GetFollower(t,i);
		if(node)
		{
			tempMatrix = GetCurrentMatrix(node,t);
			tempMatrix.NoScale();
			Matrix3 leaderMat =tempMatrix*leaderPosition;
			AppendFollowerMatrix(t,leaderMat);

			//killed because matrix3 wasn't working ...pblock->Append(follower_matrix,1,&leaderMat);
		 
		
		}
		else
		{
			//we still set up follower_matrix so that the counts
			//of the follower_matrix tab and the follower tab are equal.
			tempMatrix.IdentityMatrix();
			AppendFollowerMatrix(t,tempMatrix);

			//pblock->Append(follower_matrix,1,&tempMat);
	
		}
	}

}