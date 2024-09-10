Component* Component::getTopLevelComponent()
{
	Component* pParent = this;

	while( pParent )
	{
		if ( pParent->getParent() == NULL ) break;

		pParent = pParent->getParent();
	}

	return pParent;
}