already_AddRefed<Promise>
AudioContext::DecodeAudioData(const ArrayBuffer& aBuffer,
                              const Optional<OwningNonNull<DecodeSuccessCallback> >& aSuccessCallback,
                              const Optional<OwningNonNull<DecodeErrorCallback> >& aFailureCallback)
{
  ErrorResult rv;
  nsCOMPtr<nsIGlobalObject> parentObject = do_QueryInterface(GetParentObject());
  nsRefPtr<Promise> promise;
  AutoJSAPI jsapi;
  jsapi.Init();
  JSContext* cx = jsapi.cx();
  JSAutoCompartment ac(cx, aBuffer.Obj());

  promise = Promise::Create(parentObject, rv);
  if (rv.Failed()) {
    return nullptr;
  }

  aBuffer.ComputeLengthAndData();

  // Neuter the array buffer
  size_t length = aBuffer.Length();
  JS::RootedObject obj(cx, aBuffer.Obj());

  uint8_t* data = static_cast<uint8_t*>(JS_StealArrayBufferContents(cx, obj));

  // Sniff the content of the media.
  // Failed type sniffing will be handled by AsyncDecodeMedia.
  nsAutoCString contentType;
  NS_SniffContent(NS_DATA_SNIFFER_CATEGORY, nullptr, data, length, contentType);

  nsRefPtr<DecodeErrorCallback> failureCallback;
  nsRefPtr<DecodeSuccessCallback> successCallback;
  if (aFailureCallback.WasPassed()) {
    failureCallback = &aFailureCallback.Value();
  }
  if (aSuccessCallback.WasPassed()) {
    successCallback = &aSuccessCallback.Value();
  }
  nsRefPtr<WebAudioDecodeJob> job(
    new WebAudioDecodeJob(contentType, this,
                          promise, successCallback, failureCallback));
  mDecoder.AsyncDecodeMedia(contentType.get(), data, length, *job);
  // Transfer the ownership to mDecodeJobs
  mDecodeJobs.AppendElement(job.forget());

  return promise.forget();
}