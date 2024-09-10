const char*
WMFDecoderDllNameFor(CodecType aCodec)
{
  if (aCodec == H264) {
    // For H.264 decoding, we need msmpeg2vdec.dll on Win 7 & 8,
    // and mfh264dec.dll on Vista.
    if (IsWindows7OrGreater()) {
      return "msmpeg2vdec.dll";
    } else {
      return "mfh264dec.dll";
    }
  } else if (aCodec == AAC) {
    // For AAC decoding, we need to use msauddecmft.dll on Win8,
    // msmpeg2adec.dll on Win7, and msheaacdec.dll on Vista.
    if (IsWindows8OrGreater()) {
      return "msauddecmft.dll";
    } else if (IsWindows7OrGreater()) {
      return "msmpeg2adec.dll";
    } else {
      return "mfheaacdec.dll";
    }
  } else {
    return "";
  }
}