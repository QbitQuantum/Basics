 void run(){
     
     RNG rng(12345);
     while(ros::ok()) {
         current_time = ros::Time::now();
         //computer odemetry using integration
         double dt = (current_time - last_time).toSec();
         //Prediction model
         Prediction(dt);
         //Measurement model
         EstimateMeasurement_Update();
         RealMeasurement_Update();
         Innovation();
         ReSampling();
         Normalization();
         
         // Show all the particles on the map
         image = imread(PATH,CV_LOAD_IMAGE_COLOR);
         
         Scalar color = Scalar(rng.uniform(0,255),rng.uniform(0,255),rng.uniform(0,255));
         for(int i=0;i<Particles;++i){
             particle_position = Point(particle_state[1][i]*100+5,particle_state[0][i]*100+5);
             circle(image,particle_position,4,color,-1,8,0);
         }
         
         // Show the final predicted position on the map
         circle(postion_image,position,4,color,-1,8,0);
         
         //Show odometry localization on the map
         namedWindow( OPENCV_WINDOW, CV_WINDOW_NORMAL );// Create a window for display.
         imshow( OPENCV_WINDOW, image );                  // Show our map inside it.
         namedWindow( OPENCV_WINDOW1, CV_WINDOW_NORMAL );// Create a window for display.
         imshow( OPENCV_WINDOW1, postion_image);
         
         //Publish Geometry msg of Predicted postion
         msg.x = x;
         msg.y = y;
         msg.theta = theta;
         position_pub.publish(msg);
         
         waitKey(3);                                 // Wait for a keystroke in the window
         last_time = current_time;
         //Use if add a subscription(Add as good measure)
         ros::spinOnce();
         //Delays untill it is time to send another message
         rate->sleep();
     }
 }