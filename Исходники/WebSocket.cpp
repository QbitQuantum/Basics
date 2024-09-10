already_AddRefed<WebSocket>
WebSocket::Constructor(JSContext* aCx,
                       nsISupports* aGlobal,
                       const nsAString& aUrl,
                       const Sequence<nsString>& aProtocols,
                       ErrorResult& aRv)
{
  if (!PrefEnabled()) {
    aRv.Throw(NS_ERROR_DOM_SECURITY_ERR);
    return nullptr;
  }

  nsCOMPtr<nsIScriptObjectPrincipal> scriptPrincipal = do_QueryInterface(aGlobal);
  if (!scriptPrincipal) {
    aRv.Throw(NS_ERROR_FAILURE);
    return nullptr;
  }

  nsCOMPtr<nsIPrincipal> principal = scriptPrincipal->GetPrincipal();
  if (!principal) {
    aRv.Throw(NS_ERROR_FAILURE);
    return nullptr;
  }

  nsCOMPtr<nsIScriptGlobalObject> sgo = do_QueryInterface(aGlobal);
  if (!sgo) {
    aRv.Throw(NS_ERROR_FAILURE);
    return nullptr;
  }

  nsCOMPtr<nsPIDOMWindow> ownerWindow = do_QueryInterface(aGlobal);
  if (!ownerWindow) {
    aRv.Throw(NS_ERROR_FAILURE);
    return nullptr;
  }

  nsTArray<nsString> protocolArray;

  for (uint32_t index = 0, len = aProtocols.Length(); index < len; ++index) {

    const nsString& protocolElement = aProtocols[index];

    if (protocolElement.IsEmpty()) {
      aRv.Throw(NS_ERROR_DOM_SYNTAX_ERR);
      return nullptr;
    }
    if (protocolArray.Contains(protocolElement)) {
      aRv.Throw(NS_ERROR_DOM_SYNTAX_ERR);
      return nullptr;
    }
    if (protocolElement.FindChar(',') != -1)  /* interferes w/list */ {
      aRv.Throw(NS_ERROR_DOM_SYNTAX_ERR);
      return nullptr;
    }

    protocolArray.AppendElement(protocolElement);
  }

  nsRefPtr<WebSocket> webSocket = new WebSocket();
  nsresult rv = webSocket->Init(aCx, principal, ownerWindow, aUrl, protocolArray);
  if (NS_FAILED(rv)) {
    aRv.Throw(rv);
    return nullptr;
  }

  return webSocket.forget();
}