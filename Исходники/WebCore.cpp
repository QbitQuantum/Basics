 void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
 {
     Application& app = Application::instance();
     try
     {
         WebSocket ws(request, response);
         XDUTxtSetText(ID_CURRENT_STATUS, Convert::toQXStringRef(L"Выполнено подключение к плагину. Чтобы начать интерпретацию - кликните по соотвествующей кнопке плагина Вашего браузера."));
         char buffer[MAX_BUFFER_SIZE];
         int flags=0;
         int n=1;
         do
         {
             ZeroMemory(buffer, MAX_BUFFER_SIZE);
             n = ws.receiveFrame(buffer, sizeof(buffer), flags);
             wstring message = Convert::toUnicodeString(buffer);
             if (message == L"plugin-version") {
                 //Следующее сообщение передаст данные о плагине
                 n = ws.receiveBytes(buffer, sizeof(buffer), flags);
                 XDUTxtSetText(ID_BROWSER_PLUGIN_VERSION, Convert::toQXStringRef(Convert::toUnicodeString(buffer)));
             }
             if (message == L"exportSettings") {
                 n = ws.receiveBytes(buffer, sizeof(buffer), flags);
                 ImportSettings::globalSettings=Convert::jsonToSettings(Convert::toUnicodeString(buffer));
             }
             if (message == L"start-export") {
                 WebCore::getInstance().setSocket(&ws);
                 WebCore::startExport = true;
                 while (WebCore::startExport == true);
             }
         } while (n > 0);
     }
     catch (WebSocketException& exc)
     {
         switch (exc.code())
         {
         case WebSocket::WS_ERR_HANDSHAKE_UNSUPPORTED_VERSION:
             response.set("Sec-WebSocket-Version", WebSocket::WEBSOCKET_VERSION);
         // fallthrough
         case WebSocket::WS_ERR_NO_HANDSHAKE:
         case WebSocket::WS_ERR_HANDSHAKE_NO_VERSION:
         case WebSocket::WS_ERR_HANDSHAKE_NO_KEY:
             response.setStatusAndReason(HTTPResponse::HTTP_BAD_REQUEST);
             response.setContentLength(0);
             response.send();
             break;
         }
     }
 }