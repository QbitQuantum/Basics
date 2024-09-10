void
APIWebService::service(HttpRequest &request, HttpResponse &response)
{
    // remove trailing '/' from request, just to be consistent
    QString fullPath = request.getPath();
    while (fullPath.endsWith("/")) fullPath.chop(1);

    // get the paths
    QStringList paths = QString(request.getPath()).split("/");

    // we need to look at the first path to determine action
    if (paths.count() < 2) return; // impossible really

    // get ride of first blank, all URLs start with a '/'
    paths.removeFirst();

    // ROOT PATH RETURNS A LIST OF ATHLETES
    if (paths[0] == "") {
        listAthletes(response); // return csv list of all athlete and their characteristics
        return;
    }

    // we don't have a fave icon
    if (paths[0] == "favicon.ico") return;

    // Call to retreive athlete data, downstream will resolve
    // which functions to call for different data requests
    athleteData(paths, response);
}