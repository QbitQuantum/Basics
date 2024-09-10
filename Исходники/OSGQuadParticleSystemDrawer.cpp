Action::ResultE QuadParticleSystemDrawer::draw(DrawEnv *pEnv, ParticleSystemUnrecPtr System, const MFUInt32& Sort)
{
    bool isSorted(Sort.size() > 0);
    UInt32 NumParticles;
    if(isSorted)
    {
        NumParticles = Sort.size();
    }
    else
    {
        NumParticles = System->getNumParticles();
    }
    Pnt3f P1,P2,P3,P4;
    UInt32 Index;

    //Calculate the CameraToObject basis
    Matrix WorldToObject(pEnv->getObjectToWorld()); 
    WorldToObject.invert();

    Matrix CameraToObject(pEnv->getCameraToWorld()); 
    CameraToObject.mult(WorldToObject);

    glBegin(GL_QUADS);
        for(UInt32 i(0); i<NumParticles;++i)
        {
            if(isSorted)
            {
                Index = Sort[i];
            }
            else
            {
                Index = i;
            }
            //Loop through all particles
            //Get The Normal of the Particle
            Vec3f Normal = getQuadNormal(pEnv, System, Index, CameraToObject);


            //Calculate the Binormal as the cross between Normal and Up
            Vec3f Binormal = getQuadUpDir(pEnv,  System, Index, CameraToObject).cross(Normal);

            //Get the Up Direction of the Particle
            Vec3f Up = Normal.cross(Binormal);

            //Determine Local Space of the Particle
            //This is where error occurs
            Pnt3f Position = System->getPosition(Index);

            //Determine the Width and Height of the quad
            Real32 Width = System->getSize(Index).x()*getQuadSizeScaling().x(),Height =System->getSize(Index).y()*getQuadSizeScaling().y();

            //Calculate Quads positions
            P1 = Position + (Width/2.0f)*Binormal + (Height/2.0f)*Up;
            P2 = Position + (Width/2.0f)*Binormal - (Height/2.0f)*Up;
            P3 = Position - (Width/2.0f)*Binormal - (Height/2.0f)*Up;
            P4 = Position - (Width/2.0f)*Binormal + (Height/2.0f)*Up;

            //Draw the Quad
            glNormal3fv(Normal.getValues());

            glColor4fv(System->getColor(Index).getValuesRGBA());
            glTexCoord2f(1.0, 1.0);
            glVertex3fv(P1.getValues());


            glTexCoord2f(0.0, 1.0);
            glVertex3fv(P4.getValues());


            glTexCoord2f(0.0, 0.0);
            glVertex3fv(P3.getValues());

            glTexCoord2f(1.0, 0.0);
            glVertex3fv(P2.getValues());
        }
        glColor4f(1.0f,1.0f,1.0f,1.0f);
    glEnd();

    //Generate a local space for the particle
    return Action::Continue;
}