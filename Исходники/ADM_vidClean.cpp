uint8_t AVDMVideoSmooth::getFrameNumberNoAlloc(uint32_t frame,
				uint32_t *len,
   				ADMImage *data,
				uint32_t *flags)
{
uint8_t *dst,*dstu,*dstv,*src,*srcu,*srcv;

            	int16_t l,u=0,v=0;
             	int16_t nb;
              int16_t fl,fu,fv;
              int16_t	ldelta,udelta,vdelta;
              int16_t   threshold=10,su=0,sv=0;

			if(frame>=_info.nb_frames) return 0;
			ADM_assert(_uncompressed);					
								
		// read uncompressed frame
       		if(!_in->getFrameNumberNoAlloc(frame, len,_uncompressed,flags)) return 0;

         	src=YPLANE(_uncompressed);
           	srcu=UPLANE(_uncompressed);;
           	srcv=VPLANE(_uncompressed);;

              dst=YPLANE(data);
              dstu=UPLANE(data);
              dstv=VPLANE(data);

              int16_t radius=_param->radius;

         		for(int32_t y=0;y<(int32_t)(_info.height );y++)
           	{
		         		for(int32_t x=0;x<(int32_t)(_info.width );x++)
             			{
                      	// for each pixel we take the surrounding one
                       	// if threshold is not met
                        		l=getPixel(x,y,_uncompressed->data);
                          	if(!(x&1))
                           	{
                          		u=getPixelU(x,y,srcu);
                          		v=getPixelU(x,y,srcv);
                            }
                            nb=0;
                            fl=0;fu=0;fv=0;


                             //------------------------                        	                        		
                   	    	for(int16_t yy=-radius+1;yy<radius;yy++)
                         	{                       			

                        	    	for(int16_t xx=-radius+1;xx<radius;xx++)
                              		{
                                  		if( (xx*xx+yy*yy)<radius*radius)
                                    	{
                                   		ldelta =getPixel(x+xx,y+yy,_uncompressed->data)-l;
  		                            		udelta=getPixelU(x+xx,y+yy,srcu)-u;
                                     		vdelta=getPixelU(x+xx,y+yy,srcv)-v;                                       	


                                         	if((udelta*udelta<threshold*threshold)&&
                                          	(vdelta*vdelta<threshold*threshold) &&
                                           	(ldelta*ldelta<threshold*threshold))
                                          		{
                                                  	nb++;
                                                   	fl=fl+ldelta+l;
                                                    fu=fu+udelta+u;
															fv=fv+vdelta+v;
                                              	}
                                        }
                                 	 }
                                  }
                                  //----------------------------------
                                  //
                                  // average value
                                  	fl=fl/nb;
                                 	fu=fu/nb;
                                  	fv=fv/nb;
                                   // now melt it
                                  	// 50/50
                                 /*  fl=(fl+l)>>1;
                                   fu=(fu+u)>>1;
                                   fv=(fv+v)>>1;*/

                                 	*dst++=fl;
                                  if(y&1)       	
                                  if(x&1)				
                                  	{
                        			setPixelU(  (su+fu)>>1,x,y,dstu);
                           			setPixelU(  (sv+fv)>>1,x,y,dstv);  
					}
                                	else
                                 	{
                                     	su=fu;
                                      	sv=fv;
                                    }

                  	}          // end for x