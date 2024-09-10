int pdgl_main_body()
{
    static float hull_planes[]= {
        1, 0, 0, 1,
        1, 1, 0, 1,
        0, 1, 0, 1,
        -1, 1, 0, 1,
        -1, 0, 0, 1,
        -1, -1, 0, 1,
        0, -1, 0, 1,
        1, -1, 0, 1,
        0, 0, 1, 1,
        0, 0, -1, 1,
    };

    static int t;
    char buf[64];
    float mins[3], maxs[3];
    float io[3], iv[4], fw[2], pt[4], f, g, v;
    float im[16], im1[16];
    int i, j, k;
    unsigned short *kcur;

    main_time+=pdgl_dt_f;
    V3F_COPY(main_cam_org, main_dlight_org);

    V3F_ZERO(main_dlight_org+3);
    main_dlight_org[3]=sin(main_time*0.25)*75;
    main_dlight_org[4]=cos(main_time*0.25)*75;
    main_dlight_org[5]=10;

    kcur=pdgl_keybuf;

    f=main_cam_ang[2]*(M_PI/180);
    fw[0]=-sin(f);
    fw[1]=cos(f);

    bsdeGetAttrFV(main_cam_id, BSDE_ORIGIN, main_cam_org, 3);
    bsdeGetAttrFV(main_cam_id, BSDE_VELOCITY, main_cam_vel, 3);

    if(main_cam_raw)
    {
        bsdeHide(main_cam_id);
    } else
    {
        bsdeUnhide(main_cam_id);
    }

    io[0]=main_cam_org[0]-10*sin(f);
    io[1]=main_cam_org[1]+10*cos(f);
    io[2]=main_cam_org[2];

    f=(((rand()&0xFFF)/2048.0)-1)*0.1;
    g=(((rand()&0xFFF)/2048.0)-1)*0.1;
    io[0]+=f;
    io[1]+=g;

    v=1000;

    while(*kcur)
    {
        if(*kcur==K_ESCAPE)
        {
            main_kill=1;
            return(-1);
        }
        if(*kcur==K_F10)
        {
//			Tex_DoScreenshot();
        }

        if(*kcur==K_F2)
        {
            main_cam_raw=!main_cam_raw;
        }

        if(*kcur=='a')
        {
            i=bsdeNewOBB(-1, -1, -1, 1, 1, 1);
            main_objs[main_nobjs++]=i;
            main_addsolid(i);
//			bsdeSetAttrFV(i, BSDE_ORIGIN, VEC3(f, g, 10), 3);
            bsdeSetAttrFV(i, BSDE_ORIGIN, io, 3);
            bsdeSetAttrF(i, BSDE_DENSITY, 1);

            bsdeSetAttrFV(i, BSDE_VELOCITY, main_cam_vel, 3);

            if(PDGL_KeyDown(K_ALT))
                bsdeSetAttrFV(i, BSDE_VELOCITY,
                              VEC3(v*fw[0], v*fw[1], 0), 3);
        }

        if(*kcur=='A')
        {
            i=bsdeNewAABB(-2, -2, -2, 2, 2, 2);
            main_objs[main_nobjs++]=i;
            main_addsolid(i);
//			bsdeSetAttrFV(i, BSDE_ORIGIN, VEC3(f, g, 10), 3);
            bsdeSetAttrFV(i, BSDE_ORIGIN, io, 3);
            bsdeSetAttrF(i, BSDE_DENSITY, 1);

            bsdeSetAttrFV(i, BSDE_VELOCITY, main_cam_vel, 3);

            if(PDGL_KeyDown(K_ALT))
                bsdeSetAttrFV(i, BSDE_VELOCITY,
                              VEC3(v*fw[0], v*fw[1], 0), 3);
        }

        if(*kcur=='s')
        {
            i=bsdeNewSphere(1);
            main_objs[main_nobjs++]=i;
            main_addsolid(i);
//			bsdeSetAttrFV(i, BSDE_ORIGIN, VEC3(f, g, 10), 3);
            bsdeSetAttrFV(i, BSDE_ORIGIN, io, 3);
            bsdeSetAttrF(i, BSDE_DENSITY, 1);

            bsdeSetAttrFV(i, BSDE_VELOCITY, main_cam_vel, 3);

            if(PDGL_KeyDown(K_ALT))
                bsdeSetAttrFV(i, BSDE_VELOCITY,
                              VEC3(v*fw[0], v*fw[1], 0), 3);
        }

        if(*kcur=='c')
        {
            i=bsdeNewCappedCylinder(2, 1);
            main_objs[main_nobjs++]=i;
            main_addsolid(i);
//			bsdeSetAttrFV(i, BSDE_ORIGIN, VEC3(f, g, 10), 3);
            bsdeSetAttrFV(i, BSDE_ORIGIN, io, 3);
            bsdeSetAttrF(i, BSDE_DENSITY, 1);

            bsdeSetAttrFV(i, BSDE_VELOCITY, main_cam_vel, 3);

            if(PDGL_KeyDown(K_ALT))
                bsdeSetAttrFV(i, BSDE_VELOCITY,
                              VEC3(v*fw[0], v*fw[1], 0), 3);
        }

        if(*kcur=='C')
        {
            i=bsdeNewCylinder(2, 1);
            main_objs[main_nobjs++]=i;
            main_addsolid(i);
//			bsdeSetAttrFV(i, BSDE_ORIGIN, VEC3(f, g, 10), 3);
            bsdeSetAttrFV(i, BSDE_ORIGIN, io, 3);
            bsdeSetAttrF(i, BSDE_DENSITY, 1);

            bsdeSetAttrFV(i, BSDE_VELOCITY, main_cam_vel, 3);

            if(PDGL_KeyDown(K_ALT))
                bsdeSetAttrFV(i, BSDE_VELOCITY,
                              VEC3(v*fw[0], v*fw[1], 0), 3);
        }

        if(*kcur=='h')
        {
            i=bsdeNewHullF(hull_planes, 10);
            main_objs[main_nobjs++]=i;
            main_addsolid(i);
//			bsdeSetAttrFV(i, BSDE_ORIGIN, VEC3(f, g, 10), 3);
            bsdeSetAttrFV(i, BSDE_ORIGIN, io, 3);
            bsdeSetAttrF(i, BSDE_DENSITY, 1);

            bsdeSetAttrFV(i, BSDE_VELOCITY, main_cam_vel, 3);

            if(PDGL_KeyDown(K_ALT))
                bsdeSetAttrFV(i, BSDE_VELOCITY,
                              VEC3(v*fw[0], v*fw[1], 0), 3);
        }

        if(*kcur=='m')
        {
            i=bsdeNewTriMeshF(main_gear_vecs, main_gear_tris,
                              main_gear_nvecs, main_gear_ntris);
            main_objs[main_nobjs++]=i;
            main_addsolid(i);
//			bsdeSetAttrFV(i, BSDE_ORIGIN, VEC3(f, g, 10), 3);
            bsdeSetAttrFV(i, BSDE_ORIGIN, io, 3);
            bsdeSetAttrF(i, BSDE_DENSITY, 1);

            bsdeSetAttrFV(i, BSDE_VELOCITY, main_cam_vel, 3);

            if(PDGL_KeyDown(K_ALT))
                bsdeSetAttrFV(i, BSDE_VELOCITY,
                              VEC3(v*fw[0], v*fw[1], 0), 3);
        }

        kcur++;
    }

    V3F_ZERO(iv);
    if(PDGL_KeyDown(K_SHIFT))
    {
        f=main_cam_ang[2]*(M_PI/180);
        if(PDGL_KeyDown(K_LEFTARROW))
        {
//			main_cam_org[0]-=pdgl_dt_f*15*cos(f);
//			main_cam_org[1]-=pdgl_dt_f*15*sin(f);
            iv[0]-=pdgl_dt_f*15*cos(f);
            iv[1]-=pdgl_dt_f*15*sin(f);
        }
        if(PDGL_KeyDown(K_RIGHTARROW))
        {
//			main_cam_org[0]+=pdgl_dt_f*15*cos(f);
//			main_cam_org[1]+=pdgl_dt_f*15*sin(f);
            iv[0]+=pdgl_dt_f*15*cos(f);
            iv[1]+=pdgl_dt_f*15*sin(f);
        }
    } else
    {
        if(PDGL_KeyDown(K_LEFTARROW))main_cam_ang[2]+=90*pdgl_dt_f;
        if(PDGL_KeyDown(K_RIGHTARROW))main_cam_ang[2]-=90*pdgl_dt_f;
    }
    if(PDGL_KeyDown(K_UPARROW))main_cam_ang[0]+=90*pdgl_dt_f;
    if(PDGL_KeyDown(K_DOWNARROW))main_cam_ang[0]-=90*pdgl_dt_f;

    f=main_cam_ang[2]*(M_PI/180);
    if(PDGL_KeyDown(K_HOME))
    {
//		main_cam_org[0]-=pdgl_dt_f*15*sin(f);
//		main_cam_org[1]+=pdgl_dt_f*15*cos(f);
        iv[0]-=pdgl_dt_f*15*sin(f);
        iv[1]+=pdgl_dt_f*15*cos(f);
    }
    if(PDGL_KeyDown(K_END))
    {
//		main_cam_org[0]+=pdgl_dt_f*15*sin(f);
//		main_cam_org[1]-=pdgl_dt_f*15*cos(f);
        iv[0]+=pdgl_dt_f*15*sin(f);
        iv[1]-=pdgl_dt_f*15*cos(f);
    }

//	if(PDGL_KeyDown(K_PGUP))main_cam_org[2]+=pdgl_dt_f*15;
//	if(PDGL_KeyDown(K_PGDN))main_cam_org[2]-=pdgl_dt_f*15;
    if(PDGL_KeyDown(K_PGUP))iv[2]+=pdgl_dt_f*15;
    if(PDGL_KeyDown(K_PGDN))iv[2]-=pdgl_dt_f*15;

    if(main_cam_raw)
    {
        V3F_ADD(main_cam_org, iv, pt);
        bsdeSetAttrFV(main_cam_id, BSDE_ORIGIN, pt, 3);

        V3F_ZERO(pt);
        bsdeSetAttrFV(main_cam_id, BSDE_VELOCITY, pt, 3);
    } else
    {
//		Vec3F_Add(main_cam_vel, iv, pt);
//		Vec3F_Scale(iv, 1.0/pdgl_dt_f, pt);
//		pt[0]=iv[0]/pdgl_dt_f;
//		pt[1]=iv[1]/pdgl_dt_f;
//		pt[2]=iv[2]/pdgl_dt_f+main_cam_vel[2];
//		bsdeSetAttrFV(main_cam_id, BSDE_VELOCITY, pt, 3);

//		bsdeGetAttrFV(main_cam_id, BSDE_VELOCITY, pt, 3);
//		V3F_ADDSCALE(pt, iv, 1.0/pdgl_dt_f, pt);

//		pt[0]=pt[0]*0.1+iv[0]*(1.0/pdgl_dt_f);
//		pt[1]=pt[1]*0.1+iv[1]*(1.0/pdgl_dt_f);
//		pt[2]=pt[2]+iv[2]*(1.0/pdgl_dt_f);

//		V3F_SCALE(iv, 1.0/pdgl_dt_f, pt);
//		bsdeSetAttrFV(main_cam_id, BSDE_CONTACT_VELOCITY, pt, 3);
//		bsdeSetAttrF(main_cam_id, BSDE_CONTACT_POWER, 500);

//		bsdeSetAttrFV(main_cam_id, BSDE_VELOCITY, pt, 3);

        V3F_SCALE(iv, 0.25*1.0/pdgl_dt_f, pt);
        pt[2]*=0.15;

        bsdeSetAttrFV(main_cam_id, BSDE_WANTED_VELOCITY, pt, 3);
        bsdeSetAttrI(main_cam_id, BSDE_WANTED_VELOCITY, 1);
    }

//	Draw_SetPerspective_3D(4.0/3.0, 90, 0,
//		VEC3(0, -15, 5), VEC3(90-45, 0, 0), 0, 0, pdgl_xs, pdgl_ys);

//	Draw_SetPerspective_3D(4.0/3.0, 90, 0,
//		VEC3(0, -10, 5), VEC3(90-45, 0, 0), 0, 0, pdgl_xs, pdgl_ys);

//	Draw_SetPerspective_3D(4.0/3.0, 90, 0,
//		VEC3(0, -15, 0), VEC3(90, 0, 0), 0, 0, pdgl_xs, pdgl_ys);

    Draw_SetPerspective_3D(4.0/3.0, 90, 0,
                           main_cam_org, main_cam_ang, 0, 0, pdgl_xs, pdgl_ys);

    glDisable(GL_CULL_FACE);
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);

    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

    pt[0]=0.8;
    pt[1]=0.8;
    pt[2]=0.8;
    pt[3]=1;
    glMaterialfv(GL_FRONT, GL_DIFFUSE, pt);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, pt);

    pt[0]=main_cam_org[0];
    pt[1]=main_cam_org[1];
    pt[2]=main_cam_org[2];
    pt[3]=1;
    glLightfv(GL_LIGHT0, GL_POSITION, pt);
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 1.0/1000.0);
//	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.0/100000.0);

    glEnable(GL_LIGHT0);

    glDisable(GL_LIGHTING);

    if(main_bsp)
    {
        relink_ents();
//		pdgl_main_drawlightnode(main_bsp, main_bsp);
        pdgl_main_faceid=0;
        pdgl_main_drawnode(main_bsp);
    } else
    {
        draw_ents2();
    }

    glDisable(GL_LIGHTING);
    glDisable(GL_CULL_FACE);

    glColor4f(1, 0, 0, 1);
    glBegin(GL_LINES);
    glVertex3f(io[0], io[1], io[2]);
    glVertex3f(io[0], io[1], io[2]-50);
    glEnd();


    f=bsdeGetWorldAttrF(BSDE_REALTIME);
