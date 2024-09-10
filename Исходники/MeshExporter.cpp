void MeshExporter::_dumpJoint(IGameNode * node)
{
	IGameObject * obj = node->GetIGameObject();
	IGameObject::MaxType T = obj->GetMaxType();
	IGameObject::ObjectTypes type = obj->GetIGameType();
	const char * name = node->GetName();
		
	switch(type)
	{
	case IGameObject::IGAME_BONE:
	case IGameObject::IGAME_HELPER:
		{
			joint * bone = mMeshSource->NewJoint(node->GetName());
			int parent = -1;

			if (node->GetNodeParent())
			{
				parent = _getJointId(node->GetNodeParent()->GetName());

				mMeshSource->SetJointLink(parent, mMeshSource->GetJointCount() - 1);
			}
			else
			{
				INode* pNode = node->GetMaxNode()->GetParentNode();
				if (pNode)
					parent = _getJointId(pNode->GetName());
			}
				
			IGameControl * pGameControl = node->GetIGameControl();
			// base matrix
			{
				GMatrix matWorld = node->GetLocalTM();
				bone->position = Utility::ToFloat3(matWorld.Translation());
				bone->rotation = Utility::ToQuat(matWorld.Rotation());
				bone->scale = Utility::ToFloat3(matWorld.Scaling());

				/*
				if (node->GetNodeParent())
				{
					int parentId = _getBoneId(node->GetNodeParent()->GetName());

					if (parentId != -1)
					{
						xBone * parentBn = GetBone(parentId);

						bone->position = bone->position - parentBn->position;
						bone->orientation = parentBn->orientation.Inverse() * bone->orientation;
						bone->scale = bone->scale / parentBn->scale;
					}
				}
				*/
			}

			_dumpAnimation(pGameControl, mMeshSource->GetJointCount() - 1);
		}

		break;
	}
}