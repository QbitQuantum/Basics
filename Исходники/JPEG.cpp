 // Handles exit on errors.
 void ErrorExit(j_common_ptr cinfo)
 {
     struct InputSource* inputSource = (struct InputSource*)(cinfo->client_data);
     longjmp(inputSource->mErrorManager.mSetJumpBuffer, 1);
 }