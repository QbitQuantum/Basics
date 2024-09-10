HealpixSource::HealpixSource(KConfig *cfg, const QString& filename, const QString& type, const QDomElement& e) : KstDataSource(cfg, filename, type) {
  int ret;
  size_t poff;
   
  _valid = false;
  if (type.isEmpty( ) || type == "HEALPIX") {
    strncpy(_healpixfile, filename.latin1(), HEALPIX_STRNL);
    
    _names = healpix_strarr_alloc(HEALPIX_FITS_MAXCOL);
    _units = healpix_strarr_alloc(HEALPIX_FITS_MAXCOL);
    _keys = healpix_keys_alloc();
    
    ret = healpix_fits_map_info(_healpixfile, &_mapNside, &_mapOrder, &_mapCoord, &_mapType, &_nMaps, _creator, _extname, _names, _units, _keys);
    
    if (_mapType == HEALPIX_FITS_CUT) {
      poff = 1;
    } else {
      poff = 0;
    }
    if (ret) {
      _valid = true;
      _mapNpix = 12 * _mapNside * _mapNside;
      _nX = 800;
      _nY = 600;
      _autoTheta = true;
      _autoPhi = true;
      //FIXME switch to radians default later
      _thetaUnits = HPUNIT_RADEC;
      _phiUnits = HPUNIT_RADEC;
      _vecUnits = HPUNIT_RADEC;
      _autoMag = true;
      _vecDegrade = 0;
      _vecTheta = 0;
      _vecPhi = 0;
      _vecQU = false;
      loadConfig(cfg);
      if (!e.isNull()) {
        load(e);
      }
      
      // populate the metadata
      QString metaVal;
      QString metaName;
      metaVal.sprintf("%lu", (long unsigned int)_mapNside);
      _metaData["NSIDE"] = metaVal;
      metaVal.sprintf("%lu", (long unsigned int)_mapNpix);
      _metaData["NPIX"] = metaVal;
      metaVal.sprintf("%d", _mapOrder);
      _metaData["ORDER"] = metaVal;
      metaVal.sprintf("%d", _mapCoord);
      _metaData["COORD"] = metaVal;
      metaVal.sprintf("%d", _mapType);
      _metaData["TYPE"] = metaVal;
      metaVal.sprintf("%lu", (long unsigned int)_nMaps);
      _metaData["NMAPS"] = metaVal;
      metaVal.sprintf("%s", _creator);
      _metaData["CREATOR"] = metaVal;
      metaVal.sprintf("%s", _extname);
      _metaData["EXTNAME"] = metaVal;
      for (size_t j = 0; j < _keys->nskeys; j++) {
        metaName.sprintf("%s", _keys->skeynames[j]);
        metaVal.sprintf("%s", _keys->skeyvals[j]);
        _metaData[metaName] = metaVal;
      }
      for (size_t j = 0; j < _keys->nikeys; j++) {
        metaName.sprintf("%s", _keys->ikeynames[j]);
        metaVal.sprintf("%d", _keys->ikeyvals[j]);
        _metaData[metaName] = metaVal;
      }
      for (size_t j = 0; j < _keys->nfkeys; j++) {
        metaName.sprintf("%s", _keys->fkeynames[j]);
        metaVal.sprintf("%e", _keys->fkeyvals[j]);
        _metaData[metaName] = metaVal;
      }
      
      // populate the field list
      QString mapName;
      for (size_t i = 0; i < _nMaps; i++) {
        if (strlen(_names[i+poff]) == 0) {
          mapName.sprintf("%d - %s",(int)(i+1),"MAP");
        } else {
          mapName.sprintf("%d - %s",(int)(i+1),_names[i+poff]);
        }
        if (strlen(_units[i+poff]) == 0) {
          mapName.sprintf("%s (%s)",mapName.ascii(),"Unknown Units");
        } else {
          mapName.sprintf("%s (%s)",mapName.ascii(),_units[i+poff]);
        }
        _matrixList.append(mapName);
      }
      if (_mapType == HEALPIX_FITS_CUT) {
        if (strlen(_names[_nMaps+1]) == 0) {
          mapName.sprintf("%s","HITS");
        } else {
          mapName.sprintf("%s",_names[_nMaps+1]);
        }
        _matrixList.append(mapName);
        if (strlen(_names[_nMaps+2]) == 0) {
          mapName.sprintf("%s","ERRORS");
        } else {
          mapName.sprintf("%s",_names[_nMaps+2]);
        }
        if (strlen(_units[_nMaps+2]) == 0) {
          mapName.sprintf("%s (%s)",mapName.ascii(),"Unknown Units");
        } else {
          mapName.sprintf("%s (%s)",mapName.ascii(),_units[_nMaps+2]);
        }
        _matrixList.append(mapName);
      }
      _fieldList.append("1 - Vector Field Head Theta");
      _fieldList.append("2 - Vector Field Head Phi");
      _fieldList.append("3 - Vector Field Tail Theta");
      _fieldList.append("4 - Vector Field Tail Phi");
    } else {
      healpix_keys_free(_keys);
      healpix_strarr_free(_names, HEALPIX_FITS_MAXCOL);
      healpix_strarr_free(_units, HEALPIX_FITS_MAXCOL);
    }
  }
}