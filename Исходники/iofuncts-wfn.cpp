/* ********************************************************************************************* */
void processPrimitivesWFN(ifstream &ifil,const int npr,int* &pricen,int* &primty,solreal* &prexp)
{
   alloc1DIntArray("pricen",npr,pricen);
   alloc1DIntArray("primty",npr,primty);
   alloc1DRealArray("prexp",npr,prexp);
   int count=0;
   int pos;
   /* Getting the primitive centers */
   pos=ifil.tellg();
   ifil.seekg(pos+20);
   for (int i=0; i<npr; i++) {
      ifil >> pricen[i];
      pricen[i]--;
      count++;
      if (count==20) {
         pos=ifil.tellg();
         ifil.seekg(pos+20);
         count=0;
      }
      //cout << pricen[i] << " ";
   }
   if ((npr%20)==0) {
      pos=ifil.tellg();
      ifil.seekg(pos-20);
   }
   /* Getting the primitive types */
   pos=ifil.tellg();
   ifil.seekg(pos+20);
   count=0;
   for (int i=0; i<npr; i++) {
      ifil >> primty[i];
      primty[i]--;
      count++;
      if (count==20) {
         pos=ifil.tellg();
         ifil.seekg(pos+20);
         count=0;
      }
      //cout << primty[i] << " ";
   }
   if ((npr%20)==0) {
      pos=ifil.tellg();
      ifil.seekg(pos-20);
   }
   /* Getting the primitive exponents */
   string line;
   int nolines;
   nolines=floor(npr/5);
   if ((npr%5)>0) {nolines++;}
   count=0;
   for (int i=0; i<nolines; i++) {
      pos=ifil.tellg();
      getline(ifil,line); 
      if (line.length()==0) {getline(ifil,line); pos++;}
      line.erase(0,10);
      for (int j=0; j<5; j++) {
         if (count<npr) {
            if ((line[10]=='D')||(line[10]=='d')) {
               line[10]='e';
            }
            prexp[count]=(solreal)atof((line.substr(0,14)).c_str());
            count++;
            line.erase(0,14);
         }
      }
   }
}