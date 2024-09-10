        bool processRequest(const TcpConnectionPtr& conn, const string& request){
            string id;
            string puzzle;
            bool goodRequest = true;

            string::const_iterator colon = find(request.begin(), request.end(), ':');
            if(colon != request.end()){
                id.assign(request.begin(), colon);
                puzzle.assign(colon+1, request.end());
            }else{
                puzzle = request;
            }

            if(puzzle.size() == implicit_cast<size_t>(kCells)){
                LOG_DEBUG << conn->name();
                string result = solveSudoku(puzzle);
                if(id.empty()){
                    conn->send(result+"\r\n");
                }else{
                    conn->send(id +":"+ result+"\r\n" );
                }
            }else
                goodRequest = false;
            return goodRequest;
        }