void CAICorpse::SetupFromSource( IEntity& sourceEntity, ICharacterInstance& characterInstance, const uint32 priority)
{
	// 1.- Move resources from source entity, into AICorpse
	GetEntity()->SetFlags(GetEntity()->GetFlags() | (ENTITY_FLAG_CASTSHADOW));

	sourceEntity.MoveSlot(GetEntity(), 0);

	// Moving everything from one slot into another will also clear the render proxies in the source.
	// Thus, we need to invalidate the model so that it will be properly reloaded when a non-pooled
	// entity is restored from a save-game.
	CActor* sourceActor = static_cast<CActor*>(gEnv->pGame->GetIGameFramework()->GetIActorSystem()->GetActor(sourceEntity.GetId()));
	if (sourceActor != NULL)
	{
		sourceActor->InvalidateCurrentModelName();
	}

	// 2.- After 'MoveSlot()', characterInstance is now stored inside CAICorpse
	// It needs to be now updated from the entity system
	characterInstance.SetFlags( characterInstance.GetFlags() | CS_FLAG_UPDATE );

#if AI_CORPSES_ENABLE_SERIALIZE
	m_modelName = characterInstance.GetFilePath();
#endif

	// 3.- Search for any attached weapon and clone them
	IItemSystem* pItemSystem = g_pGame->GetIGameFramework()->GetIItemSystem();

	IAttachmentManager* pAttachmentManager = characterInstance.GetIAttachmentManager();
	const uint32 attachmentCount = (uint32)pAttachmentManager->GetAttachmentCount();
	for(uint32 i = 0; i < attachmentCount ; ++i)
	{
		IAttachment* pAttachment = pAttachmentManager->GetInterfaceByIndex(i);
		assert(pAttachment != NULL);

		IAttachmentObject* pAttachmentObject = pAttachment->GetIAttachmentObject();
		if((pAttachmentObject == NULL) || (pAttachmentObject->GetAttachmentType() != IAttachmentObject::eAttachment_Entity))
			continue;

		const EntityId attachedEntityId = static_cast<CEntityAttachment*>(pAttachmentObject)->GetEntityId();

		IItem* pItem = pItemSystem->GetItem(attachedEntityId);
		if(pItem != NULL)
		{
			if(AllowCloneAttachedItem( pItem->GetEntity()->GetClass() ))
			{
				if(m_attachedItemsInfo.size() < m_attachedItemsInfo.max_size())
				{
					AttachedItem attachedItemInfo;
					attachedItemInfo.pClass = pItem->GetEntity()->GetClass();
					attachedItemInfo.attachmentName = pAttachment->GetName();

					attachedItemInfo.id = CloneAttachedItem( attachedItemInfo, pAttachment );
					m_attachedItemsInfo.push_back(attachedItemInfo);
				}
			}
		}	
	}

	//Only accept requested priority if it has attached weapons
	m_priority = (m_attachedItemsInfo.size() > 0) ? priority : 0;

	//Force physics to sleep immediately (if not already)
	IPhysicalEntity* pCorpsePhysics = GetEntity()->GetPhysics();
	if(pCorpsePhysics != NULL)
	{
		pe_action_awake awakeAction;
		awakeAction.bAwake = 0;
		pCorpsePhysics->Action( &awakeAction );
	}
}