duration_t Duration(Segment *segmentp,Way *wayp,Profile *profile)
{
 speed_t    speed1=wayp->speed;
 speed_t    speed2=profile->speed[HIGHWAY(wayp->type)];
 distance_t distance=DISTANCE(segmentp->distance);

 if(speed1==0)
   {
    if(speed2==0)
       return(hours_to_duration(10));
    else
       return distance_speed_to_duration(distance,speed2);
   }
 else /* if(speed1!=0) */
   {
    if(speed2==0)
       return distance_speed_to_duration(distance,speed1);
    else if(speed1<=speed2)
       return distance_speed_to_duration(distance,speed1);
    else
       return distance_speed_to_duration(distance,speed2);
   }
}