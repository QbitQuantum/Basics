void keyPress(unsigned char key, int x, int y){
    if (key == 'w'){
      btVector3 velocity(0,0,0);
      velocity = box2->getLinearVelocity();
      box2->applyCentralImpulse(btVector3(0,0,-3));
    }
    if (key == 's'){
      btVector3 velocity(0,0,0);
      velocity = box2->getLinearVelocity();
      box2->applyCentralImpulse(btVector3(0,0,3));
    }
   if (key == 'a'){
      btVector3 velocity(0,0,0);
      velocity = box2->getLinearVelocity();
      box2->applyCentralImpulse(btVector3(-3,0,0));
    }
   if (key == 'd'){
      btVector3 velocity(0,0,0);
      velocity = box2->getLinearVelocity();
      box2->applyCentralImpulse(btVector3(3,0,0));
    }
    else if (key == 27){
      quick_exit(0);
    }
    tim();
}