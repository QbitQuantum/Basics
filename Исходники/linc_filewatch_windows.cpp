            DWORD WINAPI FileWatcherThread::run_thread( void *_watcher ) {

                FileWatcherThread *watcher = (FileWatcherThread*)_watcher;


                while(watcher->running) {

                    ReadDirectoryChangesW(
                        watcher->handle, watcher->buffer, watcher->buffer_size, TRUE,
                        FILE_NOTIFY_CHANGE_CREATION | FILE_NOTIFY_CHANGE_FILE_NAME | FILE_NOTIFY_CHANGE_LAST_WRITE,
                        NULL, &watcher->overlap, NULL
                    );

                    WaitForSingleObject(watcher->overlap.hEvent, INFINITE);

                        int seek = 0;

                        while(seek < watcher->buffer_size) {

                            PFILE_NOTIFY_INFORMATION notifier = PFILE_NOTIFY_INFORMATION(watcher->buffer + seek);

                            WCHAR szwFileName[MAX_PATH];
                            int ulCount = notifier->FileNameLength/2;
                            wcsncpy(szwFileName, notifier->FileName, ulCount);
                            szwFileName[ulCount] = L'\0';

                            std::wstring widepath(szwFileName);
                            std::string path(widepath.begin(), widepath.end());

                            FilewatchEventType _event_type = fe_unknown;

                                switch( notifier->Action ) {

                                    case FILE_ACTION_ADDED:{
                                        _event_type = fe_create;
                                        break;
                                    }

                                    case FILE_ACTION_REMOVED:{
                                        _event_type = fe_remove;
                                        break;
                                    }

                                    case FILE_ACTION_MODIFIED:{
                                        _event_type = fe_modify;
                                        break;
                                    }

                                    case FILE_ACTION_RENAMED_OLD_NAME:{
                                        _event_type = fe_remove;
                                        break;
                                    }

                                    case FILE_ACTION_RENAMED_NEW_NAME:{
                                        _event_type = fe_create;
                                        break;
                                    }

                                } //switch

                                if(_event_type != fe_unknown) {

                                    // put into queue
                                    snow::io::event_node_t* node = new snow::io::event_node_t;
                                    node->path = std::string(watcher->path+"/"+path);
                                    node->event_type = (int)_event_type;

                                    snow::io::eventqueue_push(&filewatch_queue, node);

                                }

                            seek += notifier->NextEntryOffset;

                            if(notifier->NextEntryOffset == 0) {
                                break;
                            }

                        } //seek < buffer size

                    } //while running

                return 0;

            } //run_thread