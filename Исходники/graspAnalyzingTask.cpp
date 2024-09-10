 double perpendicularDistInBTrans(const position & p){
   position pInB = p*bodyTrans.inverse();
   //positions cannot be dotted with themselves because they aren't really meant to be used as vectors
   //    return sqrt(pInB%pInB - pInB%v);
   return sqrt(pInB.x()*pInB.x() + pInB.y()*pInB.y() + pInB.z()*pInB.z()- pow(pInB%v,2));
   
 }