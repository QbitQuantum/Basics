void EnvelopeGen::OnProcess(int voiceID, Synth* synth)
{
    EnvelopeGenVoiceData &data = mVoiceData[voiceID];

    Frame<SampleType> &output = mOutputs[0].frame;

    if (data.postRelease)
    {
        // release envelope
        for (size_t i = 0; i < synth->GetFrameSize(); i++)
        {
            output[i] = data.releaseVolume * Exp(-data.time * mReleaseInv);
            data.time += synth->GetSampleRateInv();
        }
    }
    else
    {
        for (size_t i = 0; i < synth->GetFrameSize(); i++)
        {
            if (data.time < mAttack) // attack envelope
                output[i] = 0.5 - 0.5 * Cos(data.time * mAttackInv * M_PI);
            else if (data.time > 0.0)
                output[i] = mSustain + (1.0f - mSustain) * Exp(-(data.time - mAttack) * mDecayInv);
            else
                output[i] = 0.0;

            data.time += synth->GetSampleRateInv();
        }

        data.lastValue = output[synth->GetFrameSize() - 1];
    }
}