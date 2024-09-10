int RMQ(int i,int j)
{
 int m,max,s;
 m=int(log((double)(j-i+1))/log(2.0));
 max=f[i][m]>f[j-p[m]+1][m]?f[i][m]:f[j-p[m]+1][m];
 if(h[i+p[m]-1]==h[i+p[m]])
 {
   s=Bsearch(i+p[m],j,h[i+p[m]])-(i+p[m])+1;
   max=max>s+right[i][m]?max:s+right[i][m];
 }
 if(h[j-p[m]]==h[j-p[m]+1])
 {
   s=j-p[m]-Msearch(i,j-p[m],h[j-p[m]])+1;
   max=max>s+left[j-p[m]+1][m]?max:s+left[j-p[m]+1][m];
 }
 return max;
}