bool FilesDownload::downloadList()
{

    string base = "http://" + host + "/" + path;


    // On parcours la liste
    for (size_t i = 0; i < filesToDownload.size(); i++) {

        string file = filesToDownload[i];

        size_t pos;
        string link;

        while( (pos = file.find("/")) != string::npos ) {

            link += file.substr(0, pos);

            if (!dirExists(link))
                CreateDirectoryA(link.c_str(), NULL);

            link += "/";
            file.erase(0, pos + 1);
        }

        link += file;


        // On télécharge le fichier
        if (!Download::download(base + link, link)) {
            printf("Erreur download: %s", link.c_str());
            return false;
        }

    }

    return true;
}