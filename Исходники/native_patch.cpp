int main(int argc, const char * argv[]){
    if (argc!=4) {
        std::cout<<"patch command parameter:\n oldFileName diffFileName outNewFileName\n";
        return 0;
    }
    const char* oldFileName=argv[1];
    const char* diffFileName=argv[2];
    const char* outNewFileName=argv[3];
    std::cout<<"old :\"" <<oldFileName<< "\"\ndiff:\""<<diffFileName<<"\"\nout :\""<<outNewFileName<<"\"\n";
    clock_t time0=clock();
    {
        std::vector<TByte> diffData; readFile(diffData,diffFileName);
        const TUInt diffFileDataSize=(TUInt)diffData.size();
        TUInt kNewDataSizeSavedSize=-1;
        const hpatch_StreamPos_t _newFileDataSize=readSavedSize(diffData,&kNewDataSizeSavedSize);
        const TUInt newDataSize=(TUInt)_newFileDataSize;
        if (newDataSize!=_newFileDataSize) exit(1);

        std::vector<TByte> oldData; readFile(oldData,oldFileName);
        const TUInt oldDataSize=(TUInt)oldData.size();

        std::vector<TByte> newData;
        newData.resize(newDataSize);
        TByte* newData_begin=0; if (!newData.empty()) newData_begin=&newData[0];
        const TByte* oldData_begin=0; if (!oldData.empty()) oldData_begin=&oldData[0];
        clock_t time1=clock();
        if (!patch(newData_begin,newData_begin+newDataSize,oldData_begin,oldData_begin+oldDataSize,
                   &diffData[0]+kNewDataSizeSavedSize, &diffData[0]+diffFileDataSize)){
            std::cout<<"  patch run error!!!\n";
            exit(3);
        }
        clock_t time2=clock();
        writeFile(newData,outNewFileName);
        std::cout<<"  patch ok!\n";
        std::cout<<"oldDataSize : "<<oldDataSize<<"\ndiffDataSize: "<<diffData.size()<<"\nnewDataSize : "<<newDataSize<<"\n";
        std::cout<<"\npatch   time:"<<(time2-time1)*(1000.0/CLOCKS_PER_SEC)<<" ms\n";
    }
    clock_t time3=clock();
    std::cout<<"all run time:"<<(time3-time0)*(1000.0/CLOCKS_PER_SEC)<<" ms\n";
    return 0;
}