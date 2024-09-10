int32_t TestFontClusters(void)
{
#ifdef _USE_LEO_
    int32_t          name;
    int            i,j;
    int            nClust;
    int            porog=50; // test !!!
    int            numInvalid;

    LeoFieldSetup  fs={0};
    RecRaster   rec;
    RecObject   ro={0};
    LeoPageSetup ps={0};
    ClustInfo cluInfo;
    uchar addLet,resLet;

#ifdef _SAVE_INVALID_CLU_
    FILE          *fp;
#endif

    curNumFile++;

    nClust=FONGetClustCount();
    set_alphabet(alphabet1, alpha_str);

#ifdef _SAVE_INVALID_CLU_
    fp=fopen("clust.tst","at");
    fprintf(fp,"file %d\n",curNumFile);
#endif

    LEOSetPlatform(LEOGetCPU());
    fs.nStyle = LS_PRINT;
    memcpy(fs.AlphaTable,alphabet1,256);
    LEOSetupField(&fs);

    for(i=0,numInvalid=0;i<nClust;i++)
    {
        cluInfo.let = 0;
        j=FONGetClustInfo(&cluInfo,i+1);
        if(j<=0)
            continue;

        if(cluInfo.attr & CTB_PRINT_ITALIC)
            continue;

        if(cluInfo.attr & CTB_PRINT_BOLD)
            continue;

        // now - test only russian ASCII letters
        if(cluInfo.let < 128 ||
           cluInfo.let >= 176 && cluInfo.let < 224 ||
           cluInfo.let > 240
           )
            continue;

        addLet=(cluInfo.let < 144 ? cluInfo.let +32 :
                cluInfo.let < 160 ? cluInfo.let +80 :
                cluInfo.let < 176 ? cluInfo.let -32 :
                cluInfo.let - 80
                );


        name=0;
        FONGetClusterAsBW(&name,i,porog,&rec);

        memset(&ro,0,sizeof(RecObject));
        memcpy(&ro.recData.recRaster,&rec,sizeof(RecRaster));
        ps.nIdPage=-1;
        ro.recData.lwStatus=0;
        LEOSetupPage(&ps);

        LEORecogPrintChar(&ro);

        // ничего хорошего по LEO ?
        if( ro.recResults.lnAltCnt <= 0 ||
            ro.recResults.Alt[0].Prob < 150
            )
            continue;

        for(j=0;j<ro.recResults.lnAltCnt;j++)
        {
            resLet = stdAnsiToAscii(ro.recResults.Alt[j].Code);

            if( resLet == cluInfo.let ||
                resLet == addLet )
                break;
        }

        if(j==0)
            continue;

        { char *qq;

            resLet = stdAnsiToAscii(ro.recResults.Alt[0].Code);
            if( !is_lower(resLet) )
                resLet =  to_lower(resLet);
            if( (qq=strchr(hasNearSame,cluInfo.let)) &&
                NearSame[qq-(char*)hasNearSame] == resLet
                )
                continue;
        }

        // узналось как что-то иное ?
        // если совсем не распозналось - бывает ('»' в sten91)
        if( j >= ro.recResults.lnAltCnt ||
            ro.recResults.Alt[j].Prob < 180 ||
            ro.recResults.Alt[j].Prob < 220 &&
            ro.recResults.Alt[j].Prob + 25 < ro.recResults.Alt[0].Prob
            )
        {
            FonTestInfo testInfo[MAXCHECKALT];

            // проверим
            resLet = stdAnsiToAscii(ro.recResults.Alt[0].Code);
            j=FONTestChar(&rec,resLet,testInfo,0);

            if( j <=0 || testInfo[0].prob <= 215 )
            {
                resLet=(resLet < 144 ? resLet +32 :
                        resLet < 160 ? resLet +80 :
                        resLet < 176 ? resLet -32 :
                        resLet - 80
                        );
                j=FONTestChar(&rec,resLet,testInfo,0);
            }

            if( j > 0 && testInfo[0].prob > 215 )
            {
                numInvalid++;
                FONSetClusterInvalid(i+1);
#ifdef _SAVE_INVALID_CLU_
                fprintf(fp,"    invalid %d (%c -> %c(%d))\n",i+1,cluInfo.let,
                        stdAnsiToAscii(ro.recResults.Alt[0].Code),
                        ro.recResults.Alt[0].Prob);
#endif
            }
        } // end if j

    }   // end clusters



#ifdef _SAVE_INVALID_CLU_
    fclose(fp);
#endif

    return numInvalid;
#else
    return 0;
#endif
}