void DynamicAnimation_init(DynamicAnimation* self, const SDL_Rect* dest, SDL_Texture* texture, const SDL_Rect** rectAnimation, uint32_t maxN, uint32_t currentN, uint32_t nbFrame)
{
	Animation_init((Animation*)self, dest, texture, maxN, currentN, nbFrame);
	self->rect = (SDL_Rect*)malloc(maxN * sizeof(SDL_Rect));
	uint32_t i;
	for(i=0; i < maxN; i++)
		copyRect(&(self->rect[i]), rectAnimation[i]);
    ((Animation*)self)->setSubNSpriteRect = &DynamicAnimation_setSubNSpriteRect;
	((Animation*)self)->setSubNSpriteRect((Animation*)self, currentN);
}