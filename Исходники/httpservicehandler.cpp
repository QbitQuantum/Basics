void httpServiceHandler::service(HttpRequest &request, HttpResponse &response)
{
    QByteArray path=request.getPath();
    qDebug("RequestMapper: path=%s",path.data());
//    response.write("Hello World",true);


     if (request.getParameter("action")=="sendMessage")
     {
         QString bodyStr = request.getBody();
         int bodyLen = bodyStr.length();
         int nameIndex = bodyStr.indexOf("name=", 0);
         QString message = "";
         if(bodyLen > 0 && nameIndex > 0)
         {
            message = bodyStr.mid(nameIndex + 5, bodyLen-nameIndex-5);
            qDebug() << "message --> " << message;
            m_mainwindow->setMessage(message);
         }
     }     

     if(m_isHaveHtmlFile)
     {
        response.write(m_htmlFile);
     }
     else
     {
         response.setHeader("Content-Type", "text/html; charset=utf-8");
         response.write("<html><body>");
         response.write("<form method=\"post\">");
         response.write(" <H1><input style=\"font-size:150%;\" type=\"hidden\" name=\"action\" value=\"sendMessage\"></H1>");
         response.write(" <H1> 输入点啥吧：</H1> <H1><input style=\"font-size:150%;\" type=\"text\" name=\"name\"></H1><br>");
         response.write("  <H1><input style=\"font-size:150%;\" type=\"submit\" value=\"确定\"></H1>");
         response.write("</form>");
         response.write("</body></html>",true);
     }
}