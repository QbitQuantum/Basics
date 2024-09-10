int SL_MSC(Mat Input_Image, Mat Memory_Images, Size img_size, Mat *Fwd_Path, Mat *Bwd_Path, TransformationSet & finalTrans){
	t_total = clock();
	t_loop = 0;

	Mat affine_transformation;
	double MAX_VAL = 255;
	Mat transformations;
	vector < Mat > transformation_set;

    Mat G_layer; // Competition function values for each layer.
    vector< Mat > G; // The competition function
    int iteration_count = 100; // Number of iterations for which MSC will operate.
    int ret = -1;
    double verified_ret;
    FILE *fp;
    double dot_product_input_object = Input_Image.dot(Input_Image);

    
    int layer_count = 1+(int)(xTranslate_layer)+(int)(yTranslate_layer)+(int)(rotate_layer)+(int)(scale_layer);
     
    //transformations.release();
    //G_layer.release();
    
    
    k_transformations = new double[layer_count-1];
    
   // k_transformations[layer_count-1] = k_memory;

		getTransform(img_size, transformation_set, G, finalTrans);

	//transformation_set.clear();

	vector<Mat>().swap(transformation_set);

	/* get the mapping for transformation*/
	vector<Mat> MapForw, MapBack;
	MapForw.reserve(layer_count - 1);
	MapBack.reserve(layer_count - 1);
	getTransMap(img_size, FORWARD, MapForw);
	getTransMap(img_size, BACKWARD, MapBack);



	int* idxTrans = new int[layer_count - 1];

	FPV = new Fwd_Path_Values[layer_count];
	FPV[0].Fwd_Superposition = Input_Image.clone();
	for (int i = 1; i < layer_count; i++) {
		FPV[i].Fwd_Superposition = Mat::zeros(Input_Image.rows, Input_Image.cols, CV_32F);
		FPV[i].Transformed_Templates = Mat::zeros(Size(Input_Image.rows*Input_Image.cols, G[i-1].cols), CV_32F);
	}

	int count = 0;
    while(iteration_count > 0){
        iteration_count--;
        //printf("About to call MSC %d\n",count++);
        ret = MapSeekingCircuit(Input_Image, Memory_Images, img_size, Fwd_Path, Bwd_Path, layer_count, MapForw,MapBack, &G, k_transformations);
        
		bool flag = 1;		/* 1 for stopping the msc*/
        if(iteration_count %5 == 0){
			///* only inspect before the scaling layer*/

			for (int kk = 0; kk < G.size(); kk++) {
				//cout << "-------\n" << G[kk] << "-------\n";
				if (countNonZero(G[kk]) != 1) {
					flag = 0;
					break;
				}
				else {
					vector<Point> idx;
					Mat current;
					G[kk].convertTo(current, CV_8UC1, 100);
					//cout << current << endl << G[kk] << endl;
					findNonZero(current, idx);
					idxTrans[kk] = (idx[0]).x;
				}
			}


			if (dispInMid) {
				imshow("FPV_Forward[1]", (*Fwd_Path) * 255);

				imshow("BPV[1]", (*Bwd_Path) * 255);
				cvWaitKey(0);
			}
			/* stop iteration condition: only one transformation is left*/
			/* record the final transformation*/
			if (flag) {
				double xT = -xT_val[idxTrans[0]];
				double yT = -yT_val[idxTrans[1]];
				double ang = -rot_val[idxTrans[2]];
				double sc;
				if (scale_layer)
					sc = sc_val[idxTrans[3]];
				else
					sc = 1;
				//double xT = 0;
				//double yT = 0;
				//double ang = 0;
				//double sc = 1;
				finalTrans = TransformationSet(xT, yT, ang, sc);
				break;
			}
        }
        //printf("MSC dot products are done\n");
        verified_ret = Verify_Object(Input_Image, *Bwd_Path, dot_product_input_object);
        /*
        if(verified_ret == 0){
            printf("Image not recognized\n");
        }else{
            printf("Everything seems to be fine\n");
        }
         */
    }
	ret = MapSeekingCircuit(Input_Image, Memory_Images, img_size, Fwd_Path, Bwd_Path, layer_count, MapForw, MapBack, &G, k_transformations);
	//printf("The value of verified_ret is %g\n", verified_ret);

	//xT_val.clear();
	//yT_val.clear();
	//rot_val.clear();
	//sc_val.clear();

	vector<double>().swap(xT_val);
	vector<double>().swap(yT_val);
	vector<double>().swap(rot_val);
	vector<double>().swap(sc_val);

	//MapForw.clear();
	vector<Mat>().swap(MapForw);
	//MapBack.clear();
	//G.clear();
	vector<Mat>().swap(MapBack);
	vector<Mat>().swap(G);

	t_total = clock()-t_total;

	printf("it takes %d/%d for loop\n", t_loop, t_total);
    return ret;
    
}