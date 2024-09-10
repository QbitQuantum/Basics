/**
 * main
 */
int main(int argc, const char **argv)
{
    // Our main data storage vessel..
    RASPIVID_STATE state;

    MMAL_STATUS_T status = -1;
    MMAL_PORT_T *camera_video_port = NULL;
    MMAL_PORT_T *camera_still_port = NULL;
    MMAL_PORT_T *preview_input_port = NULL;
    MMAL_PORT_T *encoder_input_port = NULL;
    MMAL_PORT_T *encoder_output_port = NULL;

    time_t timer_begin,timer_end;
    double secondsElapsed;

    bcm_host_init();
    signal(SIGINT, signal_handler);

    // read default status
    default_status(&state);

    // init windows and OpenCV Stuff
    cvNamedWindow("camcvWin", CV_WINDOW_AUTOSIZE);
    int w=state.width;
    int h=state.height;
    dstImage = cvCreateImage(cvSize(w,h), IPL_DEPTH_8U, 3);
    py = cvCreateImage(cvSize(w,h), IPL_DEPTH_8U, 1);		// Y component of YUV I420 frame
    pu = cvCreateImage(cvSize(w/2,h/2), IPL_DEPTH_8U, 1);	// U component of YUV I420 frame
    pv = cvCreateImage(cvSize(w/2,h/2), IPL_DEPTH_8U, 1);	// V component of YUV I420 frame
    pu_big = cvCreateImage(cvSize(w,h), IPL_DEPTH_8U, 1);
    pv_big = cvCreateImage(cvSize(w,h), IPL_DEPTH_8U, 1);
    image = cvCreateImage(cvSize(w,h), IPL_DEPTH_8U, 3);	// final picture to display


    // create camera
    if (!create_camera_component(&state))
    {
        vcos_log_error("%s: Failed to create camera component", __func__);
    }
// AZG(20160226): Debug
    else if ((status = raspipreview_create(&state.preview_parameters)) != MMAL_SUCCESS)
    {
        vcos_log_error("%s: Failed to create preview component", __func__);
        destroy_camera_component(&state);
    }
    else
    {
        PORT_USERDATA callback_data;

        camera_video_port   = state.camera_component->output[MMAL_CAMERA_VIDEO_PORT];
        camera_still_port   = state.camera_component->output[MMAL_CAMERA_CAPTURE_PORT];

        VCOS_STATUS_T vcos_status;

        callback_data.pstate = &state;

        vcos_status = vcos_semaphore_create(&callback_data.complete_semaphore, "RaspiStill-sem", 0);
        vcos_assert(vcos_status == VCOS_SUCCESS);

        // assign data to use for callback
        camera_video_port->userdata = (struct MMAL_PORT_USERDATA_T *)&callback_data;

        // init timer
        time(&timer_begin);


        // start capture
        if (mmal_port_parameter_set_boolean(camera_video_port, MMAL_PARAMETER_CAPTURE, 1) != MMAL_SUCCESS)
        {
            goto error;
        }

        // Send all the buffers to the video port

        int num = mmal_queue_length(state.video_pool->queue);
        int q;
        for (q=0; q<num; q++)
        {
            MMAL_BUFFER_HEADER_T *buffer = mmal_queue_get(state.video_pool->queue);

            if (!buffer)
                vcos_log_error("Unable to get a required buffer %d from pool queue", q);

            if (mmal_port_send_buffer(camera_video_port, buffer)!= MMAL_SUCCESS)
                vcos_log_error("Unable to send a buffer to encoder output port (%d)", q);
        }


        // Now wait until we need to stop
        vcos_sleep(state.timeout);

error:

        mmal_status_to_int(status);


        // Disable all our ports that are not handled by connections
        check_disable_port(camera_still_port);

        if (state.camera_component)
            mmal_component_disable(state.camera_component);

        //destroy_encoder_component(&state);
        //	raspipreview_destroy(&state.preview_parameters);
        destroy_camera_component(&state);

    }
    if (status != 0)
        raspicamcontrol_check_configuration(128);

    time(&timer_end);  /* get current time; same as: timer = time(NULL)  */
    cvReleaseImage(&dstImage);
    cvReleaseImage(&pu);
    cvReleaseImage(&pv);
    cvReleaseImage(&py);
    cvReleaseImage(&pu_big);
    cvReleaseImage(&pv_big);

    secondsElapsed = difftime(timer_end,timer_begin);

    printf ("%.f seconds for %d frames : FPS = %f\n", secondsElapsed,nCount,(float)((float)(nCount)/secondsElapsed));

    return 0;
}