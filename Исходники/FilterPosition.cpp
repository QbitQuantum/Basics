//ACRE_RESULT CFilterPosition::process(short* samples, int sampleCount, int channels, CPlayer *player, const unsigned int* channelSpeakerArray, unsigned int *channelMask, ACRE_VOLUME volume) {
ACRE_RESULT CFilterPosition::process(short* samples, int sampleCount, int channels, const unsigned int speakerMask, CSoundMixdownEffect *params) {
    X3DAUDIO_LISTENER Listener = {};
    X3DAUDIO_EMITTER Emitter = {0};
    X3DAUDIO_DSP_SETTINGS DSPSettings = {0};
    X3DAUDIO_CONE emitterCone = {0};

    X3DAUDIO_VECTOR listener_position;
    X3DAUDIO_VECTOR speaker_position;
    X3DAUDIO_VECTOR vector_listenerDirection;
    X3DAUDIO_VECTOR vector_speakerDirection;
    
    //LOCK(player);
    //LOCK(CEngine::getInstance()->getSelf());
    float killCoef;
    float *Matrix = new float[1 * channels];

    //LOG("channels: %d", channels);
    if (!this->p_IsInitialized) {
        // we need to figure out what channel mask we want to use.
        /*
        unsigned int initSpeakers = channelSpeakerArray[0];
        LOG("Speaker 1: %d", channelSpeakerArray[0]);
        for (int i = 1; i < channels; i++) {
            LOG("Speaker %d: %d", i+1, channelSpeakerArray[i]);
            initSpeakers = initSpeakers | channelSpeakerArray[i];
        }
        */
        X3DAudioInitialize(speakerMask, X3DAUDIO_SPEED_OF_SOUND, this->p_X3DInstance);

        this->p_IsInitialized = TRUE;
    }
    
    if (CAcreSettings::getInstance()->getDisablePosition())
        return ACRE_OK;

    DSPSettings.SrcChannelCount = 1;
    DSPSettings.DstChannelCount = channels;
    DSPSettings.pMatrixCoefficients = Matrix;

    speaker_position.x = params->getParam("speakerPosX");
    speaker_position.y = params->getParam("speakerPosY");
    speaker_position.z = params->getParam("speakerPosZ");

    Emitter.Position = speaker_position;

    vector_speakerDirection.x = params->getParam("headVectorX");
    vector_speakerDirection.y = params->getParam("headVectorY");
    vector_speakerDirection.z = params->getParam("headVectorZ");

    Emitter.OrientFront = vector_speakerDirection;
    Emitter.OrientTop = this->getUpVector(vector_speakerDirection);
    Emitter.Velocity = X3DAUDIO_VECTOR( 0, 0, 0 );
    Emitter.ChannelCount = 1;

    if (params->getParam("isWorld") == POSITIONAL_EFFECT_ISWORLD) {
        listener_position.x = CEngine::getInstance()->getSelf()->getWorldPosition().x;
        listener_position.y = CEngine::getInstance()->getSelf()->getWorldPosition().y;
        listener_position.z = CEngine::getInstance()->getSelf()->getWorldPosition().z;


        vector_listenerDirection.x = CEngine::getInstance()->getSelf()->getHeadVector().x;
        vector_listenerDirection.y = CEngine::getInstance()->getSelf()->getHeadVector().y;
        vector_listenerDirection.z = CEngine::getInstance()->getSelf()->getHeadVector().z;

        if (params->getParam("speakingType") == ACRE_SPEAKING_DIRECT) {
            /*if(CEngine::getInstance()->getSoundEngine()->getCurveModel() == ACRE_CURVE_MODEL_AMPLITUDE) {
                Emitter.CurveDistanceScaler = (player->getAmplitudeCoef())*(CEngine::getInstance()->getSoundEngine()->getCurveScale());
                Emitter.pVolumeCurve = NULL;
            } else */
            if (CEngine::getInstance()->getSoundEngine()->getCurveModel() == ACRE_CURVE_MODEL_SELECTABLE_A) {
                Emitter.CurveDistanceScaler = 1.0f*(params->getParam("curveScale"));
                Emitter.pVolumeCurve = NULL;
            } else if (CEngine::getInstance()->getSoundEngine()->getCurveModel() == ACRE_CURVE_MODEL_SELECTABLE_B) {
                Emitter.CurveDistanceScaler = 1.0f*(params->getParam("curveScale"));
                Emitter.pVolumeCurve = (X3DAUDIO_DISTANCE_CURVE *)&distanceCurve;
            } else {
                Emitter.CurveDistanceScaler = 1.0f;
                Emitter.pVolumeCurve = NULL;
                //Emitter.pVolumeCurve = (X3DAUDIO_DISTANCE_CURVE *)&distanceCurve;
            }
        } else {
            Emitter.CurveDistanceScaler = 1.0f;
            Emitter.pVolumeCurve = (X3DAUDIO_DISTANCE_CURVE *)&distanceCurve;
        }
    } else {
        listener_position.x = 0.0f;
        listener_position.y = 0.0f;
        listener_position.z = 0.0f;


        vector_listenerDirection.x = 0.0f;
        vector_listenerDirection.y = 1.0f;
        vector_listenerDirection.z = 0.0f;

        Emitter.CurveDistanceScaler = 1.0f;
        Emitter.pVolumeCurve = (X3DAUDIO_DISTANCE_CURVE *)&distanceCurve;
    }
    
    Emitter.DopplerScaler = 1.0f;
    Emitter.ChannelRadius = 1.0f;

    emitterCone.InnerAngle = X3DAUDIO_PI/4;
    emitterCone.OuterAngle = X3DAUDIO_PI/2;
    emitterCone.InnerVolume = 1.2f;
    emitterCone.OuterVolume = 1.0f;

    Emitter.pCone = &emitterCone;
    //Listener.pCone = &emitterCone;

    
    

    Emitter.InnerRadius = 2.0f;
    Emitter.InnerRadiusAngle = X3DAUDIO_PI/4.0f;

    X3DAUDIO_VECTOR listener_topVec = this->getUpVector(vector_listenerDirection);

    //float listenerDot = vector_listenerDirection.x*listener_topVec.x + vector_listenerDirection.y*listener_topVec.y + vector_listenerDirection.z*listener_topVec.z;
    //TRACE("Listener Dot Product: %f", listenerDot);
    Listener.OrientFront = vector_listenerDirection;
    Listener.OrientTop = listener_topVec;
    Listener.Position = listener_position;
    
    //UNLOCK(CEngine::getInstance()->getSelf());
    //UNLOCK(player);
    

    X3DAudioCalculate(this->p_X3DInstance, &Listener, &Emitter,
    X3DAUDIO_CALCULATE_MATRIX | X3DAUDIO_CALCULATE_EMITTER_ANGLE,
    &DSPSettings );

    /*
    std::string matrixVals = std::string("");
    for (int i = 0; i < channels; i++) {
        char *mAppend;
        sprintf(mAppend, "%f, ", Matrix[i]);
        matrixVals.append(std::string(mAppend));
    }
    
    TRACE("MATRIX: %s", matrixVals.c_str());
    */
    TRACE("matrix: c:[%d], %f, %f, %f", channels, Matrix[0], Matrix[1], (Matrix[0] + Matrix[1]));// +Matrix[2] + Matrix[3] + Matrix[4] + Matrix[5]));
    /*
    LOG("Positions: d:[%f], l:[%f,%f,%f] s:[%f,%f,%f]",
        DSPSettings.EmitterToListenerDistance,
        Listener.Position.x,
        Listener.Position.y,
        Listener.Position.z,
        Emitter.Position.x,
        Emitter.Position.y,
        Emitter.Position.z
        );
    */


    if (CEngine::getInstance()->getSoundEngine()->getCurveModel() == ACRE_CURVE_MODEL_AMPLITUDE || CEngine::getInstance()->getSoundEngine()->getCurveModel() == ACRE_CURVE_MODEL_SELECTABLE_A) {
        killCoef = std::max(0.0f,(1-((DSPSettings.EmitterToListenerDistance-(MAX_FALLOFF_DISTANCE))/MAX_FALLOFF_RANGE)));

        if (DSPSettings.EmitterToListenerDistance < (MAX_FALLOFF_DISTANCE)) {
            killCoef = 1;
        }
        killCoef = std::min(1.0f, killCoef);
    } else {
        killCoef = 1;
    };
    //LOG("dis: %f kc: %f ac: %f", DSPSettings.EmitterToListenerDistance, killCoef, this->getPlayer()->getAmplitudeCoef());
    for (int x = 0; x < sampleCount * channels; x+=channels) {
        for (int i = 0; i < channels; i++) {
            samples[x+i] = (short)(samples[x+i] * Matrix[i] * killCoef);
        }
    }

    if (Matrix)
        delete Matrix;

    return ACRE_OK;
}