void myCam::aktivatePlaymode(QVector3D kugelWhite, int abstand)
{
    this->activePlaymode = true;
    this->distanz = abstand;
    this->kugelWhite = kugelWhite;

    QVector3D position;
    position.setX(kugelWhite.x());
    position.setY(kugelWhite.y());
    position.setZ(kugelWhite.z());
    if(position.x()==0 && position.y()==0 && position.z() == 0)
    {
        position.setZ(-1);
    }
    position.normalize();
    position.setX(position.x()*abstand + kugelWhite.x());
    position.setY(8);
    position.setZ(position.z()*abstand + kugelWhite.z());
    //this->viewMatrix.setToIdentity();
    //this->viewMatrix.lookAt(position,kugelWhite,QVector3D(0,1,0));
    this->queueAnimation(position,kugelWhite,100);
    position = position-kugelWhite;

    if(position.x()>0 && position.z()>0)
    {
        this->angleY = atan(position.z()/position.x())*180/3.1415926-90;
    }
    else if(position.x()<0 && position.z()>0)
    {
        this->angleY = atan(-position.x()/position.z())*180/3.1415926;
    }
    else if(position.x()<0 && position.z()<0)
    {
        this->angleY = atan(position.z()/position.x())*180/3.1415926+90;
    }
    else if(position.x()>0 && position.z()<0)
    {
        this->angleY = atan(position.x()/-position.z())*180/3.1415926+180;
    }
    else if(position.x() == 0)
    {
        if(position.z()>0)
            this->angleY = 0;
        else
            this->angleY = 180;
    }
    else if(position.z() == 0)
    {
        if(position.x()>0)
            this->angleY = 270;
        else
            this->angleY = 90;
    }
    this->angleX = 15;
    this->camRotate(0,0);
    this->freeCameramode = false;
}