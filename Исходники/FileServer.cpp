void FileServerRequestHandler::handleRequest(const HTTPRequest& request, Poco::MemoryInputStream& message,
                                             const std::shared_ptr<StreamSocket>& socket)
{
    try
    {
        bool noCache = false;
#if ENABLE_DEBUG
        noCache = true;
#endif
        Poco::Net::HTTPResponse response;
        Poco::URI requestUri(request.getURI());
        LOG_TRC("Fileserver request: " << requestUri.toString());
        requestUri.normalize(); // avoid .'s and ..'s

        std::string path(requestUri.getPath());
        if (path.find("loleaflet/" LOOLWSD_VERSION_HASH "/") == std::string::npos)
        {
            LOG_WRN("client - server version mismatch, disabling browser cache.");
            noCache = true;
        }

        std::vector<std::string> requestSegments;
        requestUri.getPathSegments(requestSegments);
        const std::string relPath = getRequestPathname(request);
        // Is this a file we read at startup - if not; its not for serving.
        if (requestSegments.size() < 1 || FileHash.find(relPath) == FileHash.end())
            throw Poco::FileNotFoundException("Invalid URI request: [" + requestUri.toString() + "].");

        const auto& config = Application::instance().config();
        const std::string loleafletHtml = config.getString("loleaflet_html", "loleaflet.html");
        const std::string endPoint = requestSegments[requestSegments.size() - 1];
        if (endPoint == loleafletHtml)
        {
            preprocessFile(request, message, socket);
            return;
        }

        if (request.getMethod() == HTTPRequest::HTTP_GET)
        {
            if (endPoint == "admin.html" ||
                endPoint == "adminSettings.html" ||
                endPoint == "adminHistory.html" ||
                endPoint == "adminAnalytics.html")
            {
                preprocessAdminFile(request, socket);
                return;
            }

            if (endPoint == "admin-bundle.js" ||
                endPoint == "admin-localizations.js")
            {
                noCache = true;

                if (!LOOLWSD::AdminEnabled)
                    throw Poco::FileAccessDeniedException("Admin console disabled");

                if (!FileServerRequestHandler::isAdminLoggedIn(request, response))
                    throw Poco::Net::NotAuthenticatedException("Invalid admin login");

                // Ask UAs to block if they detect any XSS attempt
                response.add("X-XSS-Protection", "1; mode=block");
                // No referrer-policy
                response.add("Referrer-Policy", "no-referrer");
            }

            // Do we have an extension.
            const std::size_t extPoint = endPoint.find_last_of('.');
            if (extPoint == std::string::npos)
                throw Poco::FileNotFoundException("Invalid file.");

            const std::string fileType = endPoint.substr(extPoint + 1);
            std::string mimeType;
            if (fileType == "js")
                mimeType = "application/javascript";
            else if (fileType == "css")
                mimeType = "text/css";
            else if (fileType == "html")
                mimeType = "text/html";
            else if (fileType == "png")
                mimeType = "image/png";
            else if (fileType == "svg")
                mimeType = "image/svg+xml";
            else
                mimeType = "text/plain";

            auto it = request.find("If-None-Match");
            if (it != request.end())
            {
                // if ETags match avoid re-sending the file.
                if (!noCache && it->second == "\"" LOOLWSD_VERSION_HASH "\"")
                {
                    // TESTME: harder ... - do we even want ETag support ?
                    std::ostringstream oss;
                    Poco::DateTime now;
                    Poco::DateTime later(now.utcTime(), int64_t(1000)*1000 * 60 * 60 * 24 * 128);
                    oss << "HTTP/1.1 304 Not Modified\r\n"
                        << "Date: " << Poco::DateTimeFormatter::format(
                            now, Poco::DateTimeFormat::HTTP_FORMAT) << "\r\n"
                        << "Expires: " << Poco::DateTimeFormatter::format(
                            later, Poco::DateTimeFormat::HTTP_FORMAT) << "\r\n"
                        << "User-Agent: " << WOPI_AGENT_STRING << "\r\n"
                        << "Cache-Control: max-age=11059200\r\n"
                        << "\r\n";
                    socket->send(oss.str());
                    socket->shutdown();
                    return;
                }
            }

            response.set("User-Agent", HTTP_AGENT_STRING);
            response.set("Date", Poco::DateTimeFormatter::format(Poco::Timestamp(), Poco::DateTimeFormat::HTTP_FORMAT));

            bool gzip = request.hasToken("Accept-Encoding", "gzip");
            const std::string *content;
#if ENABLE_DEBUG
            if (std::getenv("LOOL_SERVE_FROM_FS"))
            {
                // Useful to not serve from memory sometimes especially during loleaflet development
                // Avoids having to restart loolwsd everytime you make a change in loleaflet
                const std::string filePath = Poco::Path(LOOLWSD::FileServerRoot, relPath).absolute().toString();
                HttpHelper::sendFile(socket, filePath, mimeType, response, noCache);
                return;
            }
#endif
            if (gzip)
            {
                response.set("Content-Encoding", "gzip");
                content = getCompressedFile(relPath);
            }
            else
                content = getUncompressedFile(relPath);

            if (!noCache)
            {
                // 60 * 60 * 24 * 128 (days) = 11059200
                response.set("Cache-Control", "max-age=11059200");
                response.set("ETag", "\"" LOOLWSD_VERSION_HASH "\"");
            }
            response.setContentType(mimeType);
            response.add("X-Content-Type-Options", "nosniff");

            std::ostringstream oss;
            response.write(oss);
            const std::string header = oss.str();
            LOG_TRC("#" << socket->getFD() << ": Sending " <<
                    (!gzip ? "un":"") << "compressed : file [" << relPath << "]: " << header);
            socket->send(header);
            socket->send(*content);
        }
    }
    catch (const Poco::Net::NotAuthenticatedException& exc)
    {
        LOG_ERR("FileServerRequestHandler::NotAuthenticated: " << exc.displayText());
        sendError(401, request, socket, "", "", "WWW-authenticate: Basic realm=\"online\"\r\n");
    }
    catch (const Poco::FileAccessDeniedException& exc)
    {
        LOG_ERR("FileServerRequestHandler: " << exc.displayText());
        sendError(403, request, socket, "403 - Access denied!",
                  "You are unable to access");
    }
    catch (const Poco::FileNotFoundException& exc)
    {
        LOG_WRN("FileServerRequestHandler: " << exc.displayText());
        sendError(404, request, socket, "404 - file not found!",
                  "There seems to be a problem locating");
    }
}