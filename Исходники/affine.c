void *affine_loop(void *number)
{

/*
	if(set_single_core_affinity()!=EXIT_SUCCESS)
	{
		perror("Core Affinity");
	}
*/

	int block_size;
	int max_files;
	int i=0;
	int section=0;
	float pos[8]={0,0,1,0,0,1,1,1};

	Point2f srcTri[4];
	Point2f dstTri[4];

	max_files=3601;
	block_size=max_files/4;

	Mat rot_mat( 2, 3, CV_32FC1 );
	Mat warp_mat( 2, 3, CV_32FC1 );


	// Output variables
	Mat src, warp_dst, warp_rotate_dst;

	struct thread_limits *ptr_obj = (struct thread_limits *) number;
	int start_loop = ptr_obj->start_no;
	int stop_loop  = ptr_obj->stop_no;

	/*------------------------- Starting the loop --------------------------*/

	for (i=start_loop; i<=stop_loop; i++)
	{

		/*------------------------- Loading the Image --------------------------*/

		if(option==1)
		{
			// Select the right frame
			sprintf(frame_name2,"Sobel_frame_no_%05u.ppm",i);
			// Load the Image
			src = imread( frame_name2, 1 );
		}

		else
		{
			sprintf(frame_name,"Frame_no_%05u.ppm",i);
			src = imread( frame_name, 1 );
		}

		/*---------------------- Affine Transform : Warp -----------------------*/

		// Setting up the output image parameters

		warp_dst = Mat::zeros( src.rows, src.cols, src.type() );


		/*---------------------- Change the parameter values ----------------------*/

	
	
		switch(section)
		{

			case 0:
			{

				pos[1]=pos[1]+0.001;
				pos[2]=pos[2]-0.001;
				pos[4]=pos[4]+0.001;
				pos[7]=pos[7]-0.001;
		
			
				// Setting parameters for matrix computation

				srcTri[0] = Point2f( 0,0 );
				srcTri[1] = Point2f( src.cols - 1, 0 );
				srcTri[2] = Point2f( 0, src.rows - 1 );
				srcTri[3] = Point2f( src.cols - 1, src.rows - 1 );

				dstTri[0] = Point2f( src.cols*pos[0], src.rows*pos[1] );
				dstTri[1] = Point2f( src.cols*pos[2], src.rows*pos[3] );
				dstTri[2] = Point2f( src.cols*pos[4], src.rows*pos[5] );
				dstTri[3] = Point2f( src.cols*pos[6], src.rows*pos[7] );
			
				section=i/block_size;

				//printf("Case 0: %u\t %f %f %f %f %f %f %f %f\n",i,pos[0],pos[1],pos[2],pos[3],pos[4],pos[5],pos[6],pos[7]);

				break;
			}

			case 1:
			{

				pos[0]=pos[0]+0.001;
				pos[3]=pos[3]+0.001;
				pos[5]=pos[5]-0.001;
				pos[6]=pos[6]-0.001;
		
			
				// Setting parameters for matrix computation

				srcTri[0] = Point2f( 0,0 );
				srcTri[1] = Point2f( src.cols - 1, 0 );
				srcTri[2] = Point2f( 0, src.rows - 1 );
				srcTri[3] = Point2f( src.cols - 1, src.rows - 1 );

				dstTri[0] = Point2f( src.cols*pos[0], src.rows*pos[1] );
				dstTri[1] = Point2f( src.cols*pos[2], src.rows*pos[3] );
				dstTri[2] = Point2f( src.cols*pos[4], src.rows*pos[5] );
				dstTri[3] = Point2f( src.cols*pos[6], src.rows*pos[7] );
			
				section=i/block_size;

				//printf("Case 1: %u\t %f %f %f %f %f %f %f %f\n",i,pos[0],pos[1],pos[2],pos[3],pos[4],pos[5],pos[6],pos[7]);

				break;
			}
		
			case 2:
			{
			
				pos[1]=pos[1]-0.001;
				pos[2]=pos[2]+0.001;
				pos[4]=pos[4]-0.001;
				pos[7]=pos[7]+0.001;
		
			
				// Setting parameters for matrix computation

				srcTri[0] = Point2f( 0,0 );
				srcTri[1] = Point2f( src.cols - 1, 0 );
				srcTri[2] = Point2f( 0, src.rows - 1 );
				srcTri[3] = Point2f( src.cols - 1, src.rows - 1 );

				dstTri[0] = Point2f( src.cols*pos[0], src.rows*pos[1] );
				dstTri[1] = Point2f( src.cols*pos[2], src.rows*pos[3] );
				dstTri[2] = Point2f( src.cols*pos[4], src.rows*pos[5] );
				dstTri[3] = Point2f( src.cols*pos[6], src.rows*pos[7] );
			
				section=i/block_size;

				//printf("Case 2: %u\t %f %f %f %f %f %f %f %f\n",i,pos[0],pos[1],pos[2],pos[3],pos[4],pos[5],pos[6],pos[7]);

				break;
			}
		

			case 3:
			{

				pos[0]=pos[0]-0.001;
				pos[3]=pos[3]-0.001;
				pos[5]=pos[5]+0.001;
				pos[6]=pos[6]+0.001;
		
			
				// Setting parameters for matrix computation

				srcTri[0] = Point2f( 0,0 );
				srcTri[1] = Point2f( src.cols - 1, 0 );
				srcTri[2] = Point2f( 0, src.rows - 1 );
				srcTri[3] = Point2f( src.cols - 1, src.rows - 1 );

				dstTri[0] = Point2f( src.cols*pos[0], src.rows*pos[1] );
				dstTri[1] = Point2f( src.cols*pos[2], src.rows*pos[3] );
				dstTri[2] = Point2f( src.cols*pos[4], src.rows*pos[5] );
				dstTri[3] = Point2f( src.cols*pos[6], src.rows*pos[7] );

			
				section=i/block_size;

				//printf("Case 3: %u\t %f %f %f %f %f %f %f %f\n",i,pos[0],pos[1],pos[2],pos[3],pos[4],pos[5],pos[6],pos[7]);

				break;
			}

			default:
			{
				//printf("Value: %d\n",section);
				//perror("Default switch() case");
				break;
			}
		}
		



		// Calculate the Affine Transform matrix

		warp_mat = getAffineTransform( srcTri, dstTri );


		// Applying the Affine Transform to the src image

		warpAffine( src, warp_dst, warp_mat, warp_dst.size() );



		/*-------------------- Affine Transform : Rotate -----------------------*/

		// Compute the Rotation Matrix Parameters

		Point center = Point( warp_dst.cols/2, warp_dst.rows/2 );
		double angle = ROTATION_ANGLE;
		double scale = ISOTROPIC_SCALE_FACTOR;

		// Generate the Rotation Matrix

		rot_mat = getRotationMatrix2D( center, angle, scale );

		// Rotate the Image

		warpAffine( warp_dst, warp_rotate_dst, rot_mat, warp_dst.size() );


		/*------------------------- Storing the Image ---------------------------*/


		sprintf(frame_name3,"Affine_frame_no_%05u.ppm",i);

		// Storing the Image

		imwrite(frame_name3, warp_dst);

	}
	// End of 'for' loop

	return NULL;
}