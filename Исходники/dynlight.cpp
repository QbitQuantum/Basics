int finddynlights()
{
    closedynlights.setsize(0);
    if(!usedynlights) return 0;
    physent e;
    e.type = ENT_CAMERA;
    e.collidetype = COLLIDE_AABB;
    loopvj(dynlights)
    {
        dynlight &d = dynlights[j];
        if(d.curradius <= 0) continue;
        d.dist = camera1->o.dist(d.o) - d.curradius;
        if(d.dist > dynlightdist || isfoggedsphere(d.curradius, d.o) || pvsoccluded(d.o, 2*int(d.curradius+1)))
            continue;
        e.o = d.o;
        e.radius = e.xradius = e.yradius = e.eyeheight = e.aboveeye = d.curradius;
        if(collide(&e, vec(0, 0, 0), 0, false)) continue;

        int insert = 0;
        loopvrev(closedynlights) if(d.dist >= closedynlights[i]->dist) { insert = i+1; break; }
        closedynlights.insert(insert, &d);
    }
    return closedynlights.length();
}