int main(int argc, char** argv)
{
    Win110ct win;
    Turtle * t = win.getTurtle();
    t->penDown();
    t->setPosition(512,200);
    t->setColour({128,128,255});

    for(int i=0; i<24; ++i)
    {
        t->setPosition(512,200);
        dragon(t, i, 400);
        win.render();
        SDL_Delay(2000);
        win.clearBack();
    }

    win.getchar();
    return 0;
}