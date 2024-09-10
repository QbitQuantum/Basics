void
add2bbox(		/* expand bounding box to fit object */
    register OBJREC  *o,
    FVECT  bbmin,
    FVECT  bbmax
)
{
    CONE  *co;
    FACE  *fo;
    INSTANCE  *io;
    MESHINST  *mi;
    FVECT  v;
    register int  i, j;

    switch (o->otype) {
    case OBJ_SPHERE:
    case OBJ_BUBBLE:
        if (o->oargs.nfargs != 4)
            objerror(o, USER, "bad arguments");
        for (i = 0; i < 3; i++) {
            VCOPY(v, o->oargs.farg);
            v[i] -= o->oargs.farg[3];
            point2bbox(v, bbmin, bbmax);
            v[i] += 2.0 * o->oargs.farg[3];
            point2bbox(v, bbmin, bbmax);
        }
        break;
    case OBJ_FACE:
        fo = getface(o);
        j = fo->nv;
        while (j--)
            point2bbox(VERTEX(fo,j), bbmin, bbmax);
        break;
    case OBJ_CONE:
    case OBJ_CUP:
    case OBJ_CYLINDER:
    case OBJ_TUBE:
    case OBJ_RING:
        co = getcone(o, 0);
        if (o->otype != OBJ_RING)
            circle2bbox(CO_P0(co), co->ad, CO_R0(co), bbmin, bbmax);
        circle2bbox(CO_P1(co), co->ad, CO_R1(co), bbmin, bbmax);
        break;
    case OBJ_INSTANCE:
        io = getinstance(o, IO_BOUNDS);
        for (j = 0; j < 8; j++) {
            for (i = 0; i < 3; i++) {
                v[i] = io->obj->scube.cuorg[i];
                if (j & 1<<i)
                    v[i] += io->obj->scube.cusize;
            }
            multp3(v, v, io->x.f.xfm);
            point2bbox(v, bbmin, bbmax);
        }
        break;
    case OBJ_MESH:
        mi = getmeshinst(o, IO_BOUNDS);
        for (j = 0; j < 8; j++) {
            for (i = 0; i < 3; i++) {
                v[i] = mi->msh->mcube.cuorg[i];
                if (j & 1<<i)
                    v[i] += mi->msh->mcube.cusize;
            }
            multp3(v, v, mi->x.f.xfm);
            point2bbox(v, bbmin, bbmax);
        }
        break;
    }
}