void rescale_image_to_fit(Buffer* input, Buffer* output, bool doFlip) {

  const Dimensions inputDims = input->_dims;
  const int inputWidth = inputDims[1];
  const int inputHeight = inputDims[0];
  const int inputChannels = inputDims[2];

  const Dimensions outputDims = output->_dims;
  const int outputWidth = outputDims[1];
  const int outputHeight = outputDims[0];
  const int outputChannels = outputDims[2];

  if ((inputDims == outputDims) && !doFlip) {
    const int elementCount = inputDims.elementCount();
    const size_t bytesInBuffer = (elementCount * sizeof(jpfloat_t));
    memcpy(output->_data, input->_data, bytesInBuffer);
    return;
  }

  const float flipBias = (doFlip) ? inputHeight : 0.0f;
  const float flipScale = (doFlip) ? -1.0f : 1.0f;

  const float scaleX = (inputWidth / (jpfloat_t)(outputWidth));
  const float scaleY = (flipScale * (inputHeight / (jpfloat_t)(outputHeight)));
  const int channelsToWrite = MIN(outputChannels, inputChannels);

  const Dimensions inputRowDims = inputDims.removeDimensions(1);
  const Dimensions outputRowDims = outputDims.removeDimensions(1);

  const jpfloat_t* inputDataStart = input->_data;
  jpfloat_t* const outputDataStart = output->_data;

  for (int outputY = 0; outputY < outputHeight; outputY += 1) {
    const jpfloat_t inputY = (flipBias + (outputY * scaleY));
    const int indexY0 = fmaxf(0.0f, fminf((inputHeight - 1.0f), floorf(inputY)));
    const int indexY1 = fmaxf(0.0f, fminf((inputHeight - 1.0f), ceilf(inputY)));
    const jpfloat_t lerpY = (indexY1 - inputY);
    const jpfloat_t oneMinusLerpY = (1.0f - lerpY);

    const int inputRowY0Offset = inputDims.offset(indexY0, 0, 0);
    const jpfloat_t* const inputRowY0 = (inputDataStart + inputRowY0Offset);
    const int inputRowY1Offset = inputDims.offset(indexY1, 0, 0);
    const jpfloat_t* const inputRowY1 = (inputDataStart + inputRowY1Offset);
    const int outputRowOffset = outputDims.offset(outputY, 0, 0);
    jpfloat_t* const outputRow = (outputDataStart + outputRowOffset);

    for (int outputX = 0; outputX < outputWidth; outputX += 1) {
      const jpfloat_t inputX = (outputX * scaleX);
      const int indexX0 = fmaxf(0.0f, floorf(inputX));
      const int indexX1 = fminf((inputWidth - 1.0f), ceilf(inputX));
      const jpfloat_t lerpX = (indexX1 - inputX);
      const jpfloat_t oneMinusLerpX = (1.0f - lerpX);

      const int indexX0Offset = inputRowDims.offset(indexX0, 0);
      const int indexX1Offset = inputRowDims.offset(indexX1, 0);

      const jpfloat_t* const input00Base = (inputRowY0 + indexX0Offset);
      const jpfloat_t* const input01Base = (inputRowY0 + indexX1Offset);
      const jpfloat_t* const input10Base = (inputRowY1 + indexX0Offset);
      const jpfloat_t* const input11Base = (inputRowY1 + indexX1Offset);

      const int outputOffset = outputRowDims.offset(outputX, 0);
      jpfloat_t* const outputBase = (outputRow + outputOffset);

      for (int channel = 0; channel < outputChannels; channel += 1) {
        jpfloat_t* const outputLocation = (outputBase + channel);
        if (channel >= channelsToWrite) {
          *outputLocation = 0.0f;
        } else {
          const jpfloat_t* input00Location = (input00Base + channel);
          const jpfloat_t* input01Location = (input01Base + channel);
          const jpfloat_t* input10Location = (input10Base + channel);
          const jpfloat_t* input11Location = (input11Base + channel);

          const jpfloat_t input00 = (*input00Location);
          const jpfloat_t input01 = (*input01Location);
          const jpfloat_t input10 = (*input10Location);
          const jpfloat_t input11 = (*input11Location);

          const jpfloat_t yInterp0 = ((input00 * lerpY) + (input10 * oneMinusLerpY));
          const jpfloat_t yInterp1 = ((input01 * lerpY) + (input11 * oneMinusLerpY));
          const jpfloat_t interp = ((yInterp0 * lerpX) + (yInterp1 * oneMinusLerpX));
          *outputLocation = interp;
        }
      }

    }
  }
}