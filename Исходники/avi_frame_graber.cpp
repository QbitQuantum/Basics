		void AviFrameGraber::_Close(void){
			_status=FRAME_SUBJECT_STOP;
			//! \todo test 
			//!  \todo set timeout time as a variable instead const
			WaitForSingleObject(thread_handle_,1000);
			if (thread_handle_!=NULL){
				thread_handle_=NULL;
			}
			if(frame_!=NULL){
				AVIStreamGetFrameClose(frame_);
				frame_ = NULL;
			}
			if (stream_!=NULL){
				AVIStreamRelease(stream_);
				stream_=NULL;
			}
			if(avi_file_!=NULL){
				AVIFileRelease(avi_file_);
				avi_file_=NULL;
			}
		}