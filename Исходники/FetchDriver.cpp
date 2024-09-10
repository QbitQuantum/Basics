void
FetchDriver::SetRequestHeaders(nsIHttpChannel* aChannel) const
{
  MOZ_ASSERT(aChannel);

  AutoTArray<InternalHeaders::Entry, 5> headers;
  mRequest->Headers()->GetEntries(headers);
  bool hasAccept = false;
  for (uint32_t i = 0; i < headers.Length(); ++i) {
    if (!hasAccept && headers[i].mName.EqualsLiteral("accept")) {
      hasAccept = true;
    }
    if (headers[i].mValue.IsEmpty()) {
      aChannel->SetEmptyRequestHeader(headers[i].mName);
    } else {
      aChannel->SetRequestHeader(headers[i].mName, headers[i].mValue, false /* merge */);
    }
  }

  if (!hasAccept) {
    aChannel->SetRequestHeader(NS_LITERAL_CSTRING("accept"),
                               NS_LITERAL_CSTRING("*/*"),
                               false /* merge */);
  }

  if (mRequest->ForceOriginHeader()) {
    nsAutoString origin;
    if (NS_SUCCEEDED(nsContentUtils::GetUTFOrigin(mPrincipal, origin))) {
      aChannel->SetRequestHeader(NS_LITERAL_CSTRING("origin"),
                                 NS_ConvertUTF16toUTF8(origin),
                                 false /* merge */);
    }
  }
}