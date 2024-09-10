void MWState::StateManager::loadGame (const Character *character, const std::string& filepath)
{
    try
    {
        cleanup();

        ESM::ESMReader reader;
        reader.open (filepath);

        if (reader.getFormat() > ESM::SavedGame::sCurrentFormat)
            throw std::runtime_error("This save file was created using a newer version of OpenMW and is thus not supported. Please upgrade to the newest OpenMW version to load this file.");

        std::map<int, int> contentFileMap = buildContentFileIndexMap (reader);

        Loading::Listener& listener = *MWBase::Environment::get().getWindowManager()->getLoadingScreen();

        listener.setProgressRange(100);
        listener.setLabel("#{sLoadingMessage14}");

        Loading::ScopedLoad load(&listener);

        bool firstPersonCam = false;

        size_t total = reader.getFileSize();
        int currentPercent = 0;
        while (reader.hasMoreRecs())
        {
            ESM::NAME n = reader.getRecName();
            reader.getRecHeader();

            switch (n.val)
            {
                case ESM::REC_SAVE:
                    {
                        ESM::SavedGame profile;
                        profile.load(reader);
                        if (!verifyProfile(profile))
                        {
                            cleanup (true);
                            MWBase::Environment::get().getWindowManager()->pushGuiMode (MWGui::GM_MainMenu);
                            return;
                        }
                        mTimePlayed = profile.mTimePlayed;
                    }
                    break;

                case ESM::REC_JOUR:
                case ESM::REC_JOUR_LEGACY:
                case ESM::REC_QUES:

                    MWBase::Environment::get().getJournal()->readRecord (reader, n.val);
                    break;

                case ESM::REC_DIAS:

                    MWBase::Environment::get().getDialogueManager()->readRecord (reader, n.val);
                    break;

                case ESM::REC_ALCH:
                case ESM::REC_ARMO:
                case ESM::REC_BOOK:
                case ESM::REC_CLAS:
                case ESM::REC_CLOT:
                case ESM::REC_ENCH:
                case ESM::REC_NPC_:
                case ESM::REC_SPEL:
                case ESM::REC_WEAP:
                case ESM::REC_GLOB:
                case ESM::REC_PLAY:
                case ESM::REC_CSTA:
                case ESM::REC_WTHR:
                case ESM::REC_DYNA:
                case ESM::REC_ACTC:
                case ESM::REC_PROJ:
                case ESM::REC_MPRJ:
                case ESM::REC_ENAB:
                case ESM::REC_LEVC:
                case ESM::REC_LEVI:
                    MWBase::Environment::get().getWorld()->readRecord(reader, n.val, contentFileMap);
                    break;

                case ESM::REC_CAM_:
                    reader.getHNT(firstPersonCam, "FIRS");
                    break;

                case ESM::REC_GSCR:

                    MWBase::Environment::get().getScriptManager()->getGlobalScripts().readRecord (reader, n.val);
                    break;

                case ESM::REC_GMAP:
                case ESM::REC_KEYS:
                case ESM::REC_ASPL:
                case ESM::REC_MARK:

                    MWBase::Environment::get().getWindowManager()->readRecord(reader, n.val);
                    break;

                case ESM::REC_DCOU:
                case ESM::REC_STLN:

                    MWBase::Environment::get().getMechanicsManager()->readRecord(reader, n.val);
                    break;

                default:

                    // ignore invalid records
                    std::cerr << "Ignoring unknown record: " << n.toString() << std::endl;
                    reader.skipRecord();
            }
            int progressPercent = static_cast<int>(float(reader.getFileOffset())/total*100);
            if (progressPercent > currentPercent)
            {
                listener.increaseProgress(progressPercent-currentPercent);
                currentPercent = progressPercent;
            }
        }

        mCharacterManager.setCurrentCharacter(character);

        mState = State_Running;

        Settings::Manager::setString ("character", "Saves",
                                      character->getPath().filename().string());

        MWBase::Environment::get().getWindowManager()->setNewGame(false);
        MWBase::Environment::get().getWorld()->setupPlayer();
        MWBase::Environment::get().getWorld()->renderPlayer();
        MWBase::Environment::get().getWindowManager()->updatePlayer();
        MWBase::Environment::get().getMechanicsManager()->playerLoaded();

        if (firstPersonCam != MWBase::Environment::get().getWorld()->isFirstPerson())
            MWBase::Environment::get().getWorld()->togglePOV();

        MWWorld::ConstPtr ptr = MWMechanics::getPlayer();

        const ESM::CellId& cellId = ptr.getCell()->getCell()->getCellId();

        // Use detectWorldSpaceChange=false, otherwise some of the data we just loaded would be cleared again
        MWBase::Environment::get().getWorld()->changeToCell (cellId, ptr.getRefData().getPosition(), false);

        // Vanilla MW will restart startup scripts when a save game is loaded. This is unintuitive,
        // but some mods may be using it as a reload detector.
        MWBase::Environment::get().getScriptManager()->getGlobalScripts().addStartup();

        // Do not trigger erroneous cellChanged events
        MWBase::Environment::get().getWorld()->markCellAsUnchanged();
    }
    catch (const std::exception& e)
    {
        std::stringstream error;
        error << "Failed to load saved game: " << e.what();

        std::cerr << error.str() << std::endl;
        cleanup (true);

        MWBase::Environment::get().getWindowManager()->pushGuiMode (MWGui::GM_MainMenu);

        std::vector<std::string> buttons;
        buttons.push_back("#{sOk}");
        MWBase::Environment::get().getWindowManager()->interactiveMessageBox(error.str(), buttons);
    }
}