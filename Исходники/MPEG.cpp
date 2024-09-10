void MPEG::RenderFinal(SDL_Surface *dst, int x, int y)
{
    Stop();
    if ( VideoEnabled() ) {
        videoaction->RenderFinal(dst, x, y);
    }
    Rewind();
}