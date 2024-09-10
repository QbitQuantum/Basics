// transfer completion: copy received file locally, set timestamp(s), verify
// fingerprint, notify app, notify files
void Transfer::complete()
{
    if (type == GET)
    {
        LOG_debug << "Download complete: " << (files.size() ? LOG_NODEHANDLE(files.front()->h) : "NO_FILES") << " " << files.size();

        bool transient_error = false;
        string tmplocalname;
        string localname;
        bool success;

        // disconnect temp file from slot...
        delete slot->fa;
        slot->fa = NULL;

        // FIXME: multiple overwrite race conditions below (make copies
        // from open file instead of closing/reopening!)

        // set timestamp (subsequent moves & copies are assumed not to alter mtime)
        success = client->fsaccess->setmtimelocal(&localfilename, mtime);

#ifdef ENABLE_SYNC
        if (!success)
        {
            transient_error = client->fsaccess->transient_error;
            LOG_debug << "setmtimelocal failed " << transient_error;
        }
#endif

        // verify integrity of file
        FileAccess* fa = client->fsaccess->newfileaccess();
        FileFingerprint fingerprint;
        Node* n;
        bool fixfingerprint = false;

        if (!transient_error && fa->fopen(&localfilename, true, false))
        {
            fingerprint.genfingerprint(fa);

            if (isvalid && !(fingerprint == *(FileFingerprint*)this))
            {
                if (!badfp.isvalid || !(badfp == fingerprint))
                {
                    badfp = fingerprint;
                    delete fa;
                    client->fsaccess->unlinklocal(&localfilename);
                    return failed(API_EWRITE);
                }
                else
                {
                    fixfingerprint = true;
                }
            }
        }
#ifdef ENABLE_SYNC
        else
        {
            if (!transient_error)
            {
                transient_error = fa->retry;
                LOG_debug << "Unable to validate fingerprint " << transient_error;
            }
        }
#endif
        delete fa;

        int missingattr = 0;
        handle attachh;
        SymmCipher* symmcipher;

        if (!transient_error)
        {
            // set FileFingerprint on source node(s) if missing
            for (file_list::iterator it = files.begin(); it != files.end(); it++)
            {
                if ((*it)->hprivate && (n = client->nodebyhandle((*it)->h)))
                {
                    if (client->gfx && client->gfx->isgfx(&(*it)->localname))
                    {
                        // check for missing imagery
                        if (!n->hasfileattribute(GfxProc::THUMBNAIL120X120)) missingattr |= 1 << GfxProc::THUMBNAIL120X120;
                        if (!n->hasfileattribute(GfxProc::PREVIEW1000x1000)) missingattr |= 1 << GfxProc::PREVIEW1000x1000;
                        attachh = n->nodehandle;
                        symmcipher = n->nodecipher();
                    }

                    if (fingerprint.isvalid && (!n->isvalid || fixfingerprint))
                    {
                        *(FileFingerprint*)n = fingerprint;

                        n->serializefingerprint(&n->attrs.map['c']);
                        client->setattr(n);
                    }
                }
            }

            if (fingerprint.isvalid && fixfingerprint)
            {
                (*(FileFingerprint*)this) = fingerprint;
            }

            if (missingattr)
            {
                // FIXME: do this while file is still open
                client->gfx->gendimensionsputfa(NULL, &localfilename, attachh, symmcipher, missingattr);
            }

            // ...and place it in all target locations. first, update the files'
            // local target filenames, in case they have changed during the upload
            for (file_list::iterator it = files.begin(); it != files.end(); it++)
            {
                (*it)->updatelocalname();
            }

            // place file in all target locations - use up to one renames, copy
            // operations for the rest
            // remove and complete successfully completed files
            for (file_list::iterator it = files.begin(); it != files.end(); )
            {
                transient_error = false;
                success = false;
                localname = (*it)->localname;

                fa = client->fsaccess->newfileaccess();
                if (fa->fopen(&localname))
                {
                    // the destination path already exists
    #ifdef ENABLE_SYNC
                    if((*it)->syncxfer)
                    {
                        sync_list::iterator it2;
                        for (it2 = client->syncs.begin(); it2 != client->syncs.end(); it2++)
                        {
                            Sync *sync = (*it2);
                            LocalNode *localNode = sync->localnodebypath(NULL, &localname);
                            if (localNode)
                            {
                                LOG_debug << "Overwritting a local synced file. Moving the previous one to debris";

                                // try to move to local debris
                                if(!sync->movetolocaldebris(&localname))
                                {
                                    transient_error = client->fsaccess->transient_error;
                                }

                                break;
                            }
                        }

                        if(it2 == client->syncs.end())
                        {
                            LOG_err << "LocalNode for destination file not found";

                            if(client->syncs.size())
                            {
                                // try to move to debris in the first sync
                                if(!client->syncs.front()->movetolocaldebris(&localname))
                                {
                                    transient_error = client->fsaccess->transient_error;
                                }
                            }
                        }
                    }
                    else
    #endif
                    {
                        LOG_debug << "The destination file exist (not synced). Saving with a different name";

                        // the destination path isn't synced, save with a (x) suffix
                        string utf8fullname;
                        client->fsaccess->local2path(&localname, &utf8fullname);
                        size_t dotindex = utf8fullname.find_last_of('.');
                        string name;
                        string extension;
                        if (dotindex == string::npos)
                        {
                            name = utf8fullname;
                        }
                        else
                        {
                            string separator;
                            client->fsaccess->local2path(&client->fsaccess->localseparator, &separator);
                            size_t sepindex = utf8fullname.find_last_of(separator);
                            if(sepindex == string::npos || sepindex < dotindex)
                            {
                                name = utf8fullname.substr(0, dotindex);
                                extension = utf8fullname.substr(dotindex);
                            }
                            else
                            {
                                name = utf8fullname;
                            }
                        }

                        string suffix;
                        string newname;
                        string localnewname;
                        int num = 0;
                        do
                        {
                            num++;
                            ostringstream oss;
                            oss << " (" << num << ")";
                            suffix = oss.str();
                            newname = name + suffix + extension;
                            client->fsaccess->path2local(&newname, &localnewname);
                        } while (fa->fopen(&localnewname));


                        (*it)->localname = localnewname;
                        localname = localnewname;
                    }
                }
                else
                {
                    transient_error = fa->retry;
                }

                delete fa;
                if (transient_error)
                {
                    LOG_warn << "Transient error checking if the destination file exist";
                    it++;
                    continue;
                }

                if (!tmplocalname.size())
                {
                    if (client->fsaccess->renamelocal(&localfilename, &localname))
                    {
                        tmplocalname = localname;
                        success = true;
                    }
                    else if (client->fsaccess->transient_error)
                    {
                        transient_error = true;
                    }
                }

                if (!success)
                {
                    if((tmplocalname.size() ? tmplocalname : localfilename) == localname)
                    {
                        LOG_debug << "Identical node downloaded to the same folder";
                        success = true;
                    }
                    else if (client->fsaccess->copylocal(tmplocalname.size() ? &tmplocalname : &localfilename,
                                                   &localname, mtime))
                    {
                        success = true;
                    }
                    else if (client->fsaccess->transient_error)
                    {
                        transient_error = true;
                    }
                }

                if (success || !transient_error)
                {
                    if (success)
                    {
                        // prevent deletion of associated Transfer object in completed()
                        (*it)->transfer = NULL;
                        (*it)->completed(this, NULL);
                    }

                    if (success || !(*it)->failed(API_EAGAIN))
                    {
                        File* f = (*it);
                        files.erase(it++);
                        if(!success)
                        {
                            LOG_warn << "Unable to complete transfer due to a persistent error";

                            f->transfer = NULL;
                            f->terminated();
                        }
                    }
                    else
                    {
                        LOG_debug << "Persistent error completing file";
                        it++;
                    }
                }
                else
                {
                    LOG_debug << "Transient error completing file";
                    it++;
                }
            }

            if (!tmplocalname.size() && !files.size())
            {
                client->fsaccess->unlinklocal(&localfilename);
            }
        }

        if (!files.size())
        {
            localfilename = localname;
            client->app->transfer_complete(this);
            delete this;
        }
        else
        {
            // some files are still pending completion, close fa and set retry timer
            delete slot->fa;
            slot->fa = NULL;

            LOG_debug << "Files pending completion: " << files.size() << ". Waiting for a retry.";
            LOG_debug << "First pending file: " << files.front()->name;

            slot->retrying = true;
            slot->retrybt.backoff(11);
        }
    }
    else
    {
        LOG_debug << "Upload complete: " << (files.size() ? files.front()->name : "NO_FILES") << " " << files.size();

        // files must not change during a PUT transfer
        if (genfingerprint(slot->fa, true))
        {
            return failed(API_EREAD);
        }

        // if this transfer is put on hold, do not complete
        client->checkfacompletion(uploadhandle, this);
        return;
    }
}