 void runBins(){
     for(std::size_t i=0;i<nums_.size();++i){
         bin_->operator ()(nums_[i], ws_[i]);
     }
 }