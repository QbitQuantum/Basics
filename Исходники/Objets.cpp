BITMAP * Objets::getProprietes(int p_x,int p_y, int p_w, int p_h) {
    clear_to_color(proprietes,makecol(255,255,255));
    rect(proprietes,1,1,149,199,0);
    textprintf_ex(proprietes, font,35,10, makecol(0, 0, 0),makecol(255, 255, 255), "Proprietes");
    line(proprietes,0,20,200,20,0);
    textprintf_ex(proprietes, font,10,30, makecol(0, 0, 0),makecol(255, 255, 255), "Type : %s",nom);
    int _x,_y,_z;
    _x=(getX()-p_x);
    _y=(getY()-p_y);
    _z=getZ();

    if (!Tx->getSaisie())
        Tx->setValeur(_x);
    if (!Ty->getSaisie())
        Ty->setValeur(_y);
    if (!Tz->getSaisie())
        Tz->setValeur(_z);
    if (!Tw->getSaisie())
        Tw->setValeur(getW());
    if (!Th->getSaisie())
        Th->setValeur(getH());
    if (!Td->getSaisie())
        Td->setValeur(getD());

    textprintf_ex(proprietes, font,10,45, makecol(0, 0, 0),makecol(255, 255, 255), "x =");
    blit(Tx->getImage(),proprietes,0,0,Tx->getX(),Tx->getY(),Tx->getW(),Tx->getH());
    textprintf_ex(proprietes, font,10,60, makecol(0, 0, 0),makecol(255, 255, 255), "y =");
    blit(Ty->getImage(),proprietes,0,0,Ty->getX(),Ty->getY(),Ty->getW(),Ty->getH());
    textprintf_ex(proprietes, font,10,75, makecol(0, 0, 0),makecol(255, 255, 255), "z =");
    blit(Tz->getImage(),proprietes,0,0,Tz->getX(),Tz->getY(),Tz->getW(),Tz->getH());
    textprintf_ex(proprietes, font,10,90, makecol(0, 0, 0),makecol(255, 255, 255), "Longueur =");
    blit(Tw->getImage(),proprietes,0,0,Tw->getX(),Tw->getY(),Tw->getW(),Tw->getH());
    textprintf_ex(proprietes, font,10,105, makecol(0, 0, 0),makecol(255, 255, 255), "Largeur =");
    blit(Th->getImage(),proprietes,0,0,Th->getX(),Th->getY(),Th->getW(),Th->getH());
    textprintf_ex(proprietes, font,10,120, makecol(0, 0, 0),makecol(255, 255, 255), "Hauteur =");
    blit(Td->getImage(),proprietes,0,0,Td->getX(),Td->getY(),Td->getW(),Td->getH());

    char *lesens;
    if (sens=="N")
        lesens="Nord";
    else if (sens=="E")
        lesens="Est";
    else if (sens=="S")
        lesens="Sud";
    else if (sens=="O")
        lesens="Ouest";
    textprintf_ex(proprietes, font,10,135, makecol(0, 0, 0),makecol(255, 255, 255), "Sens = %s",lesens);
    delete [] lesens;

    textprintf_ex(proprietes, font,10,150, makecol(0, 0, 0),makecol(255, 255, 255), "Couleur = ");
    rectfill(proprietes,90,148,100,158,q_c);
    rect(proprietes,90,148,100,158,0);
    return proprietes;
}