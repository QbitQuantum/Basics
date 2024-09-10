void MapperGui::widgetHidden(const gcn::Event& event){
    // create a new map
    if( event.getSource() == loadMapBox ){
        if( loadMapBox->isInfoReady() ){
            //release old World (or create if NULL ptr)
            if( world != NULL ){
                notify("Releasing old world from memory");
                world->unload();
            } else {
                notify("Making a new AreaMap object");
                world = new AreaMap;
            }

            //make the new layers
            notify("Allocating layers...");
            world->setSize(6);
            for( size_t i = 0; i < world->size(); ++i ){
                world->getLayer(i).setSize( loadMapBox->getMapWidth(), loadMapBox->getMapHeight() );
            }


            // set other properties
            notify("Setting Properties");
            world->setFilename( loadMapBox->getFilename() );
            world->setMapName( loadMapBox->getMapName() );
            world->setExclusive( loadMapBox->isExclusive() );
            for( size_t i = 0; i < world->size(); ++i ){
                world->getLayer(i).setTileWidth( loadMapBox->getTileWidth() );
                world->getLayer(i).setTileHeight( loadMapBox->getTileHeight() );
            }
            unNotify();

            // free old surface
            if( worldImage != NULL ){
                SDL_FreeSurface(worldImage);
                worldImage = NULL;
            };
            //set the info as un usable  now
            loadMapBox->infoTaken();

            mapDetailsBox->setInfoSource( world );
        }
    } else



    // from the filename widget
    if( event.getSource() == filenameBox ){
        if( filenameBox->isInfoReady() ){
            std::string filename = correctFilepath(filenameBox->getFilename());
            switch( action ){
                case SAVEAS:
                    if( world != NULL ){
                        if ( world->size() == 0 ){
                            alert("Theres no map to save (try the new map button =P)");
                        } else if( (filename != "") && !filename.empty() ){
                            if( !world->saveMap(filename) ){
                                alert( ("Cant save file: " + filename) );
                            } else {
                                alert("Saved");
                            }
                        }
                    } else {
                        alert("Theres no map to save (try the new map button =P)");
                    }
                    action = NOTHING;
                    filenameBox->infoTaken();
                    break;

                case OPEN:
                    if( world == NULL ){ world = new AreaMap; }
                    if( !world->loadMap(filename) ){
                        alert( ("Cant open file: " + filename) );
                    } else {
                        //  free old worldImage
                        if( worldImage != NULL ){
                            SDL_FreeSurface(worldImage);
                            worldImage = NULL;
                        };
                    }
                    action = NOTHING;
                    filenameBox->infoTaken();
                    break;

                case NOTHING:
                    break;

                default:
                    action = NOTHING;
                    break;
            }
            mapDetailsBox->setInfoSource( world );
        }
    } else


    //trying to make a new tileste
    if( event.getSource() == makeTilesetBox ){
        if( makeTilesetBox->isInfoReady() ){
            //  check the save filename
            if( getFileSize(correctFilepath(makeTilesetBox->getSaveFilename())) ){
                notify("File already exists. If you save, old tileset def will be overwritten");
            }

            //set the info as un usable  now
            makeTilesetBox->infoTaken();
        }
    }

    mapTouched = 1;
}