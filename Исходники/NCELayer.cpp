 void forwardBias() {
   if (!biases_) {
     sampleOut_.value->zeroMem();
   } else {
     real* bias = biases_->getW()->getData();
     real* sampleOut = sampleOut_.value->getData();
     for (size_t i = 0; i < samples_.size(); ++i) {
       sampleOut[i] = bias[samples_[i].labelId];
     }
   }
 }