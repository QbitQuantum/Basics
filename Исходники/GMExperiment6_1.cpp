void GMExperiment6_1::tangent_check(int32 start_idx, int32 end_idx, vector<int> & knots, vector<Vector2f> &smoothData)
{
    Vector2f tangent_begin = firstDerivative(smoothData,start_idx);
    tangent_begin.normalize();
    //tangent_begin.normalise();
    for(int i=start_idx+1;i<end_idx; i++)
    {
           Vector2f tangent = firstDerivative(smoothData,i);
           tangent.normalize();
       if( (tangent[0]*tangent_begin[0]+tangent[1]*tangent_begin[1]) < cos(tangent_filter_angle*M_PI/180.0) )//if tangents off by more than 90 deg
       {
           knots.push_back(i);
           tangent_check(i,end_idx,knots,smoothData);
           break;
       }
    }
}