Matriz<m,n> operator*(const Matriz<m,p>& a, const Matriz<p,n>& b)
{
   Matriz<m,n> ret;
   ret.setZero();

   for(int i = 0; i < m; i++){
      for(int j = 0; j < n; j++){
         for(int k = 0 ; k < p ; k++){
            ret(i,j) += a(i,k) * b(k,j);
         }
      }

   }
   return ret;
}