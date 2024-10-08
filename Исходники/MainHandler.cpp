void ODBCHandler::handleRequest(Poco::Net::HTTPServerRequest & request, Poco::Net::HTTPServerResponse & response)
{
    Poco::Net::HTMLForm params(request, request.stream());
    LOG_TRACE(log, "Request URI: " + request.getURI());

    auto process_error = [&response, this](const std::string & message)
    {
        response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
        if (!response.sent())
            response.send() << message << std::endl;
        LOG_WARNING(log, message);
    };

    if (!params.has("query"))
    {
        process_error("No 'query' in request body");
        return;
    }

    if (!params.has("columns"))
    {
        process_error("No 'columns' in request URL");
        return;
    }

    if (!params.has("connection_string"))
    {
        process_error("No 'connection_string' in request URL");
        return;
    }

    UInt64 max_block_size = DEFAULT_BLOCK_SIZE;
    if (params.has("max_block_size"))
    {
        std::string max_block_size_str = params.get("max_block_size", "");
        if (max_block_size_str.empty())
        {
            process_error("Empty max_block_size specified");
            return;
        }
        max_block_size = parse<size_t>(max_block_size_str);
    }

    std::string columns = params.get("columns");
    std::unique_ptr<Block> sample_block;
    try
    {
        sample_block = parseColumns(std::move(columns));
    }
    catch (const Exception & ex)
    {
        process_error("Invalid 'columns' parameter in request body '" + ex.message() + "'");
        LOG_WARNING(log, ex.getStackTrace().toString());
        return;
    }

    std::string format = params.get("format", "RowBinary");
    std::string query = params.get("query");
    LOG_TRACE(log, "Query: " << query);

    std::string connection_string = params.get("connection_string");
    LOG_TRACE(log, "Connection string: '" << connection_string << "'");

    WriteBufferFromHTTPServerResponse out(request, response, keep_alive_timeout);
    try
    {
        BlockOutputStreamPtr writer = FormatFactory::instance().getOutput(format, out, *sample_block, *context);
        auto pool = getPool(connection_string);
        ODBCBlockInputStream inp(pool->get(), query, *sample_block, max_block_size);
        copyData(inp, *writer);
    }
    catch (...)
    {
        auto message = getCurrentExceptionMessage(true);
        response.setStatusAndReason(
            Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR); // can't call process_error, bacause of too soon response sending
        writeStringBinary(message, out);
        tryLogCurrentException(log);
    }
}