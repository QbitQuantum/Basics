void Load(  char ins_name[] ) {

// 	int nurseSkill[NURSE_NUM] = {0};
//
// 	int nursesContraMap[NURSE_NUM];
//
// 	int nurseDayoff[NURSE_NUM][DAY_NUM];
//
// 	char nurseShiftoff[NURSE_NUM][DAY_NUM][10] = {0}; // weight is always 1
// 	int nurseShiftoffNum[NURSE_NUM][DAY_NUM] = {0};
//

    memset(&nurseSkill, 0, sizeof(nurseSkill));
    memset(&nursesContraMap, 0, sizeof(nursesContraMap));
    memset(&nurseDayoff, 0, sizeof(nurseDayoff));
    memset(&nurseShiftoff, 0, sizeof(nurseShiftoff));
    memset(&nurseShiftoffNum, 0, sizeof(nurseShiftoffNum));


    memset(&instAttri, 0, sizeof(instAttri));
    memset(&cover_h, 0, sizeof(cover_h));
    memset(&unPatArray, 0, sizeof(unPatArray));



    FILE *instanceLoadChk_fout = fopen("instanceLoadChk.txt", "w");

    errno_t err;

    err =  fopen_s(&instance_fin,ins_name, "r");



    // ===== load loop =====
    while(   fscanf_s(instance_fin,"%s",tmp, STRMAX) != EOF   ) {


        // ========================= read name and start time =========================
        if(  !strcmp("SCHEDULING_PERIOD;", tmp ) ) {
            fscanf_s(instance_fin,"%s",tmp, STRMAX); // the '/////' line

            fscanf_s(instance_fin,"%s,",instAttri.instanceName, STRMAX);
            fscanf_s(instance_fin,"%s,",instAttri.instanceStartTime, STRMAX);
            fscanf_s(instance_fin,"%s;",tmp, STRMAX);



            fprintf(instanceLoadChk_fout,"instance name is %s\n", instAttri.instanceName);
            fprintf(instanceLoadChk_fout,"instance start time is %s\n\n", instAttri.instanceStartTime);


            if( !strcmp(instAttri.instanceStartTime,"2010-01-01,") ) {
                startTimeOffset = 5;
            }
            else if( !strcmp(instAttri.instanceStartTime,"2010-06-01,") ) {
                startTimeOffset = 2;
            }
        }

        // ========================= read skills =========================
        if(  !strcmp("SKILLS", tmp) ) {
            fscanf_s(instance_fin,"%s",tmp, STRMAX); // read '=' symble
            fscanf_s(instance_fin,"%s",tmp, STRMAX);// skill number
            instAttri.skillNum = atoi(tmp);
            fprintf(instanceLoadChk_fout,"number of skill kind is %d\n\n", instAttri.skillNum);
        }

        // ========================= read shift types =========================
        if(  !strcmp("SHIFT_TYPES", tmp) ) {
            fscanf_s(instance_fin,"%s",tmp, STRMAX);// read '=' symble
            fscanf_s(instance_fin,"%s",tmp, STRMAX);// skill number
            instAttri.shiftTypeNum = atoi(tmp);
            fprintf(instanceLoadChk_fout,"number of shift type is %d\n\n", instAttri.shiftTypeNum);
        }



        // ========================= contract description =========================
        // read the soft cons
        // read contracts arrays
        // if the weekend definition being the line
        // before it, there are 10 entries, except the first one being the hardconstraints
        // there are 9 entries which are :
        // Max & Min working day			2
        // Max & Min consec working day		2
        // Max & Min consec free day		2
        // Max & Min consec working wkd		2
        // Max working wkd in four weeks	1
        // after the wkd definition there are 5 entries in .txt file but 4 entries in .xml files.
        // since the extra one (the fourth one)always keep 0, so it could be neglected.
        // It might be the two free days before the night shift,ref to nrpdesci page 19
        // Thus there left 4 entries, which are
        // complete weekend					1
        // identical shift type in complete wkd	1
        // No Night shift before free wkd	1
        // alternative skill				1
        // ==================================================
        if( !strcmp("CONTRACTS", tmp) ) {

            fscanf_s(instance_fin,"%s",tmp, STRMAX); // read the '='
            fscanf_s(instance_fin,"%s",tmp, STRMAX); // read the number of contra
            instAttri.contractNum = atoi(tmp);
            fprintf(instanceLoadChk_fout,"contract num is %d\n\n", instAttri.contractNum);
            fscanf_s(instance_fin,"%s",tmp, STRMAX); // read line ///


            // for each contra
            for(int i = 0; i < instAttri.contractNum; i++ ) {

                fscanf_s(instance_fin,"%s",tmp, STRMAX);
                int id = atoi(tmp);
                fprintf(instanceLoadChk_fout,"contrac id is %d ///////////\n", id);


                // the contract's name
                fscanf_s(instance_fin,"%s",tmp, STRMAX);
                fprintf(instanceLoadChk_fout,"contrac description is %s\n",tmp);


                // the first (1|1) is the hard constraints, always on
                fscanf_s(instance_fin,"%s",tmp, STRMAX);

                // max & min work day
                fscanf_s(instance_fin," (%d|%d|%d),",&contractArray[id].maxWorkDayOn,&contractArray[id].maxWorkDayW,
                         &contractArray[id].maxWorkDay);
                fprintf(instanceLoadChk_fout,"max min wk day   %d %d %d \n",contractArray[id].maxWorkDayOn,
                        contractArray[id].maxWorkDayW,contractArray[id].maxWorkDay);

                fscanf_s(instance_fin," (%d|%d|%d),",&contractArray[id].minWorkDayOn,&contractArray[id].minWorkDayW,
                         &contractArray[id].minWorkDay);
                fprintf(instanceLoadChk_fout,"max min wk day   %d %d %d \n",contractArray[id].minWorkDayOn,
                        contractArray[id].minWorkDayW,contractArray[id].minWorkDay);



                // max & min ConWorkDay
                fscanf_s(instance_fin," (%d|%d|%d),",&contractArray[id].maxConWorkDayOn,&contractArray[id].maxConWorkDayW,
                         &contractArray[id].maxConWorkDay);
// 				fprintf(instanceLoadChk_fout,"max min wk day   %d %d %d \n",contractArray[id].maxConWorkDayOn,
// 					contractArray[id].maxConWorkDayW,contractArray[id].maxConWorkDay);
                fscanf_s(instance_fin," (%d|%d|%d),",&contractArray[id].minConWorkDayOn,&contractArray[id].minConWorkDayW,
                         &contractArray[id].minConWorkDay);

                // max & min ConFree
                fscanf_s(instance_fin," (%d|%d|%d),",&contractArray[id].maxConFreeOn,&contractArray[id].maxConFreeW,
                         &contractArray[id].maxConFree);
                fscanf_s(instance_fin," (%d|%d|%d),",&contractArray[id].minConFreeOn,&contractArray[id].minConFreeW,
                         &contractArray[id].minConFree);

                // max & min con work weekend
                fscanf(instance_fin," (%d|%d|%d),",&contractArray[id].maxConWorkWeekendOn,&contractArray[id].maxConWorkWeekendW,
                       &contractArray[id].maxConWorkWeekend);
                fscanf(instance_fin," (%d|%d|%d),",&contractArray[id].minConWorkWeekendOn,&contractArray[id].minConWorkWeekendW,
                       &contractArray[id].minConWorkWeekend);

                // max working weekend
                fscanf(instance_fin," (%d|%d|%d),",&contractArray[id].maxWorkingWeekendOn,&contractArray[id].maxWorkingWeekendW,
                       &contractArray[id].maxWorkingWeekend);
                fprintf(instanceLoadChk_fout,"maxWorkingWeekend  %d %d %d \n",contractArray[id].maxWorkingWeekendOn,
                        contractArray[id].maxWorkingWeekendW,contractArray[id].maxWorkingWeekend);


                // wkd definition
                fscanf_s(instance_fin,"%s",tmp, STRMAX);
                //fprintf(instanceLoadChk_fout,"weekend is default \n");
                if( !strcmp("SaturdaySunday,", tmp) ) contractArray[id].wkdDayNum = 2;
                else if( !strcmp("FridaySaturdaySunday,", tmp) ) contractArray[id].wkdDayNum = 3;
                fprintf(instanceLoadChk_fout, "wkd num is %d \n", contractArray[id].wkdDayNum);


                // complete wkd
                fscanf(instance_fin," (%d|%d),",  &contractArray[id].completeWeekendOn,&contractArray[id].completeWeekendW);
                fprintf(instanceLoadChk_fout,"complete weekend     %d %d \n",contractArray[id].completeWeekendOn,
                        contractArray[id].completeWeekendW);


                // identical shift in wkd
                fscanf(instance_fin," (%d|%d),",  &contractArray[id].idenShiftInWeekendOn,&contractArray[id].idenShiftInWeekendW);
                fprintf(instanceLoadChk_fout,"identical     %d %d \n",contractArray[id].idenShiftInWeekendOn,
                        contractArray[id].idenShiftInWeekendW);

                //no night shift
                fscanf(instance_fin," (%d|%d),",  &contractArray[id].noNSBfFWeekendOn,&contractArray[id].noNSBfFWeekendW);
                fprintf(instanceLoadChk_fout,"no night is    %d %d \n",contractArray[id].noNSBfFWeekendOn,
                        contractArray[id].noNSBfFWeekendW);


                // not no use, maybe it is the no 2free days after a night shift
                // however, the cons is always 0|0 in every instance, so do not need
                // to load
                fscanf_s(instance_fin,"%s",tmp, STRMAX);


                // alternative
                fscanf(instance_fin," (%d|%d),",  &contractArray[id].alternativeOn,&contractArray[id].alternativeW);
                fprintf(instanceLoadChk_fout,"alter is    %d %d \n",contractArray[id].alternativeOn,
                        contractArray[id].alternativeW);

                // read contracts' pattern
                // e.g. ... 3, 0 1 2;
                fscanf_s(instance_fin,"%s",tmp, STRMAX);
                int patternNum = atoi(tmp);
                contractArray[id].unWantPatTotal = patternNum;
                fprintf(instanceLoadChk_fout,"unwanted pattern num is %d\n",contractArray[id].unWantPatTotal);

                // each pattern, read the id
                for(int i = 0; i<patternNum; i++) {
                    fscanf_s(instance_fin,"%s",tmp, STRMAX);
                    contractArray[id].unWantPat[i] = atoi(tmp);
                    fprintf(instanceLoadChk_fout,"unwant pattern is %d\n", contractArray[id].unWantPat[i]);
                }
                fprintf(instanceLoadChk_fout,"\n");
            }
        }


        // ========================= read patterns =========================
        //2, 1, 3 (None|Friday) (Any|Saturday) (Any|Sunday);
        //1, 1, 3 (D|Any) (E|Any) (D|Any);
        //0, 1, 2 (L|Any) (D|Any);

        if(  !strcmp("PATTERNS", tmp) ) {
            fprintf(instanceLoadChk_fout,"\n////////////////////   PATTERN    ///////////////////// \n");

            fscanf_s(instance_fin,"%s",tmp, STRMAX); // the '=' symbol
            fscanf_s(instance_fin,"%s",tmp, STRMAX); // the pattern number
            int patternTotal = atoi(tmp);
            fprintf(instanceLoadChk_fout,"pattern total number is %d\n", patternTotal);
            fscanf_s(instance_fin,"%s",tmp, STRMAX); // read the ////////////


            // for each pattern, fill the unPatArray to record
            for(int j = 0; j < patternTotal; j++) {

                // pattern ID
                fscanf_s(instance_fin,"%s",tmp, STRMAX);
                int patternId = atoi(tmp);
                unPatArray[patternId].patIdx = patternId;
                fprintf(instanceLoadChk_fout,"pattern id is %d\n", patternId);

                // pattern weight, always 1, leave it alone
                fscanf_s(instance_fin,"%s",tmp, STRMAX);
                unPatArray[patternId].patWeight = atoi(tmp);


                // total number of shifts in a sequence
                fscanf_s(instance_fin,"%s",tmp, STRMAX);
                int shiftTotal = atoi(tmp);
                fprintf(instanceLoadChk_fout,"shift total is %d\n", shiftTotal);
                unPatArray[patternId].shiftTotal = shiftTotal;


                // loop the shift sequence
                // e.g. 2, 1, 3 (None|Friday) (Any|Saturday) (Any|Sunday);
                for(int i = 0; i<shiftTotal; i++) {
                    fscanf_s(instance_fin,"%s",tmp, STRMAX);

                    // the pattern related to wkd
                    if( strlen(tmp) > 10 ) {
                        unPatArray[patternId].patSeq[0] = 'F';
                        unPatArray[patternId].patSeq[1] = 'A';
                        unPatArray[patternId].patSeq[2] = 'A';
                    }

                    else {
                        if(tmp[1] == 'D' && tmp[2] == 'H') {	// for DH
                            unPatArray[patternId].patSeq[i] = tmp[2];
                        }
                        else
                            unPatArray[patternId].patSeq[i] = tmp[1];
                    }

                }

            }



            // pattern struct show
            //for(int i = 0; i< patternTotal ;i++){
            //	printf("idx is %d, weight is %d, shiftNum is %d", unPatArray[i].patIdx,unPatArray[i].patWeight,unPatArray[i].shiftTotal);
            //	for(int j = 0; j < unPatArray[i].shiftTotal; j++ ){
            //		printf("%c ", unPatArray[i].patSeq[j]);
            //	}
            //	printf("\n");
            //}
        } // read pattern




        // ========================= read employees =========================
        if(  !strcmp("EMPLOYEES", tmp) ) {
            fprintf(instanceLoadChk_fout,"\n////////////////////   EMPLOYEE READ    ///////////////////// \n");

            fscanf_s(instance_fin,"%s",tmp, STRMAX);
            nurseTotal = atoi(tmp);
            fprintf(instanceLoadChk_fout,"nurse number is %d\n", nurseTotal);

            fscanf_s(instance_fin,"%s",tmp, STRMAX); // read the line ///

            for(int i = 0; i<nurseTotal; i++) {
                int id;

                fscanf_s(instance_fin,"%s",tmp, STRMAX); // nurse id
                id = atoi(tmp);
                fscanf_s(instance_fin,"%s",tmp, STRMAX); // another id, no use

                fscanf_s(instance_fin,"%s",tmp, STRMAX); // contra id
                nursesContraMap[id] = atoi(tmp);
                fprintf(instanceLoadChk_fout,"nurse %d's contra id is %d ",id, nursesContraMap[id] );

                // use another array to hold the skill level of a nurse
                fscanf_s(instance_fin,"%s",tmp, STRMAX); // skill level
                nurseSkill[id] = atoi(tmp);
                fprintf(instanceLoadChk_fout,"nurse %d's skill level is %d \n",id, nurseSkill[id] );

                // 'nurse' of 'nurse and head nurse',
                // don't need to read, above information is enough
                fscanf_s(instance_fin,"%s",tmp, STRMAX);
                if(nurseSkill[id]>1)fscanf_s(instance_fin,"%s",tmp, STRMAX);

            }
        }


        // ========================= read hard cover  =========================
        if(  !strcmp("DAY_OF_WEEK_COVER", tmp) ) {
            //if(  compare("DAY_OF_WEEK_COVER", tmp, strlen(tmp)) ){
            fprintf(instanceLoadChk_fout,"\n////////////////////   HARD COVER CONS    ///////////////////// \n");

            fscanf_s(instance_fin,"%s",tmp, STRMAX); // read the '='
            fscanf_s(instance_fin,"%s",tmp, STRMAX); // read the number

            int weekcovernum = (tmp[0] - 48) * 10 + tmp[1] - 48; // the week cover total number
            fprintf(instanceLoadChk_fout," the weekcovernum is %d\n", weekcovernum);

            fscanf_s(instance_fin,"%s",tmp, STRMAX); // read the //line


            for(int i = 0; i<weekcovernum; i++) {

                fscanf_s(instance_fin,"%s",tmp, STRMAX);// read the week day name

                // there is a mapping between seven day name and the indice of cover_h
                // 0 is Sunday
                if( !strcmp("Monday,", tmp) )fillCoverMap(1);
                else if( !strcmp("Tuesday,", tmp) )fillCoverMap(2);
                else if( !strcmp("Wednesday,", tmp) )fillCoverMap(3);
                else if( !strcmp("Thursday,", tmp) )fillCoverMap(4);
                else if( !strcmp("Friday,", tmp) )fillCoverMap(5);
                else if( !strcmp("Saturday,", tmp) )fillCoverMap(6);
                else if( !strcmp("Sunday,", tmp) )fillCoverMap(0);
            }

            // check the cover_h
            for(int j = 0; j<7; j++)
                for(int i = 0; i<5; i++)
                    fprintf(instanceLoadChk_fout,"the day cover  is %d \n", cover_h[j][i]);
        }



        // ========================= load day off =========================
        if(  !strcmp("DAY_OFF_REQUESTS", tmp) ) {
            fprintf(instanceLoadChk_fout,"\n////////////////////   DAT OFF REQUESTS    ///////////////////// \n");

            fscanf_s(instance_fin,"%s",tmp, STRMAX); // read the '='
            fscanf_s(instance_fin,"%s",tmp, STRMAX); // read the number

            int dayoffnum = atoi(tmp);
            //printf("day off number is %d", dayoffnum);

            fscanf_s(instance_fin,"%s",tmp, STRMAX); // read the ////

            for(int i = 0; i<dayoffnum; i++) {

                fscanf_s(instance_fin,"%s",tmp, STRMAX); // read the nurse id
                int nurseId = atoi(tmp);

                fscanf_s(instance_fin,"%s",tmp, STRMAX); // read the day name
                int day = (tmp[8]-48)*10 + tmp[9] - 48;

                fscanf_s(instance_fin,"%s",tmp, STRMAX); // read the weight
                nurseDayoff[nurseId][day-1] = atoi(tmp) ; // the dayIdx in array starts with '0'
                fprintf(instanceLoadChk_fout,"nurse % d in day %d the off is  %d \n", nurseId, day, nurseDayoff[nurseId][day-1] );
                //puts(tmp);
            }
// 			for(int i = 0; i<nurseTotal ; i++){
// 				for(int j = 0; j<DAY_NUM; j++){
// 					fprintf(instanceLoadChk_fout,"%d ",nurseDayoff[i][j]);
// 				}
// 				fprintf(instanceLoadChk_fout,"\n");
//
// 			}
        }


        // ========================= load the shift off =========================
        if(  !strcmp("SHIFT_OFF_REQUESTS", tmp) ) {
            fprintf(instanceLoadChk_fout,"\n////////////////////   SHIFT OFF REQUESTS    ///////////////////// \n");

            fscanf_s(instance_fin,"%s",tmp, STRMAX); // read the '='
            fscanf_s(instance_fin,"%s",tmp, STRMAX); // read the number

            int shiftoffnum = atoi(tmp);
            //printf("shift off number is %d", shiftoffnum);
            fprintf(instanceLoadChk_fout,"shift off num is %d\n", shiftoffnum);

            fscanf_s(instance_fin,"%s",tmp, STRMAX); // read the ////

            for(int i = 0; i<shiftoffnum; i++) {
                fscanf_s(instance_fin,"%s",tmp, STRMAX); // read the nurse id
                int nurseId = atoi(tmp);

                fscanf_s(instance_fin,"%s",tmp, STRMAX); // read the day name
                int day = (tmp[8]-48)*10 + tmp[9] - 48;

                fscanf_s(instance_fin,"%s",tmp, STRMAX); // read the shift type
                //fprintf(instanceLoadChk_fout," len is %d ", strlen(tmp));

                // for 'HD' shift
                if(strlen(tmp) == 3)
                    tmp[0] = 'H';

                // multiple shift off
                nurseShiftoff[nurseId][day-1][  nurseShiftoffNum[nurseId][day-1] ] = tmp[0];
                nurseShiftoffNum[nurseId][day-1]++;


                fscanf_s(instance_fin,"%s",tmp, STRMAX); // read the weight, no use

// 				fprintf(instanceLoadChk_fout,"nurse % d in day %d the shift is %c off weight is 1 \n",
// 					nurseId, day-1, nurseShiftoff[nurseId][day-1]);
            }

            // check above
// 			 			for(int i = 0; i<nurseTotal ; i++){
// 			 				for(int j = 0; j<DAY_NUM; j++){
// 			 					if(!nurseShiftoffNum[i][j]){
// 									fprintf(instanceLoadChk_fout,"-");
// 			 					}
// 								for(int k = 0; k < nurseShiftoffNum[i][j]; k++){
// 									fprintf(instanceLoadChk_fout,"%c",nurseShiftoff[i][j][k]);
// 			 					}
// 			 				}
// 			 				fprintf(instanceLoadChk_fout,"\n");
//
// 			 			}
        }

    }

    fclose(instanceLoadChk_fout);
    fclose(instance_fin);
    //fclose(err);


}