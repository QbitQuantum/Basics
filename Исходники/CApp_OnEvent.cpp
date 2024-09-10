//---------------------------------------------------------------------------
void CApp::OnEvent(SDL_Event *Event) {

    switch(Event->type) {

        case SDL_QUIT: {
            OnExit();
            break;
        }

        case SDL_KEYDOWN: {
            Snake->onEvent(Event);
            break;
        }

        default: {
            break;
        }
    }
}