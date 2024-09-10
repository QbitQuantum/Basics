 void _finishHash(BYTE* digest) {
     LOG_IF_NTSTATUS_FAILED(BCryptFinishHash(_hHash, digest, _digestLength, 0));
 }