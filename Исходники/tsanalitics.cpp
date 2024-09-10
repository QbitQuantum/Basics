int tsanalitics::getMVL(){
    QVector<int> vec;
    int max=0;
    for(int i=0;i<ts_row_data->size();i++){
        if ( abs(ts_row_data->at(i))>5 ){
            vec.push_back(i);
        }else{
            if(vec.size()>15){
                max+=ts_row_data->at(vec.last());
            }
            vec.remove(0,vec.size());
            vec.clear();
        }
    }
    return max;
}