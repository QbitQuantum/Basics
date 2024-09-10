void CreditsInit()
{

    SDL_Color textColor = { 255, 255, 255 };
    ImageLoad("../../Resource/matrix.png", &c_background);
    TextLoad(&t, "../../Resource/alien.ttf", 30);
    TextPos(&t, 20, 250);
    TextColor(&t, &textColor);

    ButtonInit(&back, "../../Resource/back.png", 700, 500);

}