// update updates the position and the orientation of the api sound
//
void APISound::update(const Vector& position, const Vector& front) {

    if (pSourceVoice) {
		X3DAUDIO_VECTOR eFront    = {front.x, front.y, front.z};
		X3DAUDIO_VECTOR ePosition = {position.x, position.y, position.z};
		
		Emitter.OrientFront = eFront;
		Emitter.Position    = ePosition;
		// What about Velocity (Doppler) and OrientTop (apparently only for multi-channel audio?)

		// X3DAudioCalculate() http://msdn.microsoft.com/en-us/library/microsoft.directx_sdk.x3daudio.x3daudiocalculate(v=VS.85).aspx
		X3DAudioCalculate(*pX3DInstance, pListener, &Emitter, X3DAUDIO_CALCULATE_MATRIX,
			&DSPSettings );

		pSourceVoice->SetVolume(volume);
		pSourceVoice->SetFrequencyRatio(frequencyRatio);
		pSourceVoice->SetOutputMatrix(pMasteringVoice, DSPSettings.SrcChannelCount, 
         DSPSettings.DstChannelCount, DSPSettings.pMatrixCoefficients);
	}
}