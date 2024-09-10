void Piece::render(SDL_Rect location)
{
	if(context == NULL)
	{
		#if DEBUG > 1
		std::cerr << "Warning: Could not render piece, problem establishing game context\n";
		#endif
		return;
	}
	if(locationChanged(location,currentLocation))
	{
		copyRect(&currentLocation,location);
		SDL_BlitSurface(image,NULL,context->getRenderContext(),&currentLocation);
		context->screenUpdated = true;
	}
}