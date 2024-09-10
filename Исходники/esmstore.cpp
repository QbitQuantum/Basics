void ESMStore::load(ESM::ESMReader &esm, Loading::Listener* listener)
{
    listener->setProgressRange(1000);

    ESM::Dialogue *dialogue = 0;

    /// \todo Move this to somewhere else. ESMReader?
    // Cache parent esX files by tracking their indices in the global list of
    //  all files/readers used by the engine. This will greaty accelerate
    //  refnumber mangling, as required for handling moved references.
    const std::vector<ESM::Header::MasterData> &masters = esm.getGameFiles();
    std::vector<ESM::ESMReader> *allPlugins = esm.getGlobalReaderList();
    for (size_t j = 0; j < masters.size(); j++) {
        ESM::Header::MasterData &mast = const_cast<ESM::Header::MasterData&>(masters[j]);
        std::string fname = mast.name;
        int index = ~0;
        for (int i = 0; i < esm.getIndex(); i++) {
            const std::string &candidate = allPlugins->at(i).getContext().filename;
            std::string fnamecandidate = boost::filesystem::path(candidate).filename().string();
            if (Misc::StringUtils::ciEqual(fname, fnamecandidate)) {
                index = i;
                break;
            }
        }
        if (index == (int)~0) {
            // Tried to load a parent file that has not been loaded yet. This is bad,
            //  the launcher should have taken care of this.
            std::string fstring = "File " + esm.getName() + " asks for parent file " + masters[j].name
                + ", but it has not been loaded yet. Please check your load order.";
            esm.fail(fstring);
        }
        mast.index = index;
    }

    // Loop through all records
    while(esm.hasMoreRecs())
    {
        ESM::NAME n = esm.getRecName();
        esm.getRecHeader();

        // Look up the record type.
        std::map<int, StoreBase *>::iterator it = mStores.find(n.val);

        if (it == mStores.end()) {
            if (n.val == ESM::REC_INFO) {
                if (dialogue)
                {
                    dialogue->readInfo(esm, esm.getIndex() != 0);
                }
                else
                {
                    std::cerr << "error: info record without dialog" << std::endl;
                    esm.skipRecord();
                }
            } else if (n.val == ESM::REC_MGEF) {
                mMagicEffects.load (esm);
            } else if (n.val == ESM::REC_SKIL) {
                mSkills.load (esm);
            }
            else if (n.val==ESM::REC_FILT || ESM::REC_DBGP)
            {
                // ignore project file only records
                esm.skipRecord();
            }
            else {
                std::stringstream error;
                error << "Unknown record: " << n.toString();
                throw std::runtime_error(error.str());
            }
        } else {
            // Load it
            std::string id = esm.getHNOString("NAME");
            // ... unless it got deleted! This means that the following record
            //  has been deleted, and trying to load it using standard assumptions
            //  on the structure will (probably) fail.
            if (esm.isNextSub("DELE")) {
              esm.skipRecord();
              it->second->eraseStatic(id);
              continue;
            }
            it->second->load(esm, id);

            // DELE can also occur after the usual subrecords
            if (esm.isNextSub("DELE")) {
              esm.skipRecord();
              it->second->eraseStatic(id);
              continue;
            }

            if (n.val==ESM::REC_DIAL) {
                dialogue = const_cast<ESM::Dialogue*>(mDialogs.find(id));
            } else {
                dialogue = 0;
            }
            // Insert the reference into the global lookup
            if (!id.empty() && isCacheableRecord(n.val)) {
                mIds[Misc::StringUtils::lowerCase (id)] = n.val;
            }
        }
        listener->setProgress(esm.getFileOffset() / (float)esm.getFileSize() * 1000);
    }
}