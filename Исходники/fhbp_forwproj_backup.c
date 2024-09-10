/*
 * sino is freed by caller
 * ans is freed by caller
 *
 * This function is the top-level function for recursive backprojection.
 * It makes a call to 'direct_forw' once size<=baseSize.
 */
void bp_forw(sinograms* sino,int size,myFloat* tau,image* ans)
{
  sinograms* newSino;
  image* subImage;

  int i,j,m,n,k,p,u,v;

  myFloat* curRow;
  myFloat temp1,temp2;

  int pp;

  int newSize;
  int numSino;
  int sinoSize;
  int offsetX;
  int offsetY;

  myFloat shiftX,shiftY; 

  myFloat* nu_i;
  myFloat* nu_i2;
  myFloat* nu_temp;
  myFloat nu_p,nu_2n;

  int P = sino->num;
  myFloat angle;

  myFloat sum=0;
  myFloat shift;

  int newSinoSize;
  int newNumSino;
  int constShiftingFactor;
  int shiftingFactor; 

  if( size<=baseSize || sino->num <= 1 ){ 
    //BASE CASE!!!!
    direct_forw( sino , size , tau , ans );  
    return;
  } 

  else{
    printf( "\n\nGeneral case!!!!\n\n" );
    //GENERAL CASE
    subImage = ( image* ) malloc( 1 * sizeof( image ) );          //prepare subImage for recursive call
    newSize = size / 2;
    numSino = ( sino->num );
    sinoSize = ( sino->size );

    subImage->size = newSize;
    ( subImage->pixel ) = ( myFloat** )malloc( newSize * sizeof( myFloat* ) );
    shift = ( myFloat )size/4 * oneOverT;  //save some computations when computing nu's by premultiply with 1/T

    newSinoSize = ceilf((myFloat)sinoSize/2) + (sinoSize%4==3 || sinoSize%4==2?1:0);
    constShiftingFactor = ((myFloat)newSinoSize/2) - ((myFloat)sinoSize/2);    

    //for each part (that we break the image into)
    for(i=0;i<NUM_PARTS;i++){
        if(i==0){
	        shiftX = shift;
	        shiftY = shift;
        }
        else if(i==1){
	        shiftX = -shift;
	        shiftY = shift;
        }
        else if(i==2){
	        shiftX = -shift;
	        shiftY = -shift;
        }
        else {
	        shiftX = shift;
	        shiftY = -shift;
        }


      /************/

      nu_i = (myFloat*)malloc(numSino*sizeof(myFloat));
      nu_i2 = (myFloat*)malloc(numSino*sizeof(myFloat));          
      nu_temp = (myFloat*)malloc(numSino*sizeof(myFloat));

      for(p=0;p<numSino;p++){
	    //for each angle, compute nu_i,p
	    nu_i[p] = nu_forw(tau[p],shiftX,shiftY,(sino->sine)[p],(sino->cosine)[p]);//,oneOverT);
	    nu_temp[p] = rintf(nu_i[p]);
      }//end for p

      //nu_i are real nu's (for this quadrant, for all theta's)
      //nu_temp are rounded nu's

      //decide whether to downsample
      if(size<=dwnsplSize){
        printf("\nIter 1\n");
	    //throw away half the projections as usual
	    newSino = newSinoForNextIter_forw(sino,newSinoSize,constShiftingFactor,nu_i);
	    pp = 2;   
      }
      else {  
	    //keep all of them!
        printf("\nIter 2\n");  
	    newSino = newSinoForNextIter_forw2(sino,newSinoSize,constShiftingFactor,nu_i);
	    pp = 1;   
      } 

      /************/


      
      //manipulate the right part of the image
      if(i<2){
	    // 0 and 1
	    offsetY = newSize;
      }
      else {
	    // 2 and 3
	    offsetY = 0;
      }

      if(i==0 || i==3){
	    // 0 and 3
	    offsetX = newSize;
      }
      else {
	    // 1 and 2
	    offsetX = 0;
      }

      //make subImages point to appropriate parts of the big image
      for(m=0;m<newSize;m++){
	    (subImage->pixel)[m] = (ans->pixel)[m+offsetY] + offsetX;
      }
      
      newNumSino = (newSino->num);
      //for each nu_p, compute <nu_p>
      for(p=0;p<newNumSino;p++){
        nu_i2[p] = nu_i[p];
	    nu_i[p] = nu_i[pp*p]-nu_temp[pp*p];
      }


      //call bp_forw recursively
      /////////////////////////////////////////////////
      bp_forw(newSino,/*ker,*/newSize,nu_i,subImage);     //
      /////////////////////////////////////////////////
      
      
      if( size <= dwnsplSize ){
        printf( "\nTobe done\n" );
      }

      else{
        for(n=0;n<newNumSino;n++){
            shiftingFactor = rintf(nu_i2[n]) + constShiftingFactor;      
            for(m=0;m<newSinoSize;m++){
                (sino->sino)[n][m-shiftingFactor] += (newSino->sino)[n][m];
            }//end for m
        }//end for n        
      }//end if

      //free(subImage);
      //free(subImage->pixel);     
      //freeSino_forw(newSino);
      //free(newSino);
      //subImage = NULL;
      //free(nu_i);
      //free(nu_temp);
      //nu_i = NULL;
    
    }//end for i

    free(subImage);
    free(subImage->pixel);

    freeSino_forw(newSino);
    free(newSino);
    newSino = NULL;
    free(nu_i);
    free(nu_temp);
    nu_i = NULL;     
    
    //do not free subImage's pixels, because they are the output!
    
    return;

  }//end if not base case


}//end function bp_forw