//	g=bsdeGetWorldAttrF(BSDE_WORLDTIME);
//	printf("rt %f wt %f\n", f, g);

    bsdeStepWorld(pdgl_dt/1000.0);
//	bsdeStepWorld(1.0/1000.0);

    Draw_SetSolid2_2D(4.0/3.0, 400,
                      VEC3(0, 0, 0), VEC3(0, 0, 0), 0, 0, pdgl_xs, pdgl_ys);

//	GfxFont_SetFont("fixed", 0);
//	kprints(buf, "%2.2f fps", 1.0/(pdgl_dt/1000.0));
//	GfxFont_DrawString(buf, -400, 300-12-8,
//		8, 8,  0, 255, 0, 255);

    kcur=pdgl_keybuf;
    while(*kcur)
    {
        if(*kcur==K_F10)
        {
            glFinish();
//			Tex_DoScreenshot();
        }
        kcur++;
    }

    main_vidbuf_t+=pdgl_dt_f;
    if(main_vidbuf_fd && (main_vidbuf_t>1.0/15.0))
    {
        main_vidbuf_t-=1.0/15.0;

        glFinish();
        glReadPixels (0, 0, 800, 600, GL_RGBA, GL_UNSIGNED_BYTE,
                      main_vidbuf);
        fwrite(main_vidbuf, 1, 800*600*4, main_vidbuf_fd);
    }

    return(0);
}