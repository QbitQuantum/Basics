void PlotRna(char* seqName, char* sequence, short* structure, char* filename, float score)
{
  /*A:red, U: Green, G:Blue, C:Yellow*/
  int i, j;
  int length;
  int sizex, sizey;
  
  
  fname = filename;
  length = (int)strlen(sequence) ;
  sizex = length;
  sizey = length;
  /*printf("here......length %d\n",length);*/
  drawInit(length, length, seqName, filename, score);
  /* print out stems */
  int st, stp;
  char* c = (char*)malloc(sizeof(char)*1000);


  i = 0; j = 0;
  while(i < length) {
    while(i < length && (structure[i] == 0 || structure[i] < i)) i++;
    st = i;    
    while(i < length && (structure[i]-1 == structure[i+1])) i++; 
    stp = i;
    if (i >= length) break;
    
    sprintf(c, "%d-%d; %d-%d ",st+1, stp+1, structure[stp],structure[st]);
    i++; j++;
    if ((j%2) == 1) drawtext (sizex*CELLSIZE/4,sizey*CELLSIZE/10.0+((int)(j/2)+1)*CELLSIZE*sizey/30,c,1.0e6);
    else drawtext (sizex*CELLSIZE/2,sizey*CELLSIZE/10.0+((int)(j/2))*CELLSIZE*sizey/30,c,1.0e6);
    flushinput();

  }

 
 
  
  for(i=0; i<length; i++) {
    if(sequence[i] == 'A' || sequence[i] == 'a') 
      setcolor(RED);
    else if(sequence[i] == 'U'|| sequence[i] == 'u' || sequence[i] == 'T' || sequence[i] == 't')
      setcolor(GREEN);
    else if(sequence[i] == 'G' || sequence[i] == 'g')
      setcolor(BLUE);
    else if(sequence[i] == 'C' || sequence[i] == 'c')
      setcolor(YELLOW);
    else
      setcolor(BLACK);
    fillrect((i+0.2)*CELLSIZE, (sizey/2 - 0.8)*CELLSIZE, (i+0.8)*CELLSIZE, (sizey/2 - 0.2)*CELLSIZE);
    flushinput();
  }
  plotBP(sequence, structure);
  close_postscript();
  close_graphics();
}