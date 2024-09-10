void RogueSkill4::HandleNodeCollisionStart(StringHash eventType, VariantMap& eventData)
{
	using namespace NodeCollisionStart;

	SharedPtr<Node> otherNode = SharedPtr<Node>(static_cast<Node*>(eventData[P_OTHERNODE].GetPtr()));

	RigidBody* rb = static_cast<RigidBody*>(eventData[P_BODY].GetPtr());
	Node* noed = rb->GetNode();

	if (!otherNode->HasComponent<Health>())
	{
		noed->Remove();
		return;
	}

	if (otherNode->GetVar("npcType").GetInt() == 1)//terry
	{
		otherNode->GetComponent<Health>()->ModifyHealth(10, -1, false);

		if (otherNode->GetComponent<Health>()->health_ <= 0)
		{
			otherNode->GetComponent<Health>()->ModifyHealth(100, 0, false);
			otherNode->GetScene()->GetComponent<TerrySpawner>()->RespawnTerry(otherNode);
			return;
		}

		//otherNode->AddComponent(new Stunned(context_, main_, 2.0f), 0, LOCAL);

		noed->Remove();
	}
}