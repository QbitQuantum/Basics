void URPCFault::encode(UString& response)
{
   U_TRACE(0, "URPCFault::encode(%V)", response.rep)

   UString code = getFaultCode();

   response.setBuffer(100U + code.size() + faultReason.size() + detail.size());

   response.snprintf(U_CONSTANT_TO_PARAM("%v: %v%s%v"), code.rep, faultReason.rep, (detail.empty() ? "" : " - "), detail.rep);
}