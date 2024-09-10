void brain_stroke_web::service(HttpRequest &request, HttpResponse &response){
    QLOG_ERROR() << "debug thread" << QThread::currentThread();
    QByteArray path = request.getPath();
    if(path =="/getallversion"){
        get_version_controller_ins.service(request,response);
        return;
    }
    else if (path == "/getfile") {
        download_version_controller_ins.service(request,response);
        return;
    }
    else if (path == "/rename"){
        //POST
        if(request.getMethod() != "POST"){
            netutil::write(response, 401, "wrong method");
            return;
        }
        rename_version_controller_ins.service(request,response);
        return;
    }
    else if(path == "/delete"){
        //POST
        if(request.getMethod() != "POST"){
            netutil::write(response, 401, "wrong method");
            return;
        }
        delete_version_controller_ins.service(request,response);
        return;
    }
    else if(path.startsWith("/data")){
        QString key = request.getParameter("key");
        if(key != QString(inner_data_trans_key)){
            response.setStatus(401,"key error");
            response.write("key error");
        }
        else{
            StaticFileController_ins->service(request,response);
            return;
        }
    }
    else{
        response.setStatus(401,"no matched request");
        response.write("no matched request", false);
    }
}