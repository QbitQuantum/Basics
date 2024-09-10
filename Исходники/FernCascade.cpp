vector<Mat_<double> > FernCascade::Train(const vector<Mat_<uchar> >& images,
                                    const vector<Mat_<double> >& current_shapes,
                                    const vector<Mat_<double> >& ground_truth_shapes,
                                    const vector<BoundingBox> & bounding_box,
                                    const Mat_<double>& mean_shape,
                                    int second_level_num,
                                    int candidate_pixel_num,
                                    int fern_pixel_num){
    Mat_<double> candidate_pixel_locations(candidate_pixel_num,2);
    Mat_<int> nearest_landmark_index(candidate_pixel_num,1);
    vector<Mat_<double> > regression_targets;
    RNG random_generator(getTickCount());
    second_level_num_ = second_level_num;
    
    // calculate regression targets: the difference between ground truth shapes and current shapes
    // candidate_pixel_locations: the locations of candidate pixels, indexed relative to its nearest landmark on mean shape 
    regression_targets.resize(current_shapes.size()); 
    for(int i = 0;i < current_shapes.size();i++){
        regression_targets[i] = ProjectShape(ground_truth_shapes[i],bounding_box[i]) 
                                - ProjectShape(current_shapes[i],bounding_box[i]);
        Mat_<double> rotation;
        double scale;
        SimilarityTransform(mean_shape,ProjectShape(current_shapes[i],bounding_box[i]),rotation,scale);
        transpose(rotation,rotation);

        regression_targets[i] = scale * regression_targets[i] * rotation;
    }

    
    // get candidate pixel locations, please refer to 'shape-indexed features'
    for(int i = 0;i < candidate_pixel_num;i++){
        double x = random_generator.uniform(-1.0,1.0);
        double y = random_generator.uniform(-1.0,1.0);
        if(x*x + y*y > 1.0){
            i--;
            continue;
        }
        // find nearest landmark index
        double min_dist = 1e10;
        int min_index = 0;
        for(int j = 0;j < mean_shape.rows;j++){
            double temp = pow(mean_shape(j,0)-x,2.0) + pow(mean_shape(j,1)-y,2.0);
            if(temp < min_dist){
                min_dist = temp;
                min_index = j;
            }
        }
        candidate_pixel_locations(i,0) = x - mean_shape(min_index,0);
        candidate_pixel_locations(i,1) = y - mean_shape(min_index,1);
        nearest_landmark_index(i) = min_index;   
    }

    // get densities of candidate pixels for each image
    // for densities: each row is the pixel densities at each candidate pixels for an image 
    // Mat_<double> densities(images.size(), candidate_pixel_num);
    vector<vector<double> > densities;
    densities.resize(candidate_pixel_num);
    for(int i = 0;i < images.size();i++){
        Mat_<double> rotation;
        double scale;
        Mat_<double> temp = ProjectShape(current_shapes[i],bounding_box[i]);
        SimilarityTransform(temp,mean_shape,rotation,scale);
        for(int j = 0;j < candidate_pixel_num;j++){
            double project_x = rotation(0,0) * candidate_pixel_locations(j,0) + rotation(0,1) * candidate_pixel_locations(j,1);
            double project_y = rotation(1,0) * candidate_pixel_locations(j,0) + rotation(1,1) * candidate_pixel_locations(j,1);
            project_x = scale * project_x * bounding_box[i].width / 2.0;
            project_y = scale * project_y * bounding_box[i].height / 2.0;
            int index = nearest_landmark_index(j);
            int real_x = project_x + current_shapes[i](index,0);
            int real_y = project_y + current_shapes[i](index,1); 
            real_x = std::max(0.0,std::min((double)real_x,images[i].cols-1.0));
            real_y = std::max(0.0,std::min((double)real_y,images[i].rows-1.0));
            densities[j].push_back((int)images[i](real_y,real_x));
        }
    }
        
    // calculate the covariance between densities at each candidate pixels 
    Mat_<double> covariance(candidate_pixel_num,candidate_pixel_num);
    Mat_<double> mean;
    for(int i = 0;i < candidate_pixel_num;i++){
        for(int j = i;j< candidate_pixel_num;j++){
            double correlation_result = calculate_covariance(densities[i],densities[j]);
            covariance(i,j) = correlation_result;
            covariance(j,i) = correlation_result;
        }
    } 


    // train ferns
    vector<Mat_<double> > prediction;
    prediction.resize(regression_targets.size());
    for(int i = 0;i < regression_targets.size();i++){
        prediction[i] = Mat::zeros(mean_shape.rows,2,CV_64FC1); 
    } 
    ferns_.resize(second_level_num);
    for(int i = 0;i < second_level_num;i++){
        cout<<"Training ferns: "<<i+1<<" out of "<<second_level_num<<endl;
        vector<Mat_<double> > temp = ferns_[i].Train(densities,covariance,candidate_pixel_locations,nearest_landmark_index,regression_targets,fern_pixel_num);     
        // update regression targets
        for(int j = 0;j < temp.size();j++){
            prediction[j] = prediction[j] + temp[j];
            regression_targets[j] = regression_targets[j] - temp[j];
        }  
    }
    
    for(int i = 0;i < prediction.size();i++){
        Mat_<double> rotation;
        double scale;
        SimilarityTransform(ProjectShape(current_shapes[i],bounding_box[i]),mean_shape,rotation,scale);
        transpose(rotation,rotation);
        prediction[i] = scale * prediction[i] * rotation; 
    } 
    return prediction;    
}