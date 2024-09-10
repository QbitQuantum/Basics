bool ObjPatchMatcher::Match(const Mat& cimg, const Mat& dmap_raw, Mat& mask_map) {

	/*
	 * precompute feature maps
	 */
	// gradient
	Mat gray_img, gray_img_float, edge_map;
	cvtColor(cimg, gray_img, CV_BGR2GRAY);
	gray_img.convertTo(gray_img_float, CV_32F, 1.f/255);
	Canny(gray_img, edge_map, 10, 50);
	cv::imshow("edge", edge_map);
	cv::imshow("color", cimg);
	cv::waitKey(10);

	Mat grad_x, grad_y, grad_mag;
	Sobel(gray_img_float, grad_x, CV_32F, 1, 0);
	Sobel(gray_img_float, grad_y, CV_32F, 0, 1);
	magnitude(grad_x, grad_y, grad_mag);

	// depth
	Mat dmap_float, pts3d, normal_map;
	if( use_depth ) {
		Feature3D feat3d;
		dmap_raw.convertTo(dmap_float, CV_32F);
		Mat cmp_mask;
		compare(dmap_float, 800, cmp_mask, CMP_LT);
		dmap_float.setTo(800, cmp_mask);
		compare(dmap_float, 7000, cmp_mask, CMP_GT);
		dmap_float.setTo(7000, cmp_mask);
		dmap_float = (dmap_float-800)/(7000-800);

		feat3d.ComputeKinect3DMap(dmap_float, pts3d, false);
		feat3d.ComputeNormalMap(pts3d, normal_map);
	}

	/*
	 *	start searching
	 */
	// init searcher
	//searcher.Build(patch_data, BruteForce_L2);	// opencv bfmatcher has size limit: maximum 2^31
	LSHCoder lsh_coder;
	if(use_code) {
		lsh_coder.Load();
	}
	
	Mat score_map = Mat::zeros(edge_map.rows, edge_map.cols, CV_32F);
	Mat mask_vote_map = Mat::zeros(cimg.rows, cimg.cols, CV_32F);
	mask_map = Mat::zeros(cimg.rows, cimg.cols, CV_32F);
	Mat mask_count = Mat::zeros(cimg.rows, cimg.cols, CV_32S);	// number of mask overlapped on each pixel
	Mat feat;
	int topK = 40;
	int total_cnt = countNonZero(edge_map);
	vector<VisualObject> query_patches;
	query_patches.reserve(total_cnt);

	cout<<"Start match..."<<endl;
	
	float max_dist = 0;
	int cnt = 0;
	char str[30];
	double start_t = getTickCount();
//#pragma omp parallel for
	for(int r=patch_size.height/2; r<gray_img.rows-patch_size.height/2; r+=3) {
		for(int c=patch_size.width/2; c<gray_img.cols-patch_size.width/2; c+=3) {

			/*int rand_r = rand()%gray_img.rows;
			int rand_c = rand()%gray_img.cols;
			if(rand_r < patch_size.height/2 || rand_r > gray_img.rows-patch_size.height/2 ||
				rand_c < patch_size.width/2 || rand_c > gray_img.cols-patch_size.width/2) continue;*/
			int rand_r = r, rand_c = c;

			if(edge_map.at<uchar>(rand_r, rand_c) > 0) 
			{
				cnt++;
				destroyAllWindows();

				Rect box(rand_c-patch_size.width/2, rand_r-patch_size.height/2, patch_size.width, patch_size.height);
				MatFeatureSet featset;
				gray_img_float(box).copyTo(featset["gray"]);
				//grad_mag(box).copyTo(featset["gradient"]);
				if(use_depth)
				{ 
					normal_map(box).copyTo(featset["normal"]);
					dmap_float(box).copyTo(featset["depth"]);
				}
				ComputePatchFeat(featset, feat);
				vector<DMatch> matches;
				if(use_code) 
				{
					BinaryCodes codes;
					HashKey key_val;
					lsh_coder.ComputeCodes(feat, codes);
					HashingTools<HashKeyType>::CodesToKey(codes, key_val);
					MatchCode(key_val, topK, matches);
				}
				else
				{
					MatchPatch(feat, topK, matches);
				}
				
				if(matches[0].distance < 0 || matches[0].distance > 1000) {
					cout<<"match dist: "<<matches[0].distance<<endl;
					double minv, maxv;
					cout<<norm(feat, patch_data.row(matches[0].trainIdx), NORM_L2)<<endl;
					minMaxLoc(feat, &minv, &maxv);
					cout<<minv<<" "<<maxv<<endl;
					cout<<feat<<endl<<endl;
					minMaxLoc(patch_data.row(matches[0].trainIdx), &minv, &maxv);
					cout<<minv<<" "<<maxv<<endl;
					cout<<patch_data.row(matches[0].trainIdx)<<endl;
					imshow("cimg", cimg);
					waitKey(0);
				}
				vector<vector<Mat>> pixel_mask_vals(patch_size.height, vector<Mat>(patch_size.width, Mat::zeros(1, topK, CV_32F)));
				VisualObject cur_query;
				cur_query.visual_data.bbox = box;
				cur_query.visual_data.mask = Mat::zeros(patch_size.height, patch_size.width, CV_32F);
				for(size_t i=0; i<topK; i++) { 
					score_map.at<float>(rand_r,rand_c) += matches[i].distance;
					cur_query.visual_data.mask += patch_meta.objects[matches[i].trainIdx].visual_data.mask;
					for(int mr=0; mr<patch_size.height; mr++) for(int mc=0; mc<patch_size.width; mc++) {
						pixel_mask_vals[mr][mc].at<float>(i) = 
							patch_meta.objects[matches[i].trainIdx].visual_data.mask.at<float>(mr, mc);
					}
				}
				score_map.at<float>(rand_r,rand_c) /= topK;
				cur_query.visual_data.mask /= topK;			// average returned mask
				
				// compute mask quality
				Scalar mean_, std_;
				/*ofstream out("pixel_mask_std_100.txt", ios::app);
				for(int mr=0; mr<patch_size.height; mr++) for(int mc=0; mc<patch_size.width; mc++) {
				meanStdDev(pixel_mask_vals[mr][mc], mean_, std_);
				out<<std_.val[0]<<" ";
				}
				out<<endl;*/
				meanStdDev(cur_query.visual_data.mask, mean_, std_);
				cur_query.visual_data.scores.push_back(mean_.val[0]);
				cur_query.visual_data.scores.push_back(std_.val[0]);

				Mat align_mask = Mat::zeros(cimg.rows, cimg.cols, CV_8U);
				int gt_mask_id = patch_meta.objects[matches[0].trainIdx].meta_data.category_id;
				if(gt_mask_id != -1) {
					Mat nn_mask = gt_obj_masks[gt_mask_id];
					//imshow("gt mask", nn_mask*255);
					//waitKey(10);
					Rect gt_box = patch_meta.objects[matches[0].trainIdx].visual_data.bbox;
					Rect align_box = AlignBox(box, gt_box, cimg.cols, cimg.rows);
					vector<ImgWin> boxes; boxes.push_back(align_box);
					//ImgVisualizer::DrawWinsOnImg("alignbox", cimg, boxes);
					//waitKey(10);
					Rect target_box = Rect(box.x-(gt_box.x-align_box.x), box.y-(gt_box.y-align_box.y), align_box.width, align_box.height);
					cout<<target_box<<endl;
					nn_mask(align_box).copyTo(align_mask(target_box));
				}
				align_mask.convertTo(align_mask, CV_32F);
				mask_map += align_mask * matches[0].distance;	//*score_map.at<float>(r,c);
				//mask_count(box) = mask_count(box) + 1;

				//cout<<score_map.at<float>(r,c)<<endl;
				max_dist = MAX(max_dist, matches[0].distance);
				query_patches.push_back(cur_query);

				// vote object regions
				/*Point3f line_ori;
				int obj_pt_sign;
				ComputeDominantLine(cur_query.visual_desc.mask, box.tl(), line_ori, obj_pt_sign);
				for(int rr=0; rr<cimg.rows; rr++) for(int cc=0; cc<cimg.cols; cc++) {
				float line_val = line_ori.x*cc+line_ori.y*rr+line_ori.z;
				if((line_val>0?1:-1)==obj_pt_sign) mask_vote_map.at<float>(rr, cc)++;
				}*/

#ifdef VERBOSE

				// current patch
				Mat disp, patch_gray, patch_grad, patch_normal, patch_depth;
				disp = cimg.clone();
				rectangle(disp, box, CV_RGB(255,0,0), 2);
				resize(gray_img(box), patch_gray, Size(50,50));
				resize(grad_mag(box), patch_grad, Size(50,50));
				Mat cur_mask;
				resize(cur_query.visual_desc.mask, cur_mask, Size(50,50));
				if(use_depth) 
				{
					resize(normal_map(box), patch_normal, Size(50,50));

					normalize(dmap_float(box), patch_depth, 1, 0, NORM_MINMAX);
					patch_depth.convertTo(patch_depth, CV_8U, 255);
					//dmap_float(box).convertTo(patch_depth, CV_8U, 255);
					resize(patch_depth, patch_depth, Size(50,50));
				}

				Mat onormal;
				sprintf_s(str, "query_gray_%d.jpg", cnt);
				imshow(str, patch_gray);
				imwrite(str, patch_gray);

				/*sprintf_s(str, "query_grad_%d.jpg", cnt);
				ImgVisualizer::DrawFloatImg(str, patch_grad, onormal, true);
				imwrite(str, onormal);*/
				
				sprintf_s(str, "query_depth_%d.jpg", cnt);
				imshow(str, patch_depth);
				imwrite(str, patch_depth);
				
				sprintf_s(str, "query_normal_%d.jpg", cnt);
				ImgVisualizer::DrawNormals(str, patch_normal, onormal, true);
				imwrite(str, onormal);

				sprintf_s(str, "query_box_%d.jpg", cnt);
				imshow(str, disp);
				imwrite(str, disp);

				//imshow("align mask", align_mask*255);

				cur_mask.convertTo(cur_mask, CV_8U, 255);
				sprintf_s(str, "query_tmask_%d.jpg", cnt);
				imshow(str, cur_mask);
				imwrite(str, cur_mask);

				// show match results
				vector<Mat> res_imgs(topK);
				vector<Mat> res_gradients(topK);
				vector<Mat> res_normals(topK);
				vector<Mat> res_depth(topK);
				vector<Mat> db_boxes(topK);
				vector<Mat> res_masks(topK);
				for(size_t i=0; i<topK; i++) {
					VisualObject& cur_obj = patch_meta.objects[matches[i].trainIdx];
					// mask
					cur_obj.visual_desc.mask.convertTo(res_masks[i], CV_8U, 255);
					// gray
					cur_obj.visual_desc.extra_features["gray"].convertTo(res_imgs[i], CV_8U, 255);
					// gradient
					//ImgVisualizer::DrawFloatImg("", cur_obj.visual_desc.extra_features["gradient"], res_gradients[i], false);
					// 3D
					if(use_depth) 
					{
						// normal
						tools::ImgVisualizer::DrawNormals("", cur_obj.visual_desc.extra_features["normal"], res_normals[i]);
						// depth
						normalize(cur_obj.visual_desc.extra_features["depth"], res_depth[i], 1, 0, NORM_MINMAX);
						res_depth[i].convertTo(res_depth[i], CV_8U, 255);
						//cur_obj.visual_desc.extra_features["depth"].convertTo(res_depth[i], CV_8U, 255);
					}
					// box on image
					db_boxes[i] = imread(patch_meta.objects[matches[i].trainIdx].imgpath);
					resize(db_boxes[i], db_boxes[i], Size(cimg.cols, cimg.rows));
					rectangle(db_boxes[i], patch_meta.objects[matches[i].trainIdx].visual_desc.box, CV_RGB(255,0,0), 2);
				}
				Mat out_img;
				sprintf_s(str, "res_gray_%d.jpg", cnt);
				ImgVisualizer::DrawImgCollection(str, res_imgs, topK, Size(50,50), out_img);
				imwrite(str, out_img);
				
				sprintf_s(str, "res_normal_%d.jpg", cnt);
				ImgVisualizer::DrawImgCollection(str, res_normals, topK, Size(50,50), out_img);
				imwrite(str, out_img);

				sprintf_s(str, "res_depth_%d.jpg", cnt);
				ImgVisualizer::DrawImgCollection(str, res_depth, topK, Size(50,50), out_img);
				imwrite(str, out_img);

				/*sprintf_s(str, "res_gradient_%d.jpg", cnt);
				tools::ImgVisualizer::DrawImgCollection(str, res_gradients, topK, Size(50,50), out_img);
				imwrite(str, out_img);*/

				sprintf_s(str, "res_mask_%d.jpg", cnt);
				tools::ImgVisualizer::DrawImgCollection(str, res_masks, topK, Size(50,50), out_img);
				imwrite(str, out_img);

				sprintf_s(str, "res_box_%d.jpg", cnt);
				tools::ImgVisualizer::DrawImgCollection(str, db_boxes, topK/2, Size(200, 200), out_img);
				imwrite(str, out_img);

				waitKey(0);
#endif

				cout<<total_cnt--<<endl;
			}
		}
	}
	cout<<"match done. Time cost: "<<(getTickCount()-start_t)/getTickFrequency()<<"s."<<endl;

	//score_map(Rect(patch_size.width/2, patch_size.height/2, score_map.cols-patch_size.width/2, score_map.rows-patch_size.height/2)).copyTo(score_map);
	//score_map.setTo(max_dist, 255-edge_map);
	normalize(score_map, score_map, 1, 0, NORM_MINMAX);
	score_map = 1-score_map;
	//tools::ImgVisualizer::DrawFloatImg("bmap", score_map);

	mask_map /= max_dist;
	cout<<max_dist<<endl;
	normalize(mask_map, mask_map, 1, 0, NORM_MINMAX);
	//tools::ImgVisualizer::DrawFloatImg("maskmap", mask_map);

	//normalize(mask_vote_map, mask_vote_map, 1, 0, NORM_MINMAX);
	//ImgVisualizer::DrawFloatImg("vote map", mask_vote_map);
	//waitKey(0);

	return true;

	// pick top weighted points to see if they are inside objects
	// try graph-cut for region proposal
	// among all retrieved mask patch, select most discriminative one and do graph-cut
	sort(query_patches.begin(), query_patches.end(), [](const VisualObject& a, const VisualObject& b) { 
		return a.visual_data.scores[1] > b.visual_data.scores[1]; });
	for(size_t i=0; i<query_patches.size(); i++) {
		Mat disp_img = cimg.clone();
		rectangle(disp_img, query_patches[i].visual_data.bbox, CV_RGB(255,0,0));
		imshow("max std box", disp_img);
		Mat big_mask;
		resize(query_patches[i].visual_data.mask, big_mask, Size(50,50));
		ImgVisualizer::DrawFloatImg("max std mask", big_mask);
		waitKey(0);
		// use mask to do graph-cut
		Mat fg_mask(cimg.rows, cimg.cols, CV_8U);
		fg_mask.setTo(cv::GC_PR_FGD);
		Mat th_mask;
		threshold(query_patches[i].visual_data.mask, th_mask, query_patches[i].visual_data.scores[0], 1, CV_THRESH_BINARY);
		th_mask.convertTo(th_mask, CV_8U);
		fg_mask(query_patches[i].visual_data.bbox).setTo(cv::GC_FGD, th_mask);
		th_mask = 1-th_mask;
		fg_mask(query_patches[i].visual_data.bbox).setTo(cv::GC_BGD, th_mask);
		cv::grabCut(cimg, fg_mask, Rect(0,0,1,1), Mat(), Mat(), 3, cv::GC_INIT_WITH_MASK);
		fg_mask = fg_mask & 1;
		disp_img.setTo(Vec3b(0,0,0));
		cimg.copyTo(disp_img, fg_mask);
		cv::imshow("cut", disp_img);
		cv::waitKey(0);
	}


	float ths[] = {0.9f, 0.8f, 0.7f, 0.6f, 0.5f, 0.4f, 0.3f, 0.2f};
	for(size_t i=0; i<8; i++) {
		Mat th_mask;
		threshold(mask_map, th_mask, ths[i], 1, CV_THRESH_BINARY);
		char str[30];
		sprintf_s(str, "%f", ths[i]);
		ImgVisualizer::DrawFloatImg(str, th_mask);
		waitKey(0);
	}

	return true;
}