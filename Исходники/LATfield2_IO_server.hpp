void IOserver::initialize(int proc_size0,int proc_size1, int IOserver_size, int IO_node_size)
{
    int rang[3];
    int totalMPIsize;
    int itemp;
    
    MPI_Group groupTemp1,groupTemp2;
   
    MPI_Comm_group(MPI_COMM_WORLD,&world_group_);
    MPI_Group_size(world_group_,&totalMPIsize);
    
    
    if((proc_size0*proc_size1) % IOserver_size!=0 || IOserver_size % IO_node_size!=0)
    {
        //cout<<"IOserver wrong number of process"<<endl;
        exit(-44);
    }
    
    
    rang[0]=0;
    rang[1]=proc_size0*proc_size1-1;
    rang[2]=1;
    MPI_Group_range_incl(world_group_,1,&rang,&computeGroup_);
    MPI_Comm_create(MPI_COMM_WORLD,computeGroup_ , &computeComm_);    
    
    MPI_Group_rank(computeGroup_, &computeRank_);
    
    
    rang[0]=proc_size0*proc_size1;
    rang[1]=proc_size0*proc_size1 + IOserver_size - 1 ;
    rang[2]=1;
    MPI_Group_range_incl(world_group_,1,&rang,&IO_Group_);
    MPI_Comm_create(MPI_COMM_WORLD,IO_Group_ , &IO_Comm_);
    
    MPI_Group_rank(IO_Group_, &IO_Rank_);
    
    
    
    rang[0]=proc_size0*proc_size1;
    rang[1]=0;
    MPI_Group_incl(world_group_,2,&rang[0],&syncLineGroup_);
    MPI_Comm_create(MPI_COMM_WORLD,syncLineGroup_ , &syncLineComm_);
    
    MPI_Group_rank(syncLineGroup_, &syncLineRank_);
    
    
    IO_ClientSize_=proc_size0*proc_size1/IOserver_size;
    IO_NodeSize_=IO_node_size;
    
    if(computeRank_!=MPI_UNDEFINED)itemp = floor((float)computeRank_/(float)IO_ClientSize_) * IO_ClientSize_;
    else itemp = IO_Rank_ * IO_ClientSize_;
    //if(computeRank_!=MPI_UNDEFINED)cout<< "compute core: "<< computeRank_ <<" , "<<  itemp<<endl;
    //if(IO_Rank_!=MPI_UNDEFINED)cout<< "IO core: "<< IO_Rank_ <<" , "<<  itemp<<endl;
    
    rang[0] = itemp;
    rang[1] = itemp + IO_ClientSize_ -1;
    rang[2]=1;
    MPI_Group_range_incl(world_group_,1,&rang,&groupTemp2);
    
    if(computeRank_!=MPI_UNDEFINED)itemp = proc_size0*proc_size1 + floor((float)computeRank_/(float)IO_ClientSize_);
    else itemp = proc_size0*proc_size1 + IO_Rank_;
    //if(computeRank_!=MPI_UNDEFINED)cout<< "compute core: "<< computeRank_ <<" , "<<  itemp<<endl;
    //if(IO_Rank_!=MPI_UNDEFINED)cout<< "IO core: "<< IO_Rank_ <<" , "<<  itemp<<endl;

    MPI_Group_incl(world_group_,1,&itemp,&groupTemp1);
    
    MPI_Group_union(groupTemp1,groupTemp2,&masterClientGroup_);
    MPI_Comm_create(MPI_COMM_WORLD,masterClientGroup_ , &masterClientComm_);
    
    
    //if(computeRank_!=MPI_UNDEFINED)cout<< "compute core: "<< computeRank_ <<" , "<<  itemp<<endl;
    //if(IO_Rank_!=MPI_UNDEFINED)cout<< "IO core: "<< IO_Rank_ <<" , "<<  itemp<<endl;
    
    
    
    if(IO_Rank_!=MPI_UNDEFINED)
    {
                
        itemp= floor((float)IO_Rank_/ (float)IO_node_size) * IO_node_size;
        
        rang[0] = itemp;
        rang[1] = itemp + IO_node_size -1;
        rang[2]=1;
        MPI_Group_range_incl(IO_Group_,1,&rang,&IO_NodeGroup_);
        MPI_Comm_create(IO_Comm_,IO_NodeGroup_ , &IO_NodeComm_);
        MPI_Group_rank(IO_NodeGroup_, &IO_NodeRank_);
        
        files = new file_struct[MAX_FILE_NUMBER];
        dataBuffer = (char*)malloc(IO_BUFFERS_TOTAL_SIZE);
        IO_Node_=floor((float)IO_Rank_/ (float)IO_node_size) ;
        
    }
    
    
    
    sendRequest = MPI_REQUEST_NULL;
    
}