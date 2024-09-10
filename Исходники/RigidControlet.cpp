void OrientationControlet::setOrient( const Ogre::Vector3& o,
		const Ogre::Vector3& ax,
		const Ogre::Real s )
{
	if( mScale != s || !mNode ){
		//重新调整外观
		mScale = s;
		rebuildEntity();
	}
	mRaduis = ax.length() + 2*s;
	
	mNode->setPosition( o );
	mNode->setDirection( ax,Ogre::Node::TS_WORLD );
	mNodeLocal->setPosition( Ogre::Vector3(0,0,mRaduis) );
}