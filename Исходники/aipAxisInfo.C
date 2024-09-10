int AxisInfo::mapIndex(spViewInfo_t view, int i) {

   if(i<0 || i>2) return i;
   if(view == nullView) return i;

   double d=0.0;
   int ind=i;
   for(int j=0;j<3;j++) {
     if(fabs(view->p2m[j][i]) > d) {
	d=fabs(view->p2m[j][i]);
	ind = j;
     }
   }
   return ind;
}