Asteroid::Asteroid(int ast_size){
    int i, gen, dots, interval, angle, radius, min_radius, delta_radius;
    Asteroid* ast;
    Dot d;

    item = NULL;

    dots = 3*pow(2,ast_size);
    interval = 360/dots;
    min_radius = 10*pow(2,ast_size);
    delta_radius = 1.25*min_radius;

    //Generating vertex
    for(i=0; i<dots; i++){
        angle = rand()%interval + i*interval;
        radius = rand()%delta_radius + min_radius;

        d.setX(radius*cos(angle*PI/180));
        d.setY(radius*sin(angle*PI/180));
        loop_vertex.push_back(d);
    }


    if(ast_size != SMALL){

        //Generating subparts
        gen = rand()%2+2;
        while(gen>0){
            ast = new Asteroid(ast_size-1);
            d.setX(rand()%4-2);
            d.setY(rand()%4-2);
            ast->setSpeed(d);
            parts.push_back(ast);
            gen--;
        }
    }

    if(ast_size == BIG){
        //Generating item
        gen = rand()%(NUM_ITEMS*3);
        if(gen%3 == 0){
            item = new Item(gen/3);
            item->setSpeed(rand()%360, 0.25);
        }
    }

    //Adjusting centroid
    centralize();

    //setColor(0, 1, (float)(BIG - ast_size)/BIG);
    setColor(0, (GLfloat)(ast_size*0.125 + 0.75), (GLfloat)(0.25-ast_size*0.125));
    setHandling(1);

    if(rand()%2 == 0){
        commands[TURN_LEFT] = true;
    }
    else{
        commands[TURN_RIGHT] = true;
    }
}