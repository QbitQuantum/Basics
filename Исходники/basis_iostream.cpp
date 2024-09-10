        void basis_iostream::handle_write(const boost::system::error_code& err,
                size_t bytes_transferred) {

            if (!err) {
                tmout_timer_.cancel();
                io_service_.stop();
                is_timout = false;
                is_error = false;
            }
            else {
                tmout_timer_.cancel();
                checkerror(err);
                error_cod = err.value();
                is_error = true;
                io_service_.stop();
                is_data_ready = false;
                DEBUG_STR_DVNCI(is errror handle_write!!!)
            }
        }