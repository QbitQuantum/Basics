    std::string TiURLToPath(const std::string& tiURL)
    {
        try
        {
            Poco::URI inURI = Poco::URI(tiURL);

            if (inURI.getScheme() != "ti")
            {
                return tiURL;
            }

            std::string host(inURI.getHost());
            SharedApplication app = Host::GetInstance()->GetApplication();
            std::string path(app->GetComponentPath(host));

            if (path.empty())
            {
                throw ValueException::FromString("Could not find component "+host);
            }

            std::vector<std::string> segments;
            inURI.getPathSegments(segments);

            for (size_t i = 0; i < segments.size(); i++)
            {
                path = FileUtils::Join(path.c_str(), segments[i].c_str(), NULL);
            }
            return path;
        }
        catch (ValueException& e)
        {
            SharedString ss = e.DisplayString();
            Logger* log = Logger::Get("URLUtils");
            log->Error("Could not convert %s to a path: %s", tiURL.c_str(), ss->c_str());
        }
        catch (...)
        {
            Logger* log = Logger::Get("URLUtils");
            log->Error("Could not convert %s to a path", tiURL.c_str());
        }
        return tiURL;
    }