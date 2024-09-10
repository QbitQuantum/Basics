//--------------------------------------------------------------------------------------
// Processes an inbox message that the manoeuvre received.
// Param1: A pointer to the message to process.
//--------------------------------------------------------------------------------------
void GuardedFlagCapture::ProcessMessage(Message* pMessage)
{
	switch(pMessage->GetType())
	{
	case FlagDroppedMessageType:
	{
		FlagDroppedMessage* pMsg = reinterpret_cast<FlagDroppedMessage*>(pMessage);
		if(pMsg->GetData().m_flagOwner != GetTeamAI()->GetTeam())
		{
			// The flag was dropped, the manoeuvre failed
			SetFailed(true);
		}
		break;
	}
	case ScoreUpdateMessageType:
	{
		ScoreUpdateMessage* pMsg = reinterpret_cast<ScoreUpdateMessage*>(pMessage);
		if(pMsg->GetData().m_team == GetTeamAI()->GetTeam())
		{
			// The flag was captured -> the manoeuvre succeeded
			SetSucceeded(true);
		}
		break;
	}
	case EntityKilledMessageType:
	{
		EntityKilledMessage* pMsg = reinterpret_cast<EntityKilledMessage*>(pMessage);
		if(IsParticipant(pMsg->GetData().m_id) && pMsg->GetData().m_team == GetTeamAI()->GetTeam())
		{
			// Participants that get killed, drop out of the manoeuvre
			m_pTeamAI->ReleaseEntityFromManoeuvre(pMsg->GetData().m_id);
		}
		break;
	}
	case AttackedByEnemyMessageType:
	{
		AttackedByEnemyMessage* pMsg = reinterpret_cast<AttackedByEnemyMessage*>(pMessage);

		if(pMsg->GetData().m_entityId == m_flagCarrierId)
		{
			// The flag carrier is being attacked, protect him.

			// Get the attack direction
			XMFLOAT2 viewDirection(0.0f, 0.0f);
			XMStoreFloat2(&viewDirection, XMLoadFloat2(&pMsg->GetData().m_attackPosition) - XMLoadFloat2(&GetParticipant(pMsg->GetData().m_entityId)->GetPosition()));

			// Send all protectors to the position of the attacker to protect the carrier
			for(std::vector<Entity*>::iterator it = m_participants.begin(); it != m_participants.end(); ++it)
			{
				if((*it)->GetId() != m_flagCarrierId)
				{
					// Change the movement target in the orders for the entities
					reinterpret_cast<MoveOrder*>(m_activeOrders[(*it)->GetId()])->SetTargetPosition(pMsg->GetData().m_attackPosition);
				}
			}

		}

		break;
	}
	case UpdateOrderStateMessageType:
	{
	// Cancel old order, Send Follow-Up Orders, finish manoeuvre etc
	UpdateOrderStateMessage* pMsg = reinterpret_cast<UpdateOrderStateMessage*>(pMessage);
	if(IsParticipant(pMsg->GetData().m_entityId))
	{
		if(pMsg->GetData().m_orderState == SucceededOrderState)
		{
			// Let the entity wait for the next movement update (switch to defend?)
		}else if(pMsg->GetData().m_orderState == FailedOrderState)
		{
			m_pTeamAI->ReleaseEntityFromManoeuvre(pMsg->GetData().m_entityId);
		}
	}
	break;
	}
	default:
		TeamManoeuvre::ProcessMessage(pMessage);
	}
}