//-----------------------------------------------------------------------------------------
void tf3Synth::processReplacing (eF32 **inputs, eF32 **outputs, long sampleFrames)
{
	memset (outputs[0], 0, sampleFrames * sizeof (eF32));
	memset (outputs[1], 0, sampleFrames * sizeof (eF32));
	process (inputs, outputs, sampleFrames);
}