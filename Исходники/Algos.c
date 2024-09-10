//get the distance between two cities
int getDistance(struct structCity A, struct structCity B)
{
    //get distance between two cities
    int x=A.iX-B.iX;//subtract x coordinates
    int y=A.iY-B.iY;//subtract y coordinates
    double dist=pow(y,2)+pow(x,2);// raise both to the power of two and add
    double distance=sqrt(dist);//sqrt of the sum of x^2+y^2
    int myDistance=nearbyint(distance);//round to nearest int
    return myDistance;
}