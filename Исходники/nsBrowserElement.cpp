void
nsBrowserElement::SendTouchEvent(const nsAString& aType,
                                 const Sequence<uint32_t>& aIdentifiers,
                                 const Sequence<int32_t>& aXs,
                                 const Sequence<int32_t>& aYs,
                                 const Sequence<uint32_t>& aRxs,
                                 const Sequence<uint32_t>& aRys,
                                 const Sequence<float>& aRotationAngles,
                                 const Sequence<float>& aForces,
                                 uint32_t aCount,
                                 uint32_t aModifiers,
                                 ErrorResult& aRv)
{
  NS_ENSURE_TRUE_VOID(IsBrowserElementOrThrow(aRv));
  NS_ENSURE_TRUE_VOID(IsNotWidgetOrThrow(aRv));

  if (aIdentifiers.Length() != aCount ||
      aXs.Length() != aCount ||
      aYs.Length() != aCount ||
      aRxs.Length() != aCount ||
      aRys.Length() != aCount ||
      aRotationAngles.Length() != aCount ||
      aForces.Length() != aCount) {
    aRv.Throw(NS_ERROR_DOM_INVALID_ACCESS_ERR);
    return;
  }

  nsresult rv = mBrowserElementAPI->SendTouchEvent(aType,
                                                   aIdentifiers.Elements(),
                                                   aXs.Elements(),
                                                   aYs.Elements(),
                                                   aRxs.Elements(),
                                                   aRys.Elements(),
                                                   aRotationAngles.Elements(),
                                                   aForces.Elements(),
                                                   aCount,
                                                   aModifiers);

  if (NS_WARN_IF(NS_FAILED(rv))) {
    aRv.Throw(NS_ERROR_DOM_INVALID_STATE_ERR);
  }
}