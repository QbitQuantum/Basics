void BitWizardWSDevice::opcMapPixelColors(const OPC::Message &msg, const Value &inst)
{
  /*
   * Parse one JSON mapping instruction, and copy any relevant parts of 'msg'
   * into our framebuffer. This looks for any mapping instructions that we
   * recognize:
   *
   *   [ OPC Channel, OPC Pixel, Pixel Color, DMX Channel ]
   */

  unsigned msgPixelCount = msg.length() / 3;

  if (inst.IsArray() && inst.Size() == 4) {
    // Map a range from an OPC channel to our framebuffer

    const Value &vChannel  = inst[0u];
    const Value &vFirstOPC = inst[1];
    const Value &vFirstOut = inst[2];
    const Value &vCount    = inst[3];


    if (vChannel.IsUint() && vFirstOPC.IsUint() && 
	vFirstOut.IsUint() && vCount.IsUint()) {
      unsigned channel  = vChannel.GetUint();
      unsigned firstOPC = vFirstOPC.GetUint();
      unsigned firstOut = vFirstOut.GetUint();
      unsigned count    = vCount.GetUint();
      

      if (channel != msg.channel) {
	return;
      }

      // Clamping, overflow-safe
      firstOPC = std::min<unsigned>(firstOPC, msgPixelCount);
      firstOut = std::min<unsigned>(firstOut, unsigned(NUM_PIXELS));
      count = std::min<unsigned>(count, msgPixelCount - firstOPC);
      count = std::min<unsigned>(count, NUM_PIXELS - firstOut);
      
      // Copy pixels
      const uint8_t *inPtr = msg.data + (firstOPC * 3);
      unsigned outIndex = firstOut;

      //std::cout  << "mapping " << count << " pixels at " << firstOut << "...\n";
      
      while (count--) {
	uint8_t *outPtr = fbPixel(outIndex++);
	outPtr[0] = inPtr[0];
	outPtr[1] = inPtr[1];
	outPtr[2] = inPtr[2];
	inPtr += 3;
	if (outIndex >= NUM_PIXELS) return;
      }
      
      return;
    }
  }

  if (inst.IsArray() && inst.Size() == 2) {
    // Constant value

    const Value &vValue = inst[0u];
    const Value &vDMXChannel = inst[1];

    if (vValue.IsUint() && vDMXChannel.IsUint()) {
      unsigned value = vValue.GetUint();
      unsigned dmxChannel = vDMXChannel.GetUint();

      //setChannel(dmxChannel, value);
      return;
    }
  }

  // Still haven't found a match?
  if (mVerbose) {
    rapidjson::GenericStringBuffer<rapidjson::UTF8<> > buffer;
    rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<> > > writer(buffer);
    inst.Accept(writer);
    std::clog << "Unsupported JSON mapping instruction: " << buffer.GetString() << "\n";
  }
}