void HelpText::update()
{
	Game* parent = static_cast<Game*>( getAncestor() );
	float camera = parent->camera;
	switch(parent->game_state){
	case GAME_START:
	case GAME_ING:
		position = Vector3( -90, 100, 300 );
		break;
	case GAME_CLEAR:
	case GAME_OVER:
		position = Vector3( -90, 100, camera + 300 );
		break;
	}
}