nsresult nsIDNService::stringPrepAndACE(const nsAString& in, nsACString& out,
                                        bool allowUnassigned,
                                        bool convertAllLabels)
{
  nsresult rv = NS_OK;

  out.Truncate();

  if (in.Length() > kMaxDNSNodeLen) {
    NS_WARNING("IDN node too large");
    return NS_ERROR_FAILURE;
  }

  if (IsASCII(in))
    LossyCopyUTF16toASCII(in, out);
  else if (!convertAllLabels && isLabelSafe(in))
    CopyUTF16toUTF8(in, out);
  else {
    nsAutoString strPrep;
    rv = stringPrep(in, strPrep, allowUnassigned);
    if (NS_SUCCEEDED(rv)) {
      if (IsASCII(strPrep))
        LossyCopyUTF16toASCII(strPrep, out);
      else
        rv = encodeToACE(strPrep, out);
    }
  }

  if (out.Length() > kMaxDNSNodeLen) {
    NS_WARNING("IDN node too large");
    return NS_ERROR_FAILURE;
  }

  return rv;
}