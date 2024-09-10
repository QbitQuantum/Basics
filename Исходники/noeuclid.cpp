void DoneProbes(bool bReRun) {
    //#define CFM  .4
    //#define CFMXY .5
    double CFM = .2;
#define VCFM 1.0
#define COLLIDESIZE 0.5
    //Ratio of XY to Z
#define COLLIDESIZERATIO 3
#define MINSIDE .0
#define ITERATIONS 10


    //Here's what we do: gpTest->TargetLocation.r, .g, .b contains the new position we should be at, bar whatever forces we're receiving from the other rays.

    int i;

    Vec3f newp = gh.MapOffset;

    int iterations = 0;

    Quaternion orotmat[3];

    CollisionProbe * tp = gpTest;


    if (tp->Direction.r * tp->Direction.r + tp->Direction.g * tp->Direction.g + tp->Direction.b * tp->Direction.b > 0.0 && !bReRun) {
        Vec3f df = tp->TargetLocation.vec() - newp;

        double dtdiffx = df.len();

        newp = tp->TargetLocation.vec();

        double dirdiffx = sqrt(tp->Direction.r * tp->Direction.r + tp->Direction.g * tp->Direction.g + tp->Direction.b * tp->Direction.b);

        //Check to see if it's a jump, if so, consider re-running probes.
        if (dtdiffx > dirdiffx * 1.5 + 1.0) {
            printf("Jump %f %f %f -> %f %f %f\n", gh.MapOffset.x, gh.MapOffset.y, gh.MapOffset.z, tp->TargetLocation.r, tp->TargetLocation.g, tp->TargetLocation.b);
            newp = gh.MapOffset = tp->TargetLocation.vec(); // - tp->Direction.r; //??? WHY not these but Z?
            //XXX WHY WHY WHY??? WHY?? (Read why below)
            //XXX TODO TODO TODO!! There is a glitch.  We have to rotate the tp->Direction before adding it, otherwise really weird things will happen.
            //I haven't gotten around to this yet.

            //Attempt to correct direction of speed.
            gh.v = gpTestVelocity->NewDirection.vec();

            gh.ForceProbeReRun();
            goto clend;
        }
    }


    for (iterations = 0; iterations < ITERATIONS; iterations++)
        for (i = probes.size() - 1; i >= 0; i--) {
            CollisionProbe * tp = probes[i];
            //		if( tp->Normal.a > 1.0 ) continue;

            //		if( tp->TargetLocation.a > COLLIDESIZE ) continue;



            //We have a collision, need to "push" back.

            Vec3f sfn = tp->Normal.vec();

            //Actual hit xyz
            Vec3f t = tp->TargetLocation.vec();
            Vec3f nd = t - newp; //tp->Direction.r;		//Direction of ray.

            double nddiff = nd.len();
            if (nddiff < 0.00001 || std::isnan(nddiff)) {
                //fprintf( stderr, "Error: fault with tp direction.\n" );
                continue; //Don't know why this could happen.
            }

            //Make sure this was a resolved surface.  Unresolved services point to
            //some oopsies that happened inside the ray tracer.
            if (tp->Normal.r > 1) {
                continue;
            }



            nd /= nddiff;
            Vec3f iaw = tp->InAreaWarp.vec(); //Space compression


            double newcalcd = 0.0;
            //newcalcd = tp->TargetLocation.a;
            Vec3f newcollision = t - newp;
            newcollision.x /= iaw.x;
            newcollision.y /= iaw.y;
            newcollision.z /= iaw.z;

            //Tricky: newcollision can actually go inverted if the thing would be fast enough to get embedded.  Flip it back around.
            newcollision.x = fabs(newcollision.x) * ((nd.x > 0) ? 1 : -1);
            newcollision.y = fabs(newcollision.y) * ((nd.y > 0) ? 1 : -1);
            newcollision.z = fabs(newcollision.z) * ((nd.z > 0) ? 1 : -1);

            newcalcd = sqrt(newcollision.x * newcollision.x * COLLIDESIZERATIO + newcollision.y * newcollision.y * COLLIDESIZERATIO + newcollision.z * newcollision.z / COLLIDESIZERATIO);
            //		printf( "%f-%f %f-%f %f-%f ---\n", newcollisionx,newcollisiony,newcollisionz );

            if (newcalcd > COLLIDESIZE) continue;
            float press = (COLLIDESIZE - newcalcd) / COLLIDESIZE;

            tp->id = i;
            gamemap.collision(tp);

            /*
                            printf( " +%f (%f %f %f)  ->\n", press, newcollisionx, newcollisiony, newcollisionz );
                            printf( "  %f %f %f %f\n", tp->Position.r, tp->Position.g, tp->Position.b, tp->Position.a );   //x,y,z,unused
                            printf( "  %f %f %f %f\n", tp->Direction.r, tp->Direction.g, tp->Direction.b, tp->Direction.a );   //x,y,z,unused
                            printf( "  %f %f %f %f\n", tp->AuxRotation.r, tp->AuxRotation.g, tp->AuxRotation.b, tp->AuxRotation.a );   //x,y,z,unused
                            printf( "  %f %f %f %f\n", tp->NewDirection.r, tp->NewDirection.g, tp->NewDirection.b, tp->NewDirection.a );   //x,y,z,unused
                            printf( "  %f %f %f %f\n", tp->Normal.r, tp->Normal.g, tp->Normal.b, tp->Normal.a );   //x,y,z,unused
                            printf( "  %f %f %f %f\n", tp->InAreaWarp.r, tp->InAreaWarp.g, tp->InAreaWarp.b, tp->InAreaWarp.a );   //x,y,z,unused
                            printf( "  %f %f %f %f\n", tp->TargetLocation.r, tp->TargetLocation.g, tp->TargetLocation.b, tp->TargetLocation.a );   //x,y,z,unused
             */

            //If it is a bottom probe, we are on the ground.
            if (i > int(probes.size()) - 3) {
                gTimeSinceOnGround = 0;
                //gh.vZ = 0;
            }


            //First of all, nerf any motion toward the collision.
            {
                Vec3f ns = gh.v;
                ns /= ns.len();


                Vec3f dot {nd.x*ns.x,nd.y*ns.y,nd.z*ns.z};
                if (dot.x > 0) {
                    gh.v.x *= (1. - dot.x * press) * VCFM;
                }
                if (dot.y > 0) {
                    gh.v.y *= (1. - dot.y * press) * VCFM;
                }
                if (dot.z > 0) {
                    gh.v.z *= (1. - dot.z * press * VCFM);
                }
            }
            //Next, push the MapOffset back
            //(Change newx, newy, newz)

            //(ndx,ndy,ndz) represents ray.
            //(tx, ty, tz)  represents target ray hit.
            //press = distance of compression.

            Vec3f nid = newcollision * press;
            nid = nid * CFM;
            nid = {nid.x*iaw.x,nid.y*iaw.y,nid.z*iaw.z};

            if (sqrt(nid.x * nid.x + nid.y * nid.y) < MINSIDE) {
                nid.x = nid.y = 0;
            }

            newp.x -= nid.x * fabs(sfn.x);
            newp.y -= nid.y * fabs(sfn.y);
            newp.z -= nid.z * fabs(sfn.z);
        }

    if (!gGodMode) {
        gh.MapOffset = newp;
    }


    //Extract Yaw, Pitch, Roll.

    //	printf( "%f %f %f\n", gpRotFwd->NewDirection.r, gpRotFwd->NewDirection.g, gpRotFwd->NewDirection.b );
    //	printf( "%f %f %f\n", gpRotUp->NewDirection.r, gpRotUp->NewDirection.g, gpRotUp->NewDirection.b );

    /*
            float PlusZ[3];
            float Up[3];
            float Fwd[3];
     */

    //Re-rotate the camera based on the jump.
    

    orotmat[0] = gpRotFwd->NewDirection; //X
    orotmat[1] = gpRotUp->NewDirection; //Y
    orotmat[2] = orotmat[0].cross3d(orotmat[1]);
    //TODO: If we are in a situation where we're stuck on our side, don't exceute this line of code.
    LookQuaternion = Quaternion::fromMatrix((float*)orotmat).normalize();

    //Attempt to re-right the player

#define AUTO_RIGHT_COMP .8
    {
        Vec3f upout = LookQuaternion * Vec3f{0, 1, 0};
        Vec3f fwdtestout = LookQuaternion * Vec3f{0, 0, 1};
        Vec3f lefttestout = LookQuaternion * Vec3f{1, 0, 0};
        upout.z *= -1;
        fwdtestout.x *= -1;
        lefttestout.x *= -1;
        fwdtestout.y *= -1;
        lefttestout.y *= -1;

        lefttestout.z = 0; //Force flat test.

        float irtcos = upout.dot(lefttestout) * AUTO_RIGHT_COMP; //how much effort to try to right?
        float cosofs = (3.14159 / 2.0);

        //Tricky: If we're upside-down we need to re-right ourselves.
        if (upout.z < 0) irtcos *= -1.0;

        Quaternion uprotator = Quaternion::fromAxisAngle({0, 0, 1}, acos(irtcos) - cosofs);
        LookQuaternion = LookQuaternion * uprotator;

    }
clend:
    probes.clear();
    gPosition = newp;
    gDirection = gpForward->Direction.vec();
    gTargetNormal = gpForward->Normal.vec();
    gTargetCompression = gpForward->InAreaWarp.vec();
    gTargetHit = gpForward->TargetLocation.vec();
    gTargetActualDistance = gpForward->Normal.a;
    gTargetProjDistance = gpForward->InAreaWarp.a;
    gTargetPerceivedDistance = gpForward->TargetLocation.a;


    gamemap.update();

    gOverallUpdateNo++;
    //printf( "%f %f %f\n", gPositionX, gPositionY, gPositionZ );

    //	printf( "%7.1f %7.1f %7.1f  /  %7.1f %7.1f %7.1f (%f %f %f)\n", NewYaw, NewPitch, NewRoll, Yaw, Pitch, Roll, gh.MapOffsetX, gh.MapOffsetY, gh.MapOffsetZ );
}