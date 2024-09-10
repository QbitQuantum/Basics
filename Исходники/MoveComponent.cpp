//==============================================================================
Bool MoveComponent::updateWorldTransform(SceneNode& node)
{
	m_prevWTrf = m_wtrf;
	const Bool dirty = bitsEnabled(Flag::MARKED_FOR_UPDATE);

	// If dirty then update world transform
	if(dirty)
	{
		const SceneNode* parent = node.getParent();

		if(parent)
		{
			const MoveComponent* parentMove = 
				parent->tryGetComponent<MoveComponent>();

			if(parentMove == nullptr)
			{
				// Parent not movable
				m_wtrf = m_ltrf;
			}
			else if(bitsEnabled(Flag::IGNORE_PARENT_TRANSFORM))
			{
				m_wtrf = m_ltrf;
			}
			else if(bitsEnabled(Flag::IGNORE_LOCAL_TRANSFORM))
			{
				m_wtrf = parentMove->getWorldTransform();
			}
			else
			{
				m_wtrf = parentMove->getWorldTransform().
					combineTransformations(m_ltrf);
			}
		}
		else
		{
			// No parent

			m_wtrf = m_ltrf;
		}

		// Now it's a good time to cleanse parent
		disableBits(Flag::MARKED_FOR_UPDATE);
	}

	// If this is dirty then make children dirty as well. Don't walk the 
	// whole tree because you will re-walk it later
	if(dirty)
	{
		Error err = node.visitChildrenMaxDepth(1, 
			[](SceneNode& childNode) -> Error
		{ 
			Error e = childNode.iterateComponentsOfType<MoveComponent>(
				[](MoveComponent& mov) -> Error
			{
				mov.markForUpdate();
				return ErrorCode::NONE;
			});

			(void)e;

			return ErrorCode::NONE;
		});

		(void)err;
	}

	return dirty;
}