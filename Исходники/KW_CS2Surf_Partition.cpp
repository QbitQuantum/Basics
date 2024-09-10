void KW_CS2Surf::GetSSMesh()
{
	//faces in each subspace,each vector<int> represents a face composed of vertices with indices <int>
	vector<vector<vector<int>>> vecTotalFaceVer;
	//faces in each subspace,each int represents the face id of the facet in a subspace (a face may contain many facets(eg,triangles))
	vector<vector<int>> vecTotalFace;
	//the order of each element in vecTotalFaceVer&vecTotalFace is consistent with the order of subspaces
	vecTotalFaceVer.resize(this->iSSspacenum);
	vecTotalFace.resize(this->iSSspacenum);
	for (unsigned int i=0;i<this->vecResortFace.size();i++)
	{
		ResortedFace currFace=vecResortFace.at(i);
		vector<int> currFaceVertexInd=currFace.vecFaceVertexInd;
		//the two subspace this face belongs to
		for (unsigned int j=0;j<currFace.vecOrient.size();j++)
		{
			int icurrSSId=currFace.vecSubspaceId.at(j);
			if (!currFace.vecOrient.at(j))
			{
				reverse(currFaceVertexInd.begin(),currFaceVertexInd.end());
			}
			vecTotalFaceVer.at(icurrSSId).push_back(currFaceVertexInd);
			vecTotalFace.at(icurrSSId).push_back(i);
			//reverse back to the originally saved order
			if (!currFace.vecOrient.at(j))
			{
				reverse(currFaceVertexInd.begin(),currFaceVertexInd.end());
			}
		}
	}

	//id of vertices stored in vecTotalFaceVer is the global vertex id,need to convert it 
	//to the id within each subspace mesh
	//all the vertices are collected from the faces, so isolated vertices caused by the 
	//subspace combination will not be taken account into consideration

	//subspace number after combination
	int iSSNumAfterComb=0;
	for (unsigned int i=0;i<vecTotalFaceVer.size();i++)
	{
		set<int> setSSVer;
		vector<vector<set<int>::iterator>> vecFaceSetIter;
		//put all vertex indices in, store the iterator
		for (unsigned int j=0;j<vecTotalFaceVer.at(i).size();j++)
		{
			vector<set<int>::iterator> currFaceSetIter;
			for (unsigned int k=0;k<vecTotalFaceVer.at(i).at(j).size();k++)
			{
				pair<set<int>::iterator, bool> pairResult=setSSVer.insert(vecTotalFaceVer.at(i).at(j).at(k));
				currFaceSetIter.push_back(pairResult.first);
			}
			vecFaceSetIter.push_back(currFaceSetIter);
		}
		//get the id within the subspace according to the iterator
		vector<vector<int>> vecLocalVerInd;
		for (unsigned int j=0;j<vecFaceSetIter.size();j++)
		{
			vector<int> LocalFace;
			for (unsigned int k=0;k<vecFaceSetIter.at(j).size();k++)
			{
				int iLocalId=distance(setSSVer.begin(),vecFaceSetIter.at(j).at(k));
				LocalFace.push_back(iLocalId);
			}
			vecLocalVerInd.push_back(LocalFace);
		}
		//convert to triangular mesh
		//a simple method (012345->012 023 034 045),may have bug 
		vector<vector<int>> vecTriLocalVerInd;
		vector<int> vecTriFaceId;//the subspace face id of each triangle
		for (unsigned int j=0;j<vecLocalVerInd.size();j++)
		{
			vector<int> vecCurrFace=vecLocalVerInd.at(j);
			int iSecondVerLocalId=1;
			int iFacetFaceId=vecTotalFace.at(i).at(j);
			for (unsigned int k=0;k<vecCurrFace.size()-2;k++)
			{
				vector<int> vecTriFace;
				vecTriFace.push_back(vecCurrFace.at(0));
				vecTriFace.push_back(vecCurrFace.at(iSecondVerLocalId));
				vecTriFace.push_back(vecCurrFace.at(iSecondVerLocalId+1));
				iSecondVerLocalId++;
				vecTriLocalVerInd.push_back(vecTriFace);
				vecTriFaceId.push_back(iFacetFaceId);
			}
		}
		//store all the points
		vector<Point_3> vecAllPoint;
		for (set<int>::iterator SetIter=setSSVer.begin();SetIter!=setSSVer.end();SetIter++)
		{
			vecAllPoint.push_back(Point_3(vecSSver.at(3*(*SetIter)),
				vecSSver.at(3*(*SetIter)+1),
				vecSSver.at(3*(*SetIter)+2)));
		}
		KW_Mesh currSSMesh;
		//if a subspace has been combined into others,still save it as an empty one,
		//in order to keep the order of subspaces
		if (!vecAllPoint.empty() && !vecTriLocalVerInd.empty())
		{
			//Convert_Array_To_KW_Mesh<HalfedgeDS> triangle(vecAllPoint,vecLocalVerInd);
			Convert_Array_To_KW_Mesh<HalfedgeDS> triangle(vecAllPoint,vecTriLocalVerInd);
			currSSMesh.delegate(triangle);
			//record the face id of each triangle
			assert(currSSMesh.size_of_facets()==vecTriFaceId.size());
			Facet_iterator FaceIter=currSSMesh.facets_begin();
			for (unsigned int j=0;j<vecTriFaceId.size();j++)
			{
				FaceIter->SetReserved(vecTriFaceId.at(j));
				FaceIter++;
			}
		}
		//save the subspace mesh
		if (!currSSMesh.empty())
		{
			iSSNumAfterComb++;
			OBJHandle::UnitizeCGALPolyhedron(currSSMesh,false,false);
		}
		this->vecSSMesh.push_back(currSSMesh);
		////test
		//if (!currSSMesh.empty())
		//{
		//	OBJHandle::UnitizeCGALPolyhedron(currSSMesh,false,false);
		//	this->vecSinglePoly.push_back(currSSMesh);
		//}
	}
	DBWindowWrite("initial subzone no.: %d\n",this->iSSspacenum);
	DBWindowWrite("subzone no. after combination: %d\n",iSSNumAfterComb);
}