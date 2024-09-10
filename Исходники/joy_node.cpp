    ///\brief Opens joystick port, reads from port and publishes while node is active
    int main(int argc, char **argv)
    {
        diagnostic_.add("Joystick Driver Status", this, &Joystick::diagnostics);
        diagnostic_.setHardwareID("none");

        // Parameters
        ros::NodeHandle nh_param("~");
        pub_ = nh_.advertise<sensor_msgs::Joy>("joy", 1);
        nh_param.getParam("dev", joy_dev_);
        nh_param.param<double>("deadzone", deadzone_, 0.05);
        nh_param.param<double>("autorepeat_rate", autorepeat_rate_, 0);
        nh_param.param<double>("coalesce_interval", coalesce_interval_, 0.001);

        // Checks on parameters
        if (autorepeat_rate_ > 1 / coalesce_interval_)
            ROS_WARN("joy_node: autorepeat_rate (%f Hz) > 1/coalesce_interval (%f Hz) does not make sense. Timing behavior is not well defined.", autorepeat_rate_, 1/coalesce_interval_);

        if (deadzone_ >= 1)
        {
            ROS_WARN("joy_node: deadzone greater than 1 was requested. The semantics of deadzone have changed. It is now related to the range [-1:1] instead of [-32767:32767]. For now I am dividing your deadzone by 32767, but this behavior is deprecated so you need to update your launch file.");
            deadzone_ /= 32767;
        }

        if (deadzone_ > 0.9)
        {
            ROS_WARN("joy_node: deadzone (%f) greater than 0.9, setting it to 0.9", deadzone_);
            deadzone_ = 0.9;
        }

        if (deadzone_ < 0)
        {
            ROS_WARN("joy_node: deadzone_ (%f) less than 0, setting to 0.", deadzone_);
            deadzone_ = 0;
        }

        if (autorepeat_rate_ < 0)
        {
            ROS_WARN("joy_node: autorepeat_rate (%f) less than 0, setting to 0.", autorepeat_rate_);
            autorepeat_rate_ = 0;
        }

        if (coalesce_interval_ < 0)
        {
            ROS_WARN("joy_node: coalesce_interval (%f) less than 0, setting to 0.", coalesce_interval_);
            coalesce_interval_ = 0;
        }

        // Parameter conversions
        double autorepeat_interval = 1 / autorepeat_rate_;
        double scale = -1. / (1. - deadzone_) / 32767.;
        double unscaled_deadzone = 32767. * deadzone_;

        js_event event;
        struct timeval tv;
        fd_set set;
        int joy_fd;
        event_count_ = 0;
        pub_count_ = 0;
        lastDiagTime_ = ros::Time::now().toSec();

        // Big while loop opens, publishes
        while (nh_.ok())
        {
            open_ = false;
            diagnostic_.force_update();
            bool first_fault = true;
            while (true)
            {
                ros::spinOnce();
                if (!nh_.ok())
                    goto cleanup;
                joy_fd = open(joy_dev_.c_str(), O_RDONLY);
                if (joy_fd != -1)
                {
                    // There seems to be a bug in the driver or something where the
                    // initial events that are to define the initial state of the
                    // joystick are not the values of the joystick when it was opened
                    // but rather the values of the joystick when it was last closed.
                    // Opening then closing and opening again is a hack to get more
                    // accurate initial state data.
                    close(joy_fd);
                    joy_fd = open(joy_dev_.c_str(), O_RDONLY);
                }
                if (joy_fd != -1)
                    break;
                if (first_fault)
                {
                    ROS_ERROR("Couldn't open joystick %s. Will retry every second.", joy_dev_.c_str());
                    first_fault = false;
                }
                sleep(1.0);
                diagnostic_.update();
            }

            ROS_INFO("Opened joystick: %s. deadzone_: %f.", joy_dev_.c_str(), deadzone_);
            open_ = true;
            diagnostic_.force_update();

            bool tv_set = false;
            bool publication_pending = false;
            tv.tv_sec = 1;
            tv.tv_usec = 0;
            sensor_msgs::Joy joy_msg; // Here because we want to reset it on device close.
            while (nh_.ok())
            {
                ros::spinOnce();

                bool publish_now = false;
                bool publish_soon = false;
                FD_ZERO(&set);
                FD_SET(joy_fd, &set);

                //ROS_INFO("Select...");
                int select_out = select(joy_fd+1, &set, NULL, NULL, &tv);
                //ROS_INFO("Tick...");
                if (select_out == -1)
                {
                    tv.tv_sec = 0;
                    tv.tv_usec = 0;
                    //ROS_INFO("Select returned negative. %i", ros::isShuttingDown());
                    continue;
                    //				break; // Joystick is probably closed. Not sure if this case is useful.
                }

                if (FD_ISSET(joy_fd, &set))
                {
                    if (read(joy_fd, &event, sizeof(js_event)) == -1 && errno != EAGAIN)
                        break; // Joystick is probably closed. Definitely occurs.

                    //ROS_INFO("Read data...");
                    joy_msg.header.stamp = ros::Time().now();
                    event_count_++;
                    switch(event.type)
                    {
                    case JS_EVENT_BUTTON:
                    case JS_EVENT_BUTTON | JS_EVENT_INIT:
                        if(event.number >= joy_msg.buttons.size())
                        {
                            int old_size = joy_msg.buttons.size();
                            joy_msg.buttons.resize(event.number+1);
                            for(unsigned int i=old_size; i<joy_msg.buttons.size(); i++)
                                joy_msg.buttons[i] = 0.0;
                        }
                        joy_msg.buttons[event.number] = (event.value ? 1 : 0);
                        // For initial events, wait a bit before sending to try to catch
                        // all the initial events.
                        if (!(event.type & JS_EVENT_INIT))
                            publish_now = true;
                        else
                            publish_soon = true;
                        break;
                    case JS_EVENT_AXIS:
                    case JS_EVENT_AXIS | JS_EVENT_INIT:
                        if(event.number >= joy_msg.axes.size())
                        {
                            int old_size = joy_msg.axes.size();
                            joy_msg.axes.resize(event.number+1);
                            for(unsigned int i=old_size; i<joy_msg.axes.size(); i++)
                                joy_msg.axes[i] = 0.0;
                        }
                        if (!(event.type & JS_EVENT_INIT)) // Init event.value is wrong.
                        {
                            double val = event.value;
                            // Allows deadzone to be "smooth"
                            if (val > unscaled_deadzone)
                                val -= unscaled_deadzone;
                            else if (val < -unscaled_deadzone)
                                val += unscaled_deadzone;
                            else
                                val = 0;
                            joy_msg.axes[event.number] = val * scale;
                        }
                        // Will wait a bit before sending to try to combine events.
                        publish_soon = true;
                        break;
                    default:
                        ROS_WARN("joy_node: Unknown event type. Please file a ticket. time=%u, value=%d, type=%Xh, number=%d", event.time, event.value, event.type, event.number);
                        break;
                    }
                }
                else if (tv_set) // Assume that the timer has expired.
                    publish_now = true;

                if (publish_now)
                {
                    // Assume that all the JS_EVENT_INIT messages have arrived already.
                    // This should be the case as the kernel sends them along as soon as
                    // the device opens.
                    //ROS_INFO("Publish...");
                    pub_.publish(joy_msg);
                    publish_now = false;
                    tv_set = false;
                    publication_pending = false;
                    publish_soon = false;
                    pub_count_++;
                }

                // If an axis event occurred, start a timer to combine with other
                // events.
                if (!publication_pending && publish_soon)
                {
                    tv.tv_sec = trunc(coalesce_interval_);
                    tv.tv_usec = (coalesce_interval_ - tv.tv_sec) * 1e6;
                    publication_pending = true;
                    tv_set = true;
                    //ROS_INFO("Pub pending...");
                }

                // If nothing is going on, start a timer to do autorepeat.
                if (!tv_set && autorepeat_rate_ > 0)
                {
                    tv.tv_sec = trunc(autorepeat_interval);
                    tv.tv_usec = (autorepeat_interval - tv.tv_sec) * 1e6;
                    tv_set = true;
                    //ROS_INFO("Autorepeat pending... %i %i", tv.tv_sec, tv.tv_usec);
                }

                if (!tv_set)
                {
                    tv.tv_sec = 1;
                    tv.tv_usec = 0;
                }

                diagnostic_.update();
            } // End of joystick open loop.

            close(joy_fd);
            ros::spinOnce();
            if (nh_.ok())
                ROS_ERROR("Connection to joystick device lost unexpectedly. Will reopen.");
        }

cleanup:
        ROS_INFO("joy_node shut down.");

        return 0;
    }