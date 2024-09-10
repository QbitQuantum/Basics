void GaGameComponent::drawMinimap()
{
	OsClient* Client = OsCore::pImpl()->getClient( 0 );
	MaVec2d ClientSize( Client->getWidth(), Client->getHeight() );
	MaVec2d Size( 100.0f, 100.0f );
	MaMat4d Transform;
	Transform.translation( ClientSize - MaVec2d( 100.0f, 100.0f ) );
	Canvas_->pushMatrix( Transform );
	Canvas_->drawBox( -Size, Size, RsColour( 0.05f, 0.05f, 0.05f, 1.0f ), 0 );
	
	for( auto* Unit : Units_ )
	{
		auto Position = Unit->getParentEntity()->getWorldPosition();

		// HACK: Rotate and flip appropriately later.
		Position.x( -Position.x() );
;
		if( Position.x() > -99.0f && Position.x() < 99.0f &&
			Position.z() > -99.0f && Position.z() < 99.0f )
		{
			Canvas_->drawBox( Position.xz() - MaVec2d( 1.0f, 1.0f ), Position.xz() + MaVec2d( 1.0f, 1.0f ), RsColour( 1.0f, 1.0f, 1.0f, 1.0f ), 0 );
		}
	}

	Canvas_->drawLineBox( -Size, Size, RsColour( 0.0f, 0.0f, 0.0f, 1.0f ), 0 );
	Canvas_->popMatrix();
}