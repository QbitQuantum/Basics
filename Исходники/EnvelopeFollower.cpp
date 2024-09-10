void pdsp::EnvelopeFollower::prepareUnit( int expectedBufferSize, double sampleRate ){
    this->sampleRate = sampleRate;
    envelopeOutput = 0.0f;
    attackCoeff  = expf( TC / (50.0f * sampleRate * 0.001f) );
    releaseCoeff = expf( TC / (50.0f * sampleRate * 0.001f) );
}