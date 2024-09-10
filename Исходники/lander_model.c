void lndr_step(Lander *lander, float dT)
{
    lander->x += lander->dX * dT;
    lander->y += lander->dY * dT;
    lander->dY += lander->dYY * dT;

    // Handle rotations
    if((glob_game.keysDown & GMK_LEFT) && lander->rotation < PI_2)
    {
        float dif = lander->dR * dT;
        if(lander->rotation + dif < PI_2)
            lander->rotation += dif;
        else
            lander->rotation = PI_2;
    }
    if((glob_game.keysDown & GMK_RIGHT) && lander->rotation > -PI_2)
    {
        float dif = lander->dR * dT;
        if(lander->rotation - dif > -PI_2)
            lander->rotation -= dif;
        else
            lander->rotation = -PI_2;
    }

    // Make zero sticky to make sure a vertical landing is possible
    if(fabs(lander->rotation) < lander->dR * dT - 0.01)
        lander->rotation = 0;

    // Deal with thrust
    double thrust = lndr_thrust_for_state(lander);
    lander->dX += -sin(lander->rotation) * thrust;
    lander->dY -= -cos(lander->rotation) * thrust;

    // Handle jet animations
    if(lander->jetState == JS_ON || lander->jetState == JS_INCREASING)
        lander->jetFrames += dT * 1000;
    else if(lander->jetState == JS_DECREASING)
        lander->jetFrames -= dT * 1000;

    if((glob_game.keysDown & GMK_UP) && lander->prevJetState != JS_INCREASING && lander->prevJetState != JS_ON)
        lander->jetState = JS_INCREASING;
    else if(lander->jetFrames > FLAME_GROW_RATE && lander->jetState == JS_INCREASING)
    {
        lander->jetFrames = 0;
        lander->jetState = JS_ON;
    }
    else if(!(glob_game.keysDown & GMK_UP) && lander->prevJetState == JS_ON)
    {
        lander->jetFrames = FLAME_GROW_RATE;
        lander->jetState = JS_DECREASING;
    }
    else if(!(glob_game.keysDown & GMK_UP) && lander->prevJetState == JS_INCREASING)
        lander->jetState = JS_DECREASING;
    else if(lander->jetState == JS_DECREASING && lander->jetFrames <= 0)
    {
        lander->jetState = JS_OFF;
        lander->jetFrames = 0;
    }

    // Save the current jet state
    lander->prevJetState = lander->jetState;

    // Generate new matrices
    lndr_gen_mv_matrix(lander);
    lndr_gen_jet_mv_matrix(lander);
}