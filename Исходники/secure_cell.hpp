 const data_t& decrypt(const data_t& data, const data_t& context){
   return decrypt(data.begin(), data.end(), context.begin(), context.end());
 }