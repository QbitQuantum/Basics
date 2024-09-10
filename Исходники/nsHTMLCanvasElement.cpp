nsresult
nsHTMLCanvasElement::ToDataURLImpl(const nsAString& aMimeType,
                                   nsIVariant* aEncoderOptions,
                                   nsAString& aDataURL)
{
  bool fallbackToPNG = false;

  nsIntSize size = GetWidthHeight();
  if (size.height == 0 || size.width == 0) {
    aDataURL = NS_LITERAL_STRING("data:,");
    return NS_OK;
  }

  nsAutoString type;
  nsContentUtils::ASCIIToLower(aMimeType, type);

  nsAutoString params;

  // Quality parameter is only valid for the image/jpeg MIME type
  if (type.EqualsLiteral("image/jpeg")) {
    PRUint16 vartype;

    if (aEncoderOptions &&
        NS_SUCCEEDED(aEncoderOptions->GetDataType(&vartype)) &&
        vartype <= nsIDataType::VTYPE_DOUBLE) {

      double quality;
      // Quality must be between 0.0 and 1.0, inclusive
      if (NS_SUCCEEDED(aEncoderOptions->GetAsDouble(&quality)) &&
          quality >= 0.0 && quality <= 1.0) {
        params.AppendLiteral("quality=");
        params.AppendInt(NS_lround(quality * 100.0));
      }
    }
  }

  // If we haven't parsed the params check for proprietary options.
  // The proprietary option -moz-parse-options will take a image lib encoder
  // parse options string as is and pass it to the encoder.
  bool usingCustomParseOptions = false;
  if (params.Length() == 0) {
    NS_NAMED_LITERAL_STRING(mozParseOptions, "-moz-parse-options:");
    nsAutoString paramString;
    if (NS_SUCCEEDED(aEncoderOptions->GetAsAString(paramString)) && 
        StringBeginsWith(paramString, mozParseOptions)) {
      nsDependentSubstring parseOptions = Substring(paramString, 
                                                    mozParseOptions.Length(), 
                                                    paramString.Length() - 
                                                    mozParseOptions.Length());
      params.Append(parseOptions);
      usingCustomParseOptions = true;
    }
  }

  nsCOMPtr<nsIInputStream> stream;
  nsresult rv = ExtractData(type, params, getter_AddRefs(stream),
                            fallbackToPNG);

  // If there are unrecognized custom parse options, we should fall back to 
  // the default values for the encoder without any options at all.
  if (rv == NS_ERROR_INVALID_ARG && usingCustomParseOptions) {
    fallbackToPNG = false;
    rv = ExtractData(type, EmptyString(), getter_AddRefs(stream), fallbackToPNG);
  }

  NS_ENSURE_SUCCESS(rv, rv);

  // build data URL string
  if (fallbackToPNG)
    aDataURL = NS_LITERAL_STRING("data:image/png;base64,");
  else
    aDataURL = NS_LITERAL_STRING("data:") + type +
      NS_LITERAL_STRING(";base64,");

  PRUint32 count;
  rv = stream->Available(&count);
  NS_ENSURE_SUCCESS(rv, rv);

  return Base64EncodeInputStream(stream, aDataURL, count, aDataURL.Length());
}