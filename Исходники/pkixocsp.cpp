// ResponseData ::= SEQUENCE {
//    version             [0] EXPLICIT Version DEFAULT v1,
//    responderID             ResponderID,
//    producedAt              GeneralizedTime,
//    responses               SEQUENCE OF SingleResponse,
//    responseExtensions  [1] EXPLICIT Extensions OPTIONAL }
static inline Result
ResponseData(Reader& input, Context& context,
             const SignedDataWithSignature& signedResponseData,
             const DERArray& certs)
{
  der::Version version;
  Result rv = der::OptionalVersion(input, version);
  if (rv != Success) {
    return rv;
  }
  if (version != der::Version::v1) {
    // TODO: more specific error code for bad version?
    return Result::ERROR_BAD_DER;
  }

  // ResponderID ::= CHOICE {
  //    byName              [1] Name,
  //    byKey               [2] KeyHash }
  Input responderID;
  ResponderIDType responderIDType
    = input.Peek(static_cast<uint8_t>(ResponderIDType::byName))
    ? ResponderIDType::byName
    : ResponderIDType::byKey;
  rv = der::ExpectTagAndGetValue(input, static_cast<uint8_t>(responderIDType),
                                 responderID);
  if (rv != Success) {
    return rv;
  }

  // This is the soonest we can verify the signature. We verify the signature
  // right away to follow the principal of minimizing the processing of data
  // before verifying its signature.
  rv = VerifySignature(context, responderIDType, responderID, certs,
                       signedResponseData);
  if (rv != Success) {
    return rv;
  }

  // TODO: Do we even need to parse this? Should we just skip it?
  Time producedAt(Time::uninitialized);
  rv = der::GeneralizedTime(input, producedAt);
  if (rv != Success) {
    return rv;
  }

  // We don't accept an empty sequence of responses. In practice, a legit OCSP
  // responder will never return an empty response, and handling the case of an
  // empty response makes things unnecessarily complicated.
  rv = der::NestedOf(input, der::SEQUENCE, der::SEQUENCE,
                     der::EmptyAllowed::No,
                     bind(SingleResponse, _1, ref(context)));
  if (rv != Success) {
    return rv;
  }

  return der::OptionalExtensions(input,
                                 der::CONTEXT_SPECIFIC | der::CONSTRUCTED | 1,
                                 ExtensionNotUnderstood);
}