void runAddingQuantizer(LADSPA_Handle instance, unsigned long sampleCount)
{
    Quantizer *q_instance = (Quantizer *) instance;

    // Get the input and output ports.  The convention in all of the plugins I've read has been to assign these to local variables, instead of 
    // accessing the instance struct members each time.
    LADSPA_Data *input = q_instance->inputPort, *output = q_instance->outputPort;

    // Get the gain for run_adding.  This is used by the macro!
    LADSPA_Data runAddingGain = q_instance->runAddingGain;

    // Calculate the step size from the input value.
    float stepSize = (*(q_instance->reductionFactor) >= Q_FACTOR_LOWER && *(q_instance->reductionFactor) <= Q_FACTOR_UPPER)
                     ? *(q_instance->reductionFactor) * FLOAT_STEP : Q_FACTOR_LOWER;
    
    // Calculation intermediate storage.
    int exponentContainer;
    float significand;

    // Performing the processing.
    for(int i = 0; i < sampleCount; i++)
    {
        significand = frexpf(input[i], &exponentContainer); // Extract the significand of the sample for quantization.
        significand = signum(significand) * floorf(fabs(significand)/stepSize + 0.5f) * stepSize; // Apply the quantization! 
        buffer_write(output[i], ldexpf(significand, exponentContainer)); // Reapply the exponent and write the quantized value.
    }
}