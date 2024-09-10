void PbfParser::extractGeometry(protobuf::message& _geomIn, int _tileExtent, std::vector<Line>& _out, const MapTile& _tile) {
    
    pbfGeomCmd cmd = pbfGeomCmd::moveTo;
    uint32_t cmdRepeat = 0;
    
    double invTileExtent = (1.0/(double)_tileExtent);
    
    Line line;
    
    int64_t x = 0;
    int64_t y = 0;
    
    while(_geomIn.getData() < _geomIn.getEnd()) {
        
        if(cmdRepeat == 0) { // get new command, lengh and parameters..
            uint32_t cmdData = static_cast<uint32_t>(_geomIn.varint());
            cmd = static_cast<pbfGeomCmd>(cmdData & 0x7); //first 3 bits of the cmdData
            cmdRepeat = cmdData >> 3; //last 5 bits
        }
        
        if(cmd == pbfGeomCmd::moveTo || cmd == pbfGeomCmd::lineTo) { // get parameters/points
            // if cmd is move then move to a new line/set of points and save this line
            if(cmd == pbfGeomCmd::moveTo) {
                if(line.size() > 0) {
                    _out.push_back(line);
                }
                line.clear();
            }
            
            x += _geomIn.svarint();
            y += _geomIn.svarint();
            
            // bring the points in -1 to 1 space
            Point p;
            p.x = invTileExtent * (double)(2 * x - _tileExtent);
            p.y = invTileExtent * (double)(_tileExtent - 2 * y);
            
            line.push_back(p);
            
        } else if( cmd == pbfGeomCmd::closePath) { // end of a polygon, push first point in this line as last and push line to poly
            line.push_back(line[0]);
            _out.push_back(line);
            line.clear();
        }
        
        cmdRepeat--;
    }