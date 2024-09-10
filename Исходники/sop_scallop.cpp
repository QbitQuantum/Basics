void SOP_Scallop::SaveDivMap(float time)
{
        OP_Context context(time);

        bool clip = (lockInputs(context) < UT_ERROR_ABORT);

        UT_BoundingBox bbox;

        if(clip)
        {
                const GU_Detail* input = inputGeo(0,context);
                if(input != NULL)
                {
                        //UT_Matrix4 bm;
                        int res = input->getBBox(&bbox);
                        if(res == 0) clip = false;
                }
                else clip = false;
                unlockInputs();
        };

        if(!clip) return;

        UT_String file;
        STR_PARM(file,"mappath", 11, 0, time);

        float& now=time;
        //////////////////////////////////////////////////////////////////////////

        Daemon::now=now;
        Daemon::bias = evalFloat("bias",0,now);

        int cnt = evalInt("daemons", 0, now);

        Daemon* daemons=new Daemon[cnt];

        float weights = 0;

        int totd=0;

        float maxR = 0;
        for(int i=1;i<=cnt;i++)
        {
                bool skip = (evalIntInst("enabled#",&i,0,now)==0);
                if(skip) continue;

                Daemon& d = daemons[totd];

                UT_String path = "";
                evalStringInst("obj#", &i, path, 0, now);

                if(path == "") continue;

                SOP_Node* node = getSOPNode(path);

                OBJ_Node* obj = dynamic_cast<OBJ_Node*>(node->getParent());

                if(obj == NULL) continue;

                obj->getWorldTransform(d.xform,context);

                d.weight = evalFloatInst("weight#",&i,0,now);

                d.c[0] = evalFloatInst("color#",&i,0,now);
                d.c[1] = evalFloatInst("color#",&i,1,now);
                d.c[2] = evalFloatInst("color#",&i,2,now);

                int mth = evalIntInst("model#",&i,0,now);

                switch(mth)
                {
                case 1:
                        d.method = Methods::Spherical;
                        break;
                case 2:
                        d.method = Methods::Polar;
                        break;
                case 3:
                        d.method = Methods::Swirl;
                        break;
                case 4:
                        d.method = Methods::Trigonometric;
                        break;
                case 5:
                        {
                                UT_String script;
                                evalStringInst("vexcode#", &i, script, 0, now);
                                d.SetupCVEX(script);

                                break;
                        };
                case 0:
                default:
                        d.method = Methods::Linear;
                };

                d.power = evalFloatInst("power#",&i,0,now);
                d.radius = evalFloatInst("radius#",&i,0,now);
                d.parameter = evalFloatInst("parameter#",&i,0,now);

                if(d.radius > maxR) maxR = d.radius;

                weights+=d.weight;
                totd++;
        };

        if(totd == 0)
        {
                delete [] daemons;
                return;
        };

        float base = 0.0;
        for(int i=0;i<totd;i++)
        {
                Daemon& d = daemons[i];
                d.range[0]=base;
                d.range[1] = base+d.weight/weights;
                base=d.range[1];
        };

        //////////////////////////////////////////////////////////////////////////
        int total = evalInt("count",0,now);
        int degr = evalInt("degr",0,now);

        total >>= degr;

        GU_Detail det;

        UT_Vector3 current(0,0,0);
        float C[3] = { 0,0,0 };

        float R=1.0f;

        float param=0.0f;

        srand(0);

        bool medial = (evalInt("mapmedial",0,now)!=0);
        int mapdiv = evalInt("mapdiv",0,now);

        //BoundBox Box;
        OctreeBox O(mapdiv);

        //if(medial)
        //{
                O.bbox=bbox;
        //}
        //else
        //{
        //      BoundBox::limit = evalInt("nodecount", 0, now);

        //      BoundBox::medial = (evalInt("mapmedial",0,now)!=0);

        //      float boxb[6];
        //      memcpy(boxb,bbox.minvec().vec,12);
        //      memcpy(boxb+3,bbox.maxvec().vec,12);
        //      Box.Organize(boxb);
        //};

        for(int i=-50;i<total;i++)
        {
                bool ok = false;

                float w = double(rand())/double(RAND_MAX);

                for(int j=0;j<totd;j++)
                {
                        ok = daemons[j].Transform(w,current,C,R,param);
                        if(ok) break;
                };

                if(i<0) continue;

                //if(medial)
                //{
                        float P[4] = { current.x(), current.y(), current.z(), R };
                        O.Insert(P);
                //}
                //else
                //{
                //      Box.CheckPoint(current.vec);
                //}
        };

        delete [] daemons;

        //////////////////////////////////////////////////////////////////////////

        int ita[3] = {-1,-1,-1};

        //if(medial)
        //{
                int count = 0;
                OctreeBox::at = det.addPrimAttrib("count",4,GB_ATTRIB_INT,&count);
                det.addVariableName("count","COUNT");

                float radius = 0.0f;
                OctreeBox::rt = det.addAttrib("radius",4,GB_ATTRIB_FLOAT,&radius);
                det.addVariableName("radius","RADIUS");

                OctreeBox::it = det.addPrimAttrib("mask",12,GB_ATTRIB_INT,ita);
                det.addVariableName("mask","MASK");

                float box[6] = {bbox.xmin(),bbox.xmax(),bbox.ymin(),bbox.ymax(),bbox.zmin(),bbox.zmax()};
                det.addAttrib("bbox",24,GB_ATTRIB_FLOAT,box);

                O.maxlevel = 0x01<<mapdiv;
                O.parentbbox = bbox;

                O.Build(det);
        //}
        //else  Box.Build(det);

        det.save(file.buffer(),1,NULL);

        // ...SAVE ATLAS

        {
                UT_String atlas =file;
                atlas+=".atlas";
                FILE* fa = fopen(atlas.buffer(),"wb");

                GEO_PrimList& pl = det.primitives();

                int cnt = pl.entries();

                fwrite(&cnt,sizeof(int),1,fa);

                float bb[6] = { bbox.xmin(), bbox.xmax(), bbox.ymin(), bbox.ymax(), bbox.zmin(), bbox.zmax() };
                fwrite(bb,sizeof(float),6,fa);

                fwrite(&(O.maxlevel),sizeof(int),1,fa);
                fwrite(&(O.maxlevel),sizeof(int),1,fa);
                fwrite(&(O.maxlevel),sizeof(int),1,fa);

                for(int i=0;i<cnt;i++)
                {
                        const GEO_PrimVolume* v = dynamic_cast<const GEO_PrimVolume*>(pl[i]);
                        UT_BoundingBox b;
                        v->getBBox(&b);
                        float _bb[6] = { b.xmin(), b.xmax(), b.ymin(), b.ymax(), b.zmin(), b.zmax() };
                        fwrite(_bb,sizeof(float),6,fa);

                        // MASK
                        fwrite(v->castAttribData<int>(OctreeBox::it),sizeof(int),3,fa);
                }

                fclose(fa);
        }
};