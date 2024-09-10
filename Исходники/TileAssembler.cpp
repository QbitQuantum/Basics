    //=================================================================
    bool TileAssembler::readRawFile(std::string& pModelFilename,  ModelPosition& pModelPosition, AABSPTree<SubModel *> *pMainTree)
    {
        std::string filename = iSrcDir;
        if (filename.length() >0)
            filename.append("/");
        filename.append(pModelFilename);
        FILE *rf = fopen(filename.c_str(), "rb");
        if (!rf)
        {
            // depending on the extractor version, the data could be located in the root dir
            std::string baseModelFilename = pModelFilename.substr((pModelFilename.find_first_of("/")+1),pModelFilename.length());
            filename = iSrcDir;
            if (filename.length() >0)
                filename.append("/");
            filename.append(baseModelFilename);
            rf = fopen(filename.c_str(), "rb");
        }

        if (!rf)
        {
            printf("ERROR: Can't open model file in form: %s",pModelFilename.c_str());
            printf("...                          or form: %s",filename.c_str() );
            return false;
        }

        char ident[8];

        int trianglecount =0;

        #ifdef _ASSEMBLER_DEBUG
        int startgroup = 0;                     //2;
        int endgroup = INT_MAX;                 //2;
        fprintf(::g_df,"-------------------------------------------------\n");
        fprintf(::g_df,"%s\n", pModelFilename.c_str());
        fprintf(::g_df,"-------------------------------------------------\n");
        #else
        int startgroup = 0;
        int endgroup = INT_MAX;
        #endif

        // temporary use defines to simplify read/check code (close file and return at fail)
        #define READ_OR_RETURN(V,S) if (fread((V), (S), 1, rf) != 1) { \
                                        fclose(rf); return(false); }
        #define CMP_OR_RETURN(V,S)  if (strcmp((V),(S)) != 0)        { \
                                        fclose(rf); return(false); }

        READ_OR_RETURN(&ident, 8);
        if (strcmp(ident, "VMAP001") == 0)
        {
            // OK, do nothing
        }
        else if (strcmp(ident, "VMAP002") == 0)
        {
            // we have to read one int. This is needed during the export and we have to skip it here
            int tempNVectors;
            READ_OR_RETURN(&tempNVectors, sizeof(int));

        }
        else
        {
            // wrong version
            fclose(rf);
            return(false);
        }
        G3D::uint32 groups;
        char blockId[5];
        blockId[4] = 0;
        int blocksize;

        READ_OR_RETURN(&groups, sizeof(G3D::uint32));

        for (int g=0;g<(int)groups;g++)
        {
            // group MUST NOT have more then 65536 indexes !! Array will have a problem with that !! (strange ...)
            Array<int> tempIndexArray;
            Array<Vector3> tempVertexArray;

            AABSPTree<Triangle> *gtree = new AABSPTree<Triangle>();

            // add free gtree at fail
            #undef READ_OR_RETURN
            #undef CMP_OR_RETURN
            #define READ_OR_RETURN(V,S) if (fread((V), (S), 1, rf) != 1) { \
                                            fclose(rf); delete gtree; return(false); }
            #define CMP_OR_RETURN(V,S)  if (strcmp((V),(S)) != 0)        { \
                                            fclose(rf); delete gtree; return(false); }

            G3D::uint32 flags;
            READ_OR_RETURN(&flags, sizeof(G3D::uint32));

            G3D::uint32 branches;
            READ_OR_RETURN(&blockId, 4);
            CMP_OR_RETURN(blockId, "GRP ");
            READ_OR_RETURN(&blocksize, sizeof(int));
            READ_OR_RETURN(&branches, sizeof(G3D::uint32));
            for (int b=0;b<(int)branches; b++)
            {
                G3D::uint32 indexes;
                // indexes for each branch (not used jet)
                READ_OR_RETURN(&indexes, sizeof(G3D::uint32));
            }

            // ---- indexes
            READ_OR_RETURN(&blockId, 4);
            CMP_OR_RETURN(blockId, "INDX");
            READ_OR_RETURN(&blocksize, sizeof(int));
            unsigned int nindexes;
            READ_OR_RETURN(&nindexes, sizeof(G3D::uint32));
            if (nindexes >0)
            {
                unsigned short *indexarray = new unsigned short[nindexes*sizeof(unsigned short)];
                READ_OR_RETURN(indexarray, nindexes*sizeof(unsigned short));
                for (int i=0;i<(int)nindexes; i++)
                {
                    unsigned short val = indexarray[i];
                    tempIndexArray.append(val);
                }
                delete[] indexarray;
            }

            // ---- vectors
            READ_OR_RETURN(&blockId, 4);
            CMP_OR_RETURN(blockId, "VERT");
            READ_OR_RETURN(&blocksize, sizeof(int));
            unsigned int nvectors;
            READ_OR_RETURN(&nvectors, sizeof(int));

            float *vectorarray = 0;

            // add vectorarray free
            #undef READ_OR_RETURN
            #undef CMP_OR_RETURN
            #define READ_OR_RETURN(V,S) if (fread((V), (S), 1, rf) != 1) { \
                                            fclose(rf); delete gtree; delete[] vectorarray; return(false); }
            #define CMP_OR_RETURN(V,S)  if (strcmp((V),(S)) != 0)        { \
                                            fclose(rf); delete gtree; delete[] vectorarray; return(false); }

            if (nvectors >0)
            {
                vectorarray = new float[nvectors*sizeof(float)*3];
                READ_OR_RETURN(vectorarray, nvectors*sizeof(float)*3);
            }
            // ----- liquit
            if (flags & 1)
            {
                // we have liquit -> not handled yet ... skip
                READ_OR_RETURN(&blockId, 4);
                CMP_OR_RETURN(blockId, "LIQU");
                READ_OR_RETURN(&blocksize, sizeof(int));
                fseek(rf, blocksize, SEEK_CUR);
            }


            for (unsigned int i=0, indexNo=0; indexNo<nvectors; indexNo++)
            {
                Vector3 v = Vector3(vectorarray[i+2], vectorarray[i+1], vectorarray[i+0]);
                i+=3;
                v = pModelPosition.transform(v);

                float swapy = v.y;
                v.y = v.x;
                v.x = swapy;

                tempVertexArray.append(v);
            }

            // ---- calculate triangles
            int rest = nindexes%3;
            if (rest != 0)
            {
                nindexes -= rest;
            }

            for (unsigned int i=0;i<(nindexes);)
            {
                Triangle t = Triangle(tempVertexArray[tempIndexArray[i+2]], tempVertexArray[tempIndexArray[i+1]], tempVertexArray[tempIndexArray[i+0]] );
                i+=3;
                ++trianglecount;
                if (g>= startgroup && g <= endgroup)
                {
                    gtree->insert(t);
                }
            }

            // drop of temporary use defines
            #undef READ_OR_RETURN
            #undef CMP_OR_RETURN

            if (vectorarray != 0)
            {
                delete vectorarray;
            }

            if (gtree->size() >0)
            {
                gtree->balance();
                SubModel *sm = new SubModel(gtree);
                #ifdef _ASSEMBLER_DEBUG
                if (::g_df) fprintf(::g_df,"group trianglies: %d, Tris: %d, Nodes: %d, gtree.triangles: %d\n", g, sm->getNTriangles(), sm->getNNodes(), gtree->memberTable.size());
                if (sm->getNTriangles() !=  gtree->memberTable.size())
                {
                    if (::g_df) fprintf(::g_df,"ERROR !!!! group trianglies: %d, Tris: %d, Nodes: %d, gtree.triangles: %d\n", g, sm->getNTriangles(), sm->getNNodes(), gtree->memberTable.size());
                }
                #endif
                sm->setBasePosition(pModelPosition.iPos);
                pMainTree->insert(sm);
            }
            delete gtree;
        }
        fclose(rf);
        return true;
    }