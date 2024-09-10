bool SubdivScene::repositionSelectedVertex(int x, int y) {
    if (!selectedVertex)
        return false;

    printf("Repositioning vertex, (%i, %i)...\n", x,y);
    //In the plane perpendicular to camera->look, and through which the vertex passes, 
    //move vertex from where it is to where the mouse is

    //Use current vertex position to calculate the center of the screen
    Vec camPos = camera->getPos();
    Vec vPos = selectedVertex->getData().p;
    Vec diff = vPos - camPos;
    Vec look = camera->getLook().normalize();
    float cosAngle = sqrt(diff.normalize().dot(look));
    float lookLength = diff.length()*cosAngle;
    Vec centreDiff = look*lookLength;
    Vec diffInPlane = vPos - (camPos + centreDiff);
printf(" diffInPlane is"); diffInPlane.print();
printf(" Cam pos is"); camPos.print();


    float anglex = (x - Globals::getWidth()/2)*Globals::getFovx() * Globals::PI/180/Globals::getWidth();
    float angley = (y - Globals::getHeight()/2)*Globals::getFovy() * Globals::PI/180/Globals::getHeight();
    float hLength = tan(anglex)*centreDiff.length();
    float vLength = tan(angley)*centreDiff.length();
printf(" anglex is %f and angley is %f, fovx is %f\n", anglex, angley, Globals::getFovx());
printf(" hLength is %f and vLength is %f, hrat is %i\n", hLength, vLength, x - Globals::getWidth()/2);


    //calculate the shifts in the horiz and vertical directions
    Vec right = camera->getLook().cross(camera->getUp()).normalize()*hLength;
    Vec up = camera->getUp().normalize()*vLength;

printf(" Right is"); right.print();
printf(" up is"); up.print();

    Vec newPos = vPos + right + up - diffInPlane;
    selectedVertex->getData().p = newPos;

    printf("  Old position was (%f, %f, %f)\n", vPos.x, vPos.y, vPos.z);
    printf("  New position is (%f, %f, %f)\n", newPos.x, newPos.y, newPos.z);

    redrawRequired = true;
}