void Outils::ajouterBouton(Boutons *b) {
    lesBoutons.push_back(b);
    blit(b->getBouton(),lesOutils,0,0,b->getX(),b->getY(),b->getW(),b->getH());
    setH(b->getY()+b->getH());
    line(lesOutils,getW()-1,0,getW()-1,getH(),0);
    line(lesOutils,getW(),getH(),0,getH(),0);    
    line(lesOutils,0,getH(),0,0,0);
}