void C_vector_any::_Reserve(dword s){

   s = Max(s, Max(res_size, used_size));
   if(res_size!=s){
      res_size = s;
      byte *new_a = new(true) byte[res_size*elem_size];
      MemCpy(new_a, array, used_size*elem_size);
      delete[] array;
      array = new_a;
   }
}