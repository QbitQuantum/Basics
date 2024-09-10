/* nsILDAPBERValue flatten (); */
NS_IMETHODIMP nsLDAPBERElement::GetAsValue(nsILDAPBERValue **_retval) {
  // create the value object
  nsCOMPtr<nsILDAPBERValue> berValue = new nsLDAPBERValue();

  if (!berValue) {
    NS_ERROR(
        "nsLDAPBERElement::GetAsValue(): out of memory"
        " creating nsLDAPBERValue object");
    return NS_ERROR_OUT_OF_MEMORY;
  }

  struct berval *bv;
  if (ber_flatten(mElement, &bv) < 0) {
    return NS_ERROR_OUT_OF_MEMORY;
  }

  nsresult rv =
      berValue->Set(bv->bv_len, reinterpret_cast<uint8_t *>(bv->bv_val));

  // whether or not we've succeeded, we're done with the ldap c sdk struct
  ber_bvfree(bv);

  // as of this writing, this error can only be NS_ERROR_OUT_OF_MEMORY
  if (NS_FAILED(rv)) {
    return rv;
  }

  // return the raw interface pointer
  NS_ADDREF(*_retval = berValue.get());

  return NS_OK;
}