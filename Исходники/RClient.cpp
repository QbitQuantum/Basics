    void processStdin()
    {
        assert(!data.contains('\n'));
        while (true) {
            const int ch = getc(stdin);
            if (ch == EOF)
                return;
            if (ch == '\n')
                break;
            data.append(static_cast<char>(ch));
        }
        const int colon = data.indexOf(':');
        if (colon == -1) {
            error() << "Failed to match completion header" << data;
            EventLoop::eventLoop()->unregisterSocket(STDIN_FILENO);
            EventLoop::eventLoop()->quit();
            return;
        }

        int line, column, contentsSize, pos;
        const int ret = sscanf(data.constData() + colon + 1, "%d:%d:%d:%d", &line, &column, &pos, &contentsSize);
        if (ret != 4) {
            error() << "Failed to match completion header" << ret << "\n" << data;
            EventLoop::eventLoop()->unregisterSocket(STDIN_FILENO);
            EventLoop::eventLoop()->quit();
            return;
        }
        String contents(contentsSize, ' ');
        int read = 0;
        char *c = contents.data();
        while (read < contentsSize) {
            const int r = fread(c + read, sizeof(char), contentsSize - read, stdin);
            if (r < 0) {
                EventLoop::eventLoop()->unregisterSocket(STDIN_FILENO);
                EventLoop::eventLoop()->quit();
                return;
            }
            read += r;
        }
        Path path(data.constData(), colon);
        data.clear();
        if (!path.resolve(Path::MakeAbsolute)) {
            error() << "Can't resolve" << path;
            return;
        }
        // error() << path << line << column << contentsSize << pos << "\n" << contents.left(100)
        //         << contents.right(100);

        CompletionMessage msg(CompletionMessage::None, path, line, column, pos);
        const String args = String::format<64>("%s:%d:%d:%d:%d", path.constData(), line, column, pos, contentsSize);
        const char *argv[] = { "completionStream", args.constData() };
        msg.init(2, argv);
        msg.setContents(contents);
        connection->send(msg);
    }