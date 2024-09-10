static void etherReceive(pioStatusB *iosb, pio_ethbuf *irbb)

{
    int             i, stat;
    int             listNumber, devIOF, repTick, numDevs, maxDevices;
    int             error, errort, ident, totaldev, totalfec, tffunc;
    AddProVaxType   AddPro;
    char            mess[70];
    FORSTR messD = {70, 0, 0, mess};
    char            trtnod[7];
    DSC trtnodD  = { 6, 0, 0, trtnod};
    pioDevices      ReceiveCells[MAX_DEVS];
    int             aLen, dLen;
    char            auxAtt[5], auxDev[9];

    maxDevices = MAX_DEVS;
    error = 1;
    pioreq_analyze_extended(&iosb->trans, &irbb->head.bytecount, &maxDevices, &listNumber,
                            &devIOF, &repTick, &numDevs, ReceiveCells, &error, &ident,
                            &totaldev, &totalfec, &tffunc);
    if (error != 1) {
        GET_ETHER_ADDPROT(&AddPro);
        ADCOMP(&trtnodD, &AddPro, &errort);
        printf("caQtDM -- PIOREQ_ANALYZE error=%d list=%d numdevs=%d with TF=%d from <%.6s>\n", error, listNumber, numDevs,
               tffunc, trtnod);
        stat = getPioErrMsgStr(&error, &messD);
        mess[69] = '\0';
        printf("            : %s\n", mess);
        return;
    }

    GET_ETHER_ADDPROT(&AddPro);
    ADCOMP(&trtnodD, &AddPro, &errort);
    trtnod[6] = '\0';

    //printf("caQtDM -- PIOREQ_ANALYZE error=%d list=%d numdevs=%d with TF=%d from <%.6s>\n", error, listNumber, numDevs, tffunc, trtnod);

    /* copy data back to our cells for activ list */

    if (listNumber == MAX_LISTS - 2) {
        if (ReceiveCells[0].unit_code > 3) {
            ActivCells[0].ub.value = (float) Vax2HostF(&ReceiveCells[0].ub.value);
        } else {
            ActivCells[0].ub.int4val = ReceiveCells[0].ub.int4val;
        }
        ActivCells[0].error_code = ReceiveCells[0].error_code;
        ActivCells[0].unit_code = ReceiveCells[0].unit_code;

        /* copy data back to our cells for blockserver data */

    } else if (listNumber >= MAX_LISTS/2) {
        {
            knobData kData, kDataExt;
            int   status;
            float *xbuf, *ybuf;
            char  errorMsg[255];
            int dataSize;
            int totalVal, j;

            // number of devices is always 1 for profiles

            int ident =  ReceiveCells[0].ident;

            C_GetMutexKnobData(KnobDataPtr, ident, &kData);

            if(kData.index == -1) return;

            time_t                time_val;
            struct tm             *times;
            struct timeb          timer;

            kData.edata.connected = true;
            kData.edata.accessW = true;
            kData.edata.accessR = true;
            kData.edata.fieldtype = caFLOAT;
            strcpy(kData.edata.fec, trtnod);
            kData.edata.monitorCount++;

            ftime(&timer);
            time_val = timer.time;
            times = localtime(&time_val);

            status = BlockserverData(&ReceiveCells[0], &totalVal,  &xbuf, &ybuf,  errorMsg);

            if(status) {

                dataSize = totalVal * sizeof(float);

                // we have to fill also the secondary x or y datablock
                if(extent[ident] != -1) {
                    int l =  extent[ident];
                    C_GetMutexKnobData(KnobDataPtr, l, &kDataExt);

                    kDataExt.edata.connected = true;
                    kDataExt.edata.accessW = true;
                    kDataExt.edata.accessR = true;
                    kDataExt.edata.fieldtype = caFLOAT;
                    kDataExt.edata.monitorCount++;

                    if(dataSize != kDataExt.edata.dataSize) {
                        free(kDataExt.edata.dataB);
                        kDataExt.edata.dataB = (void*) malloc(dataSize);
                        kDataExt.edata.dataSize = dataSize;
                    }
                    kDataExt.edata.valueCount = totalVal;
                    float *ptr = (float*) kDataExt.edata.dataB;

                    if(kDataExt.specData[2] == 0) {
                        for(j=0; j < totalVal; j++) {
                            ptr[j] = xbuf[j];
                        }
                    } else {
                        for(j=0; j < totalVal; j++) {
                            ptr[j] = ybuf[j];
                        }
                    }
                }

                // fill datablock for this device

                if(dataSize != kData.edata.dataSize) {
                    free(kData.edata.dataB);
                    kData.edata.dataB = (void*) malloc(dataSize);
                    kData.edata.dataSize = dataSize;
                }
                kData.edata.valueCount = totalVal;
                float *ptr = (float*) kData.edata.dataB;
                if(kData.specData[2] == 0) {
                    for(j=0; j < totalVal; j++) {
                        ptr[j] = xbuf[j];
                    }
                } else {
                    for(j=0; j < totalVal; j++) {
                        ptr[j] = ybuf[j];
                    }
                }

                C_SetMutexKnobDataReceived(KnobDataPtr, &kData);
                if(extent[ident] != -1) C_SetMutexKnobDataReceived(KnobDataPtr, &kDataExt);
                free(xbuf);
                free(ybuf);
            }
        }

        /* copy data back to our cells for read lists */

    } else {
        knobData kData;
        char            unit[9];
        FORSTR          unitD = {8, 0, 0, unit};
        static char     level2[16][21];
        FORSTRARRAY     level2D = {21, 14, 4, 0};
        static char     image2[16][21];
        FORSTRARRAY     image2D = {21, 14, 4, 0};
        int             offset[16];
        char            devS[9], attS[5];
        DSC             devD = {8, 0, 0, devS};
        DSC             attD = {4, 0, 0, attS};
        int             dim = 16;
        int             len = 0;

        for (i = 0; i < numDevs; i++) {
            int dataSize = 0;
            int num = 0;

            if (ReceiveCells[i].error_code == -9) goto skip;   // prof cell coming from pioser taken out

            C_GetMutexKnobData(KnobDataPtr, ReceiveCells[i].ident, &kData);

            if(kData.index != -1) {

                F_CMDT_RCRD  bitmapping[MAX_RECORDS];
                F_SBNT_RCRD result [16];
                kData.edata.monitorCount++;
                kData.edata.connected = true;

                kData.edata.accessW = true;
                kData.edata.accessR = true;
                kData.edata.valueCount = 1;
                strcpy(kData.edata.fec, trtnod);

                memcpy(devS, ReceiveCells[i].name, 8);
                memcpy(attS, ReceiveCells[i].att, 4);
                memset(bitmapping, 0, sizeof(bitmapping));

                attS[4] = '\0';
                devS[8] = '\0';
                aLen = real_len(attS);
                dLen = real_len(devS);
                strcpy(auxAtt, attS);
                strcpy(auxDev, devS);
                auxAtt[aLen] = '\0';
                auxDev[dLen] = '\0';

                if( (strstr(kData.pv, auxAtt) == (char*) 0) ||
                        (strstr(kData.pv, auxDev) == (char*) 0)) {
                    //printf("unexpected device %d %s <%.8s> <%.4s>\n", kData.index, kData.pv, auxDev, auxAtt);
                    goto skip;
                }

                // in case of commands we do not have to consider an error code
                if(strncmp(attS, "C", 1) == 0) {
                    if(kData.edata.dataSize > 0) {
                        kData.edata.monitorCount--;
                        goto skip1;  // cmdnames should not change
                    }
                    num = getCmdNames(&devD, &attD, &dim, bitmapping);
                    if(num > 0) {
                        int j;
                        dataSize = 8 * sizeof(char) * num + (num) * sizeof(char);
                        char aux[9];
                        //printf("%.8s %.4s %d\n", devS, attS, num);

                        kData.edata.fieldtype = caENUM;
                        if(dataSize != kData.edata.dataSize) {
                            free(kData.edata.dataB);
                            kData.edata.dataB = (void*) malloc(dataSize);
                            kData.edata.dataSize = dataSize;
                        }

                        char *ptr = (char*) kData.edata.dataB;
                        ptr[0] = '\0';
                        strncpy(aux, bitmapping[0].bitName, 8);
                        aux[8] = '\0';
                        len = Min(8, real_len(aux));
                        aux[len] = '\0';
                        strcpy(ptr, aux);
                        for (j = 1; j < num; j++) {
                            strncpy(aux, bitmapping[j].bitName, 8);
                            aux[8] = '\0';
                            len = Min(8, real_len(aux));
                            aux[len] = '\0';
                            sprintf(ptr, "%s;%s", ptr, aux);
                        }
                        kData.edata.valueCount=num;
                        // in case of hipa, commands should have no value
                        kData.edata.ivalue = num+1;
                    }

                    // everything except command attribute

                } else {

                    if (ReceiveCells[i].error_code == 1) {

                        kData.edata.severity = 0;

                        // floats
                        if (ReceiveCells[i].unit_code > 3) {

                            float value = (float) Vax2HostF(&ReceiveCells[i].ub.value);

                            // new value ?
                            //if((fabs(kData.edata.rvalue - value) <= 1.e-7)  && (kData.edata.monitorCount > 1)) {
                            //    kData.edata.monitorCount--;
                            //    goto skip1;
                            //}
                            kData.edata.rvalue = (float) Vax2HostF(&ReceiveCells[i].ub.value);
                            kData.edata.fieldtype = caFLOAT;
                            kData.edata.precision = 3;

                            // integers (bitfields)
                        } else {
                            int status;
                            char level2Data[21];
                            level2Data[0] = '\0';

                            int value = ReceiveCells[i].ub.int4val;
                            kData.edata.fieldtype = caINT;  // default type

                            // new value ?
                            //if(strstr(kData.pv, "VHD0") != (char*) 0) printf("pv=<%s> old=%x new=%x mC=%d dC=%d\n",kData.pv, kData.edata.ivalue, value , kData.edata.monitorCount, kData.edata.displayCount);

                            //if(kData.edata.ivalue == value && kData.edata.monitorCount > 1 && kData.edata.displayCount != 0) {
                            //    kData.edata.monitorCount--;
                                //if(strstr(kData.pv, "VHD0") != (char*) 0) printf("skipped\n");
                            //    goto skip1;
                            //}

                            //if(strstr(kData.pv, "VHD0") != (char*) 0)printf("not skipped\n");

                            kData.edata.ivalue = ReceiveCells[i].ub.int4val;
                            kData.edata.rvalue = (float) ReceiveCells[i].ub.int4val;

                            level2D.strPtr = (char *) level2;
                            image2D.strPtr = (char *) image2;

                            // in case of ca_choice and cabitnames get also bitnames
                            if((strstr(kData.clasName, "choice") != (char *) 0) ||
                                    (strstr(kData.clasName, "bitnames") != (char *) 0)) {
                                if(kData.edata.dataSize > 0) {
                                     if(kData.edata.displayCount > 0)  goto skip1;  // bitnames should not change, but value yes
                                }
                                memset(result, 0, sizeof(result));
                                status = getBitNames(&devD, &attD, result);
                                if(status == 1) {
                                    int j;
                                    num = 0;
                                    for(j=0; j < 16; j++) {
                                        strncpy(level2[j], result[j].bitCmt, 20);
                                        level2[j][20] = '\0';
                                        num++;
                                    }
                                    dataSize = 21 * sizeof(char) * num + (num) * sizeof(char);
                                    // in case of hipa, bitnames should have no value
                                    kData.edata.ivalue = num+1;
                                }

                            } else if((strstr(kData.clasName, "lineedit") != (char *) 0) || (strstr(kData.clasName, "image") != (char *) 0)) {
                                // get digital level 2
                                int j;
                                num = getDigLvl2ext(&devD, &attD, &ReceiveCells[i].ub.int4val, &dim,  &level2D, &image2D, offset);
                                dataSize = 21 * sizeof(char) * num + (num) * sizeof(char);
                                for(j = 0; j < num; j++) {
                                    level2[j][20] = '\0';
                                    // if we have an image, compute the correct frame and keep also the string
                                    if(strlen(kData.edata.aux) > 0) {
                                        char levData[21], aux[21];
                                        strcpy(levData, level2[j]);
                                        strcpy(aux, kData.edata.aux); strcat(aux, "_");
                                        if(IsInside(strUpr(levData), aux)) {
                                            kData.edata.rvalue = offset[j];
                                            strcpy(level2Data, level2[j]);
                                            dataSize = 21 * sizeof(char);
                                        }
                                    }
                                }
                            }

                            if(num > 0) {
                                if((strstr(kData.clasName, "choice") != (char *) 0) || (strstr(kData.clasName, "bitnames") != (char *) 0)) {
                                    kData.edata.fieldtype = caENUM;
                                } else {
                                    kData.edata.fieldtype = caSTRING;
                                }
                                if(dataSize != kData.edata.dataSize) {
                                    free(kData.edata.dataB);
                                    kData.edata.dataB = (void*) malloc(dataSize);
                                    kData.edata.dataSize = dataSize;
                                }

                                char *ptr = (char*) kData.edata.dataB;

                                if(strlen(kData.edata.aux) > 0) {
                                    ptr[0] = '\0';
                                    strcpy(ptr, level2Data);
                                    kData.edata.valueCount = 1;
                                    kData.edata.enumCount=0;

                                } else {
                                    int j;
                                    char levData[21];
                                    ptr[0] = '\0';
                                    strcpy(ptr, level2[0]);
                                    for (j = 1; j < num; j++) {
                                        strncpy(levData, level2[j], 20);
                                        levData[20] = '\0';
                                        len = Min(20, real_len(levData));
                                        levData[len] = '\0';
                                        sprintf(ptr, "%s;%s", ptr, levData);
                                    }
                                    kData.edata.valueCount=num;
                                    kData.edata.enumCount=num;
                                }
                            }

                        }
                        fillUnit(&ReceiveCells[i].unit_code, &unitD);
                        unit[8] = '\0';
                        unit[real_len(unit)] = '\0';
                        strcpy(kData.edata.units, unit);
                    } else {
                        kData.edata.severity = ReceiveCells[i].error_code;
                        if (ReceiveCells[i].unit_code > 3) {
                            kData.edata.rvalue = 0.0;
                            kData.edata.fieldtype = caFLOAT;
                            kData.edata.precision = 3;
                        }
                    }
                }
skip1:;
                C_SetMutexKnobDataReceived(KnobDataPtr, &kData);
skip:;
            }
        }
    }
}