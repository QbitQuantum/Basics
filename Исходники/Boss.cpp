void Boss::comportamiento(Personaje* s, Mapa *map){
    
   
    if(clock_comportamiento.getElapsedTime().asMilliseconds()>4000)      
    { srand(time(NULL));
        int num = rand()%2;
    actitud=num;
    clock_comportamiento.restart();         
    }
    if(actitud==0){
    if(detectada && !muriendo){
        if(!rapido){ this->set_speed(fast); rapido = true;}
        int distancia = this->pos->getX() - s->getPosicion()->getX();
        if(distancia > 0){ 
            if(distancia < 15){ this->attack(s); }
            else{ this->atacando = false; this->orientacion = 1;}
        }
        else{
            if(distancia > -15){ this->attack(s); }
            else{ this->atacando = false; this->orientacion = 0;}
        }
        
        int aux = this->colision_Boss(map);
        if(!(aux == 0 && this->orientacion == 0 || aux == 1 && this->orientacion == 1)){
            this->move();
        }
        else{
            this->pos->setInicial();
            clock_posicion.restart();
        }
    }}
    
    if(actitud==1){
       
     if(detectada){
         this->getPosition()->setInicial();
          clock_posicion.restart();
        //if(this->clock_quieto.getElapsedTime().asSeconds() > 0.5){ this->quieto = false; }
        if(!rapido){ this->set_speed(fast); rapido = true;}
        int distancia = this->pos->getX() - s->getPosicion()->getX();
        if(distancia > 0){
            this->orientacion = 1; 
            this->attack2(s);
            //if(this->clock_quieto.getElapsedTime().asSeconds() > 0.1){ this->orientacion = 0; }
        }
        else{
            this->orientacion = 0; 
            this->attack2(s);
            //if(this->clock_quieto.getElapsedTime().asSeconds() > 0.1){ this->orientacion = 1; }
        }
        //this->move();
     }
    }
    
}