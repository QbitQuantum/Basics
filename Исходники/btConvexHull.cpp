int HullLibrary::calchullgen(btVector3 *verts,int verts_count, int vlimit)
{
    if(verts_count <4) return 0;
    if(vlimit==0) vlimit=1000000000;
    int j;
    btVector3 bmin(*verts),bmax(*verts);
    btAlignedObjectArray<int> isextreme;
    isextreme.reserve(verts_count);
    btAlignedObjectArray<int> allow;
    allow.reserve(verts_count);

    for(j=0;j<verts_count;j++)
    {
        allow.push_back(1);
        isextreme.push_back(0);
        bmin.setMin (verts[j]);
        bmax.setMax (verts[j]);
    }
    btScalar epsilon = (bmax-bmin).length() * btScalar(0.001);
    btAssert (epsilon != 0.0);


    int4 p = FindSimplex(verts,verts_count,allow);
    if(p.x==-1) return 0; // simplex failed



    btVector3 center = (verts[p[0]]+verts[p[1]]+verts[p[2]]+verts[p[3]]) / btScalar(4.0);  // a valid interior point
    btHullTriangle *t0 = allocateTriangle(p[2],p[3],p[1]); t0->n=int3(2,3,1);
    btHullTriangle *t1 = allocateTriangle(p[3],p[2],p[0]); t1->n=int3(3,2,0);
    btHullTriangle *t2 = allocateTriangle(p[0],p[1],p[3]); t2->n=int3(0,1,3);
    btHullTriangle *t3 = allocateTriangle(p[1],p[0],p[2]); t3->n=int3(1,0,2);
    isextreme[p[0]]=isextreme[p[1]]=isextreme[p[2]]=isextreme[p[3]]=1;
    checkit(t0);checkit(t1);checkit(t2);checkit(t3);

    for(j=0;j<m_tris.size();j++)
    {
        btHullTriangle *t=m_tris[j];
        btAssert(t);
        btAssert(t->vmax<0);
        btVector3 n=TriNormal(verts[(*t)[0]],verts[(*t)[1]],verts[(*t)[2]]);
        t->vmax = maxdirsterid(verts,verts_count,n,allow);
        t->rise = dot(n,verts[t->vmax]-verts[(*t)[0]]);
    }
    btHullTriangle *te;
    vlimit-=4;
    while(vlimit >0 && ((te=extrudable(epsilon)) != 0))
    {
        int3 ti=*te;
        int v=te->vmax;
        btAssert(v != -1);
        btAssert(!isextreme[v]);  // wtf we've already done this vertex
        isextreme[v]=1;
        //if(v==p0 || v==p1 || v==p2 || v==p3) continue; // done these already
        j=m_tris.size();
        while(j--) {
            if(!m_tris[j]) continue;
            int3 t=*m_tris[j];
            if(above(verts,t,verts[v],btScalar(0.01)*epsilon))
            {
                extrude(m_tris[j],v);
            }
        }
        // now check for those degenerate cases where we have a flipped triangle or a really skinny triangle
        j=m_tris.size();
        while(j--)
        {
            if(!m_tris[j]) continue;
            if(!hasvert(*m_tris[j],v)) break;
            int3 nt=*m_tris[j];
            if(above(verts,nt,center,btScalar(0.01)*epsilon)  || cross(verts[nt[1]]-verts[nt[0]],verts[nt[2]]-verts[nt[1]]).length()< epsilon*epsilon*btScalar(0.1) )
            {
                btHullTriangle *nb = m_tris[m_tris[j]->n[0]];
                btAssert(nb);btAssert(!hasvert(*nb,v));btAssert(nb->id<j);
                extrude(nb,v);
                j=m_tris.size();
            }
        }
        j=m_tris.size();
        while(j--)
        {
            btHullTriangle *t=m_tris[j];
            if(!t) continue;
            if(t->vmax>=0) break;
            btVector3 n=TriNormal(verts[(*t)[0]],verts[(*t)[1]],verts[(*t)[2]]);
            t->vmax = maxdirsterid(verts,verts_count,n,allow);
            if(isextreme[t->vmax])
            {
                t->vmax=-1; // already done that vertex - algorithm needs to be able to terminate.
            }
            else
            {
                t->rise = dot(n,verts[t->vmax]-verts[(*t)[0]]);
            }
        }
        vlimit --;
    }
    return 1;
}