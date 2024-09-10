bool bScreen::blit(Dot in)
{
	SDL_Surface *temp = NULL;
	SDL_Surface *nScreen = NULL;
	SDL_Rect *player = new SDL_Rect;
	SDL_Rect pos;
	SDL_Rect offset;
	SDL_Rect camera;
	bool success = false;
	camera = in.getCamera();

	offset.x = 0;
	offset.y = 0;
	
	pos.x = (in.getx()) - (camera.x);
	pos.y = (in.gety())- (camera.y);
	temp = in.getPlayerImage(0);
	player->x = 10 + ((in.phase/2)*PLAYERSPRITEW);
	player->y = 3 + ((in.direction)*PLAYERSPRITEH);
	player->w = 20;
	player->h = 30;
	
	SDL_BlitSurface(this->background, &camera, this->screen, &offset);

	SDL_BlitSurface(temp , player, this->screen, &pos );
	
	
	//rember to ask about possible memory leak here 
	//	delete temp;

	return success;

}