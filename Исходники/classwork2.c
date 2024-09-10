struct circle computeArea(struct circle instance){
    instance.area = powf ( (pi * (instance.diameter * .5)), 2 );
    return instance;
}