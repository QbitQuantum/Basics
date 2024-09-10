    void AudioWorld::simulate()
    {
        if (!mainListener_)
        {
            std::fill(std::begin(levelMatrix_), std::end(levelMatrix_), 0.0f);
            for (const auto& e : emitters_)
            {
                e->voice->applyFrequencyRatio(1);
                e->voice->applyOutputMatrix(deviceDetails_.numSrcCannels, deviceDetails_.numDestCannels, levelMatrix_.data());
            }
            return;
        }

        X3DAUDIO_LISTENER listenerParam;
        ZeroMemory(&listenerParam, sizeof(listenerParam));
        listenerParam.OrientFront = toX3DAudioVector(mainListener_->orientation * Vector3::UNIT_Z);
        listenerParam.OrientTop = toX3DAudioVector(mainListener_->orientation * Vector3::UNIT_Y);
        listenerParam.Position = toX3DAudioVector(mainListener_->position);
        listenerParam.Velocity = toX3DAudioVector(mainListener_->velocity);

        X3DAUDIO_EMITTER emitterParam;
        ZeroMemory(&emitterParam, sizeof(emitterParam));

        /// TODO:
        emitterParam.InnerRadius = 30;
        emitterParam.ChannelCount = 1;
        emitterParam.pVolumeCurve = const_cast<X3DAUDIO_DISTANCE_CURVE*>(&X3DAudioDefault_LinearCurve);
        emitterParam.CurveDistanceScaler = 500;
        emitterParam.DopplerScaler = 1;

        for (const auto& e : emitters_)
        {
            emitterParam.OrientFront = toX3DAudioVector(e->orientation * Vector3::UNIT_Z);
            emitterParam.OrientTop = toX3DAudioVector(e->orientation * Vector3::UNIT_Y);
            emitterParam.Position = toX3DAudioVector(e->position);
            emitterParam.Velocity = toX3DAudioVector(e->velocity);

            X3DAUDIO_DSP_SETTINGS dsp;
            dsp.pMatrixCoefficients = levelMatrix_.data();
            dsp.pDelayTimes = NULL;
            dsp.SrcChannelCount = deviceDetails_.numSrcCannels;
            dsp.DstChannelCount = deviceDetails_.numDestCannels;

            X3DAudioCalculate(x3DAudio_, &listenerParam, &emitterParam, X3DAUDIO_CALCULATE_MATRIX | X3DAUDIO_CALCULATE_DOPPLER, &dsp);

            e->voice->applyFrequencyRatio(dsp.DopplerFactor);
            e->voice->applyOutputMatrix(deviceDetails_.numSrcCannels, deviceDetails_.numDestCannels, levelMatrix_.data());
        }
    }