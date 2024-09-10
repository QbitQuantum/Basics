void BSInterpolation::CalculateParameters()
{
    //int knotsNo;
    //calculate length between segments
    QList<float> segmentslength; //0...n+1
    float totalLength = 0;
    for (int i = 0; i<markers.length()-1; i++) {
        segmentslength.append(sqrt(pow((markers[i+1]->point.x()-markers[i]->point.x()),2)
                                   +pow((markers[i+1]->point.y()-markers[i]->point.y()),2)
                                   +pow((markers[i+1]->point.z()-markers[i]->point.z()),2)));
        totalLength += segmentslength[i];
    }
    //data set -> n+1 length
    //calculate parameters t -> length n+1
    parameters.append(0);
    float sum = 0;
    for (int i = 0; i<segmentslength.length(); i++) {
        sum += segmentslength[i];
        parameters.append(sum /totalLength);
    }
    //calculate knots -> n+1+p+1 = m+1 length
    //first and last p+1 point -> 0 and 1 respectively if clamped
    //knots - avarage of p parameters
    for (int i = 0; i<degree+1; i++) {
        knots.append(0);
    }
    sum = 0;
    for (int i = 1; i<parameters.length()-degree; i++) { //i = 1... n-p
        for (int j = i; j<degree+i; j++)
            sum += parameters[j];
        knots.append(sum/(float)degree);
        sum = 0;
    }
    for (int i = 0; i<degree+1; i++) {
        knots.append(1);
    }
}