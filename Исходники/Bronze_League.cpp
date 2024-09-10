int findNearestBludger(point p){

    int res = -1;
    float minDist = 100000;
    
     REP(i, n){
         if(obj[i].type[0] == 'B' ){
             float dist = p.distance(obj[i].loc);
             if(dist < minDist){
                 res = i;
                 minDist = dist;
             }
         }
     }

     return res;

}