void OGPhysic::update(double time){     
    
    Vector3d terrainNorm;
    Vector3d vertex;
    Vector3d pos;
    bool collision = terrainCollision(vertex, terrainNorm);
    
    Vector3d fp = Vector3d(0,ball->getMass() * gravity,0); //forza peso
    
    if (!collision){
        Vector3d faa = 6 * M_PI * viscosity * ball->getMass() * (wind - ball->getSpeed()); //forza attrito aria
        Vector3d fr = fp + faa; //forza attiva sulla pallina
        Vector3d acc = fr / ball->getMass();
        ball->setSpeed(ball->getSpeed() + (acc * time));
        pos = ball->getPosition() + (ball->getSpeed() * time);
    }else{
        //attrito radente
        Vector3d normV = ball->getSpeed().getNormalized();
        Vector3d fat = normV * terrainNorm.dot(fp) * friction;
        
        //calcolo forza peso parallela
        Vector3d fpp = fp.length() * terrainNorm + Vector3d(0,-1,0);
        Vector3d acc = fat + fpp / ball->getMass();
        
        Vector3d speed = ball->getSpeed();
        pos = ball->getPosition();
        
        speed = Vector3d(speed.x + (acc.x * time), -speed.y * elasticity, speed.z + (acc.z * time));
        
        pos = Vector3d(pos.x + (speed.x * time), vertex.y + (speed.y * time) ,pos.z + (speed.z * time));
        
        ball->setSpeed(speed);
    }
    
    ball->setPosition(pos.x, pos.y, pos.z);
    //update pov
    pov->setPosition(pos.x, pos.y , pos.z);

}