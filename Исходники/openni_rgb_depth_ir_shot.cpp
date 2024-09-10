    void saveImagesToDisk(ros::NodeHandle& nh, ros::Subscriber& sub)
    {	 
    	//pcl::ScopeTime t1 ("save images");
    	  {  
          boost::mutex::scoped_lock lock(rgb_mutex_);   
          memcpy( cv_rgb_.data, &rgb_data_[0], 3*rows_*cols_*sizeof(unsigned char));
          
          new_rgb_ = false;
        }
        
        capture_->stop();        
        sub.shutdown();        
        sub = nh.subscribe("/camera/depth/image_raw", 1, &OpenNIShoter::frameDepthCallback, this);        
        new_depth_ = false;
        capture_->start();
        
        do
        {         
          if (new_depth_ == true )
          {
            boost::mutex::scoped_lock lock(depth_mutex_);   
            memcpy( cv_depth_.data, &depth_data_[0], rows_*cols_*sizeof(uint16_t));
          
            new_depth_ = false;
            break;
          }
          
          boost::this_thread::sleep (boost::posix_time::millisec (10)); 
             
        } while (1);
        
        
        capture_->stop();        
        sub.shutdown();        
        sub = nh.subscribe("/camera/ir/image", 1, &OpenNIShoter::frameIRCallback, this);   
        new_ir_ = false;         
        capture_->start();
        
        do
        {         
          if (new_ir_ == true )
          {            
            boost::mutex::scoped_lock lock(ir_mutex_);   
            memcpy( cv_ir_raw_.data, &ir_data_[0], rows_*cols_*sizeof(uint16_t));            
            
            cv_ir_raw_.convertTo(cv_ir_, CV_8U); 
            cv::equalizeHist( cv_ir_, cv_ir_ );
            
            int max = 0;
            
            for (int i=0; i< rows_; i++)
            {
              for (int j=0; j< cols_; j++)
              {
               if (ir_data_[i+j*rows_] > max)
                max = ir_data_[i+j*rows_];
              }
            }
            
            std::cout << "max IR val: " << max << std::endl;
            
          
            new_ir_ = false;
            break;
          }
          
          boost::this_thread::sleep (boost::posix_time::millisec (10)); 
             
        } while (1);
        
        capture_->stop();        
        sub.shutdown();        
        sub = nh.subscribe("/camera/rgb/image_raw", 1, &OpenNIShoter::frameRGBCallback, this);         
        capture_->start();

	      sprintf(depth_file, "/Depth/%018ld.png", timestamp_depth_ );
	      sprintf(rgb_file, "/RGB/%018ld.png", timestamp_rgb_);  
        sprintf(ir_file, "/IR/%018ld.png", timestamp_ir_);  
        
	      cv::imwrite( write_folder_ + depth_file, cv_depth_);
	      cv::imwrite( write_folder_ + rgb_file, cv_rgb_);
        cv::imwrite( write_folder_ + ir_file, cv_ir_);
	      
	      sprintf(depth_file_PNG, "/Depth/%018ld.png", timestamp_depth_);
	      sprintf(rgb_file_PNG, "/RGB/%018ld.png", timestamp_rgb_);
        sprintf(ir_file_PNG, "/IR/%018ld.png", timestamp_ir_);

	      off_rgb_.width(18);
	      off_rgb_.fill('0');
	      off_rgb_ << timestamp_rgb_;
	      off_rgb_ <<  " " << rgb_file_PNG << std::endl;
        
        off_depth_.width(18);
	      off_depth_.fill('0');
	      off_depth_ << timestamp_depth_;
	      off_depth_ <<  " " << depth_file_PNG << std::endl;
        
        off_ir_.width(18);
	      off_ir_.fill('0');
	      off_ir_ << timestamp_ir_;
	      off_ir_ <<  " " << ir_file_PNG << std::endl;
	  }