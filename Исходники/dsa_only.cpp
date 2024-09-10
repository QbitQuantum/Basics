		void shutdown(){
		    timer_dsa.stop();
		    timer_publish.stop();
		    timer_diag.stop();
		    nh_.shutdown();
		}