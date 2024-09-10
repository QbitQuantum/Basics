    /**
     * @param loc the location in system.indexes where the index spec is
     */
    void NOINLINE_DECL insert_makeIndex(Collection* collectionToIndex,
                                        const DiskLoc& loc,
                                        bool mayInterrupt) {
        uassert(13143,
                "can't create index on system.indexes",
                collectionToIndex->ns().coll() != "system.indexes");

        BSONObj info = loc.obj();
        std::string idxName = info["name"].valuestr();

        // Set curop description before setting indexBuildInProg, so that there's something
        // commands can find and kill as soon as indexBuildInProg is set. Only set this if it's a
        // killable index, so we don't overwrite commands in currentOp.
        if (mayInterrupt) {
            cc().curop()->setQuery(info);
        }

        IndexCatalog::IndexBuildBlock indexBuildBlock( collectionToIndex->getIndexCatalog(), idxName, loc );
        verify( indexBuildBlock.indexDetails() );

        try {
            buildAnIndex( collectionToIndex->ns(), collectionToIndex->details(),
                          *indexBuildBlock.indexDetails(), mayInterrupt);
            indexBuildBlock.success();
        }
        catch (DBException& e) {
            // save our error msg string as an exception or dropIndexes will overwrite our message
            LastError *le = lastError.get();
            int savecode = 0;
            string saveerrmsg;
            if ( le ) {
                savecode = le->code;
                saveerrmsg = le->msg;
            }
            else {
                savecode = e.getCode();
                saveerrmsg = e.what();
            }

            verify(le && !saveerrmsg.empty());
            setLastError(savecode,saveerrmsg.c_str());
            throw;
        }
    }