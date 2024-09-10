void	FSsAnimeDecoder::UpdateMatrix(FSsPart* part , FSsPartAnime* anime , FSsPartState* state)
{

	IdentityMatrix( state->Matrix );

	if (state->Parent)
	{
		memcpy( state->Matrix , state->Parent->Matrix , sizeof( float ) * 16 );
	}

	// アンカー
	if ( state->Parent )
	{
		const FVector2D& parentSize = state->Parent->Size;
		state->Position.X = state->Position.X + state->Parent->Size.X * state->Anchor.X;
		state->Position.Y = state->Position.Y + state->Parent->Size.Y * state->Anchor.Y;
	}

	TranslationMatrixM( state->Matrix , state->Position.X, state->Position.Y, state->Position.Z );//
	RotationXYZMatrixM( state->Matrix , FMath::DegreesToRadians(state->Rotation.X) , FMath::DegreesToRadians(state->Rotation.Y) , FMath::DegreesToRadians( state->Rotation.Z) );
	ScaleMatrixM(  state->Matrix , state->Scale.X, state->Scale.Y, 1.0f );
}