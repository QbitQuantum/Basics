bool Hand_filter::jumped(const tf::Vector3& p_current,const tf::Vector3& p_previous, const float threashold) const{
    if(p_current.distance(p_previous) < threashold){
        return false;
    }else{
        return true;
    }
}