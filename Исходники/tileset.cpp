bool Tileset::Load(const QString &def_filename, const QString& root_folder, bool one_image)
{
    if (def_filename.isEmpty())
        return false;

    _initialized = false;

    // Reset container data
    autotileability.clear();
    walkability.clear();
    _animated_tiles.clear();

    // Create filenames from the tileset name
    _tileset_name = CreateTilesetName(def_filename);
    _tileset_definition_filename = def_filename;

    // Set up for reading the tileset definition file.
    ReadScriptDescriptor read_data;
    if(!read_data.OpenFile(root_folder.toStdString() + def_filename.toStdString())) {
        _initialized = false;
        return false;
    }

    if (!read_data.OpenTable("tileset")) {
        read_data.CloseFile();
        qDebug("Failed to open the 'tileset' table");
        return false;
    }

    _tileset_image_filename = QString::fromStdString(read_data.ReadString("image"));

    // Prepare the tile vector and load the tileset image
    tiles.clear();
    tiles.resize(256);

    QRect rectangle;
    QImage entire_tileset;
    QString tileset_full_path = root_folder + _tileset_image_filename;
    if (!entire_tileset.load(tileset_full_path, "png")) {
        qDebug("Failed to load tileset image: %s",
                tileset_full_path.toStdString().c_str());
        return false;
    }

    if (one_image) {
        tiles[0].convertFromImage(entire_tileset);
    }
    else {

        for(uint32_t row = 0; row < num_rows; ++row) {
            for(uint32_t col = 0; col < num_cols; ++col) {
                rectangle.setRect(col * TILE_WIDTH, row * TILE_HEIGHT, TILE_WIDTH,
                                TILE_HEIGHT);
                QImage tile = entire_tileset.copy(rectangle);
                if(!tile.isNull()) {
                    // linearize the tile index
                    uint32_t i = num_rows * row + col;
                    tiles[i].convertFromImage(tile);
                } else {
                    qDebug("Image loading error!");
                }
            }
        }
    }

    // Read in autotiling information.
    if(read_data.DoesTableExist("autotiling") == true) {
        // Contains the keys (indeces, if you will) of this table's entries
        std::vector<int32_t> keys;
        uint32_t table_size = read_data.GetTableSize("autotiling");
        read_data.OpenTable("autotiling");

        read_data.ReadTableKeys(keys);
        for(uint32_t i = 0; i < table_size; ++i)
            autotileability[keys[i]] = read_data.ReadString(keys[i]);
        read_data.CloseTable();
    } // make sure table exists first

    // Read in walkability information.
    if(read_data.DoesTableExist("walkability") == true) {
        std::vector<int32_t> vect;  // used to read in vectors from the data file
        read_data.OpenTable("walkability");

        for(int32_t i = 0; i < 16; ++i) {
            read_data.OpenTable(i);
            // Make sure that at least one row exists
            if(read_data.IsErrorDetected() == true) {
                read_data.CloseTable();
                read_data.CloseTable();
                read_data.CloseFile();
                _initialized = false;
                return false;
            }

            for(int32_t j = 0; j < 16; ++j) {
                read_data.ReadIntVector(j, vect);
                if(read_data.IsErrorDetected() == false)
                    walkability[i * 16 + j] = vect;
                vect.clear();
            } // iterate through all tiles in a row
            read_data.CloseTable();
        } // iterate through all rows of the walkability table
        read_data.CloseTable();
    } // make sure table exists first

    // Read in animated tiles.
    if(read_data.DoesTableExist("animated_tiles") == true) {
        uint32_t table_size = read_data.GetTableSize("animated_tiles");
        read_data.OpenTable("animated_tiles");

        for(uint32_t i = 1; i <= table_size; ++i) {
            _animated_tiles.push_back(std::vector<AnimatedTileData>());
            std::vector<AnimatedTileData>& tiles = _animated_tiles.back();
            // Calculate loop end: an animated tile is comprised of a tile id
            // and a time, so the loop end is really half the table size.
            uint32_t tile_count = read_data.GetTableSize(i) / 2;
            read_data.OpenTable(i);
            for(uint32_t index = 1; index <= tile_count; index++) {
                AnimatedTileData anim_tile;
                anim_tile.tile_id = read_data.ReadUInt(index * 2 - 1);
                anim_tile.time    = read_data.ReadUInt(index * 2);
                tiles.push_back(anim_tile);
            } // iterate through all tiles in one animated tile
            read_data.CloseTable();
        } // iterate through all animated tiles in the table
        read_data.CloseTable();
    } // make sure table exists first

    read_data.CloseTable();
    read_data.CloseFile();

    _initialized = true;
    return true;
} // Tileset::Load(...)