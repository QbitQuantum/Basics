    astra_status_t device_stream<TFrameWrapper>::on_open()
    {
        if (is_open())
            return astra_status_t::ASTRA_STATUS_SUCCESS;

        LOG_INFO("orbbec.mocks.device_stream",
                 "creating mock stream of type: %d",
                 description().type());

        LOG_INFO("orbbec.mocks.device_stream",
                 "created mock stream of type: %d",
                 description().type());

        LOG_INFO("orbbec.mocks.device_stream",
                 "stream type %d supports modes:",
                 description().type());

        for(auto it = deviceStream_->modes_begin();
            it != deviceStream_->modes_end(); ++it)
        {
            auto mode = *it;

            LOG_INFO("orbbec.mocks.device_stream", "mode: %ux%ux%u@%u pf:%u",
                     mode.width(),
                     mode.height(),
                     mode.bytesPerPixel(),
                     mode.fps(),
                     mode.pixelFormat());
        }

        set_mode(deviceStream_->active_mode());

        return astra_status_t::ASTRA_STATUS_SUCCESS;
    }