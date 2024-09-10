        void error(const char *error_string, const char *file, const int line, const char *func)
        {          
            int code = CV_GpuApiCallError;

            if (uncaught_exception())
            {
                const char* errorStr = cvErrorStr(code);            
                const char* function = func ? func : "unknown function";    

                cerr << "OpenCV Error: " << errorStr << "(" << error_string << ") in " << function << ", file " << file << ", line " << line;
                cerr.flush();            
            }
            else    
                cv::error( cv::Exception(code, error_string, func, file, line) );
        }