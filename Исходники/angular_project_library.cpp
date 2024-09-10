void ProgAngularProjectLibrary::createGroupSamplingFiles(void)
{

    //#define DEBUGTIME
#ifdef  DEBUGTIME
    time_t start,end;
    double time_dif;
    time (&start);
#endif

    //load txt file
    mysampling.readSamplingFile(output_file_root,false);
#ifdef  DEBUGTIME

    time (&end);
    time_dif = difftime (end,start);
    start=end;
    printf ("re-read entire sampling file after %.2lf seconds\n", time_dif );
#endif

    StringVector blockList;
    getBlocksInMetaDataFile(fn_groups,blockList);
    FileName fn_temp, fn_exp;
    FileName my_output_file_root;
    MetaData SFBlock;

    fn_exp = FnexperimentalImages.removeBlockName();
    int igrp=1;
    for (StringVector::iterator it= blockList.begin();
         it!=blockList.end(); it++,igrp++)
    {
        my_output_file_root.compose(output_file_root + "_group",igrp,"");
        std::cerr<<"Writing group sampling file "<< my_output_file_root<<std::endl;

        fn_temp.compose(*it,fn_exp);
        SFBlock.read(fn_temp);
        if (SFBlock.size() > 0)//Do we really need this check?
            //I guess so since user may have supplied a particular
            //defocus classification. ROB
        {
            mysampling.fillExpDataProjectionDirectionByLR(fn_temp);//SFBlock@fn_groups
            if(compute_closer_sampling_point_bool)
            {
                //find sampling point closer to experimental point (only 0) and bool
                //and save docfile with this information
                mysampling.findClosestSamplingPoint(fn_temp,my_output_file_root);
            }

            //save saveSamplingFile
            if (compute_neighbors_bool)
            {
                mysampling.computeNeighbors(only_winner);
                mysampling.saveSamplingFile(my_output_file_root,false);
            }
        }
    }
#ifdef  DEBUGTIME
    time (&end);
    time_dif = difftime (end,start);
    start=end;
    printf ("Written all group sampling files after %.2lf seconds\n", time_dif );
#endif


}