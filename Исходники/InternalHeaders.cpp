void
InternalHeaders::Fill(const Sequence<Sequence<nsCString>>& aInit, ErrorResult& aRv)
{
  for (uint32_t i = 0; i < aInit.Length() && !aRv.Failed(); ++i) {
    const Sequence<nsCString>& tuple = aInit[i];
    if (tuple.Length() != 2) {
      aRv.ThrowTypeError<MSG_INVALID_HEADER_SEQUENCE>();
      return;
    }
    Append(tuple[0], tuple[1], aRv);
  }
}