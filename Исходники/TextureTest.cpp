void TextureTest::ProcessEvent(SDL_Event* event)
{
    switch(event->type)
    {
        case SDL_MOUSEBUTTONDOWN:
        {
            if(event->button.button == 4)
            {

            }
            else if(event->button.button == 5)
            {

            }
            break;
        }
        case SDL_KEYDOWN:
        {
            if(event->key.keysym.sym == SDLK_UP)
            {
                Vector2D oldSteer = v->GetVelocity();
                Vector2D temp = v->GetVelocity();
                temp.Normalize();
                v->SetVelocity(oldSteer+temp*16);
                //v->SetHeading(v->GetVelocity());
            }
            if(event->key.keysym.sym == SDLK_DOWN)
            {
                Vector2D oldSteer = v->GetVelocity();
                Vector2D temp = v->GetVelocity();
                temp.Normalize();
                v->SetVelocity(oldSteer-temp*163);
            }
            if(event->key.keysym.sym == SDLK_LEFT)
            {
                Matrix2D mat;
                //Vector2D vec = v->GetVelocity();
                Vector2D vecH = v->GetVelocity();
                //Vec2DRotateAroundO(vecH,angle);
                mat.Rotate(angle);
//
               //mat.Rotate(angle);
                mat.TransformVector(vecH);
//              / mat.TransformVector(vecH);
//                //v->SetVelocity(vec);
//                v->RotateHeadingToFacePosition(vecH);
                //v->SetSteeringForce(vecH);
                v->SetVelocity(vecH);
                angle=0.07;

            }
            break;
        }
        //case SDL_KEYUP
    }
}