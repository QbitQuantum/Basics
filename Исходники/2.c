   int mergeSort(int* buf, long int start, long int size)
   {
     if(size>1)
 	{
 		int size1,size2;
 			if(size%2)
 				{
 					    size1=(int)(size/2)+1;
 							size2=(int)(size/2);
 								}
 									else
 										{
 											    size1=size2=(int)(size/2);
 												    }
 													    if(mergeSort(buf, start,size1) || mergeSort(buf, start+size1,size2))
 														    {
 																return 1;
 																	}
 																		int *tmp = malloc(size*sizeof(int));
 																			if(tmp==NULL)
 																				{
 																					    fprintf (stderr, "Хозяина, памяти мала\n");
 																							fcloseall();
 																								    return 1;
 																									    }
 																										    long int i=0,j=0,k=0;
 																											    while(i!=size1 && j!=size2)
 																												    {
 																														if(buf[start+i]<buf[start+size1+j])
 																															    {
 																																	    tmp[k++] = buf[start+i++];
 																																			}
 																																				    else
 																																						{
 																																								tmp[k++] = buf[start+size1+j++];
 																																									    }
 																																										    }
 																																											    while(i!=size1)
 																																												    {
 																																														tmp[k++] = buf[start+i++];
 																																															}
 																																																while(j!=size2)
 																																																	{
 																																																		    tmp[k++] = buf[start+size1+j++];
 																																																			    }
 																																																				    for(i=0; i<size; i++)
 																																																					    {
 																																																							buf[start+i] = tmp[i];
 																																																								}
 																																																									free(tmp);
 																																																									    }
 																																																										return 0;
 																																																										}