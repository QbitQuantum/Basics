 /*
 *  GLUT calls this toutine when there is nothing else to do
 */
 void idlefunc()
 {
   double t = glutGet(GLUT_ELAPSED_TIME)/1000.0;
   int change = 2.0;
   int lane;
   idle[0] = fmod(90*t,360);
   idle[1] = fmod(45*t,360);
   idle[2] = fmod(30*t,360);
   idle[3] = fmod(22.5*t,360);
   idle[4] = fmod(18*t,360);
   idle[5] = fmod(15*t,360);
   //If rolling
   if(roll < rollmax)
   {
     roll += 1*change;
     ph -= (((6.0*change)*360) / rollmax) ;
     ph %= 360;
     zOffset += ((change*120.0) / rollmax);
     yOffset = 3 - 1.5*Sin(ph);
     explosion[3] += zOffset > 105.0 ? 1.0 : 0.0 ;
     if(zOffset >= 120.0)
     {
       ph = 0;
       zOffset = 0;
       yOffset = 3;
       xOffset = -31.0;
       roll = rollmax;
     }
   }
   for(lane = 0; lane < 8 ; lane++)
   {
     explode_and_reset(lane);
     roll_dat_ball(lane);
   }
   glutPostRedisplay();
 }