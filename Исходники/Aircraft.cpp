bool Aeromatic::fdm()
{
    Aircraft *aircraft = _aircraft[_atype];
    std::vector<System*> systems = _aircraft[_atype]->get_systems();

    _engines = _MIN(_no_engines, 4);
    aircraft->_engines = _engines;


//***** METRICS ***************************************
    _payload = _max_weight;
    _stall_weight = _max_weight;

    // first, estimate wing loading in psf
    float wing_loading = aircraft->get_wing_loading();

    // if no wing area given, use wing loading to estimate
    bool wingarea_input;
    if (_wing.area == 0)
    {
        wingarea_input = false;
        _wing.area = _max_weight / wing_loading;
    }
    else
    {
        wingarea_input = true;
        wing_loading = _max_weight / _wing.area;
    }

    // calculate wing chord
    if (_wing.aspect == 0) {
        _wing.aspect = aircraft->get_aspect_ratio();
    } else {
        _user_wing_data++;
    }
    if (_wing.chord == 0)
    {
        if (_wing.aspect > 0) {
            _wing.chord = _wing.span / _wing.aspect;
        } else {
            _wing.chord = _wing.area / _wing.span;
        }
    }
    else {
        _user_wing_data++;
    }

    // calculate aspect ratio
    if (_wing.aspect == 0) {
        _wing.aspect = (_wing.span*_wing.span) / _wing.area;
    } else {
        _user_wing_data++;
    }

    if (_wing.taper == 0) {
        _wing.taper = 1.0f;
    }

    float TR = _wing.taper;
    _wing.chord_mean = 0.75f*_wing.chord*(1.0f+TR+TR*TR)/(1.0f+TR);
    _wing.de_da = 4.0f/(_wing.aspect+2.0f);

    // leading edge sweep
    // devide the span by two and account for fuselage width
    float span = 0.45f*_wing.span;
    float root_tip = _wing.chord*(1.0f - _wing.taper);

    if (_wing.sweep_le == 0)
    {
        _wing.sweep_le = atanf(root_tip/span);
        if (_wing.shape != DELTA) {
            _wing.sweep_le *= 0.5f;
        }
        _wing.sweep_le *= RAD_TO_DEG;
        _wing.sweep_le += _wing.sweep;
    }

    if (_wing.thickness == 0)
    {
        // Hofman equation for t/c
//      float Ws = _stall_weight;
        float Vs = _stall_speed * KNOTS_TO_FPS;
        float sweep = _wing.sweep * DEG_TO_RAD;
        float TC = 0.051f * _wing.area * powf(cosf(sweep), 5.0f)/Vs;
        _wing.thickness = TC * _wing.chord;
    }

    // for now let's use a standard 2 degrees wing incidence
    if (_wing.incidence == 0) {
        _wing.incidence = 2.0;
    }

    // estimate horizontal tail area
    if (_htail.area == 0) {
        _htail.area = _wing.area * aircraft->get_htail_area();
    }

    // estimate distance from CG to horizontal tail aero center
    if (_htail.arm == 0) {
        _htail.arm = _length * aircraft->get_htail_arm();
    }

    if (_htail.aspect == 0) {
        _htail.aspect = 5.0f;	// ht_w * _wing.aspect;
    }
    if (_htail.taper == 0) {
        _htail.taper = 0.5f;
    }

    float ht_w = 0.33f; // sqrtf(_htail.area / _wing.area);
    if (_htail.span == 0) {
        _htail.span = ht_w * _wing.span;
    }

    TR = _htail.taper;
    _htail.chord_mean = 0.75f*_htail.chord*(1.0f+TR+TR*TR)/(1.0f+TR);
    _htail.de_da = 4.0f/(_htail.aspect+2.0f);

    // estimate vertical tail area
    if (_vtail.area == 0) {
        _vtail.area = _wing.area * aircraft->get_vtail_area();
    }

    // estimate distance from CG to vertical tail aero center
    if (_vtail.arm == 0) {
        _vtail.arm = _length * aircraft->get_vtail_arm();
    }

    float vt_w = 0.15f; // sqrtf(_vtail.area / _wing.area*0.5f);
    if (_vtail.span == 0) {
        _vtail.span = vt_w * _wing.span;
    }
    if (_vtail.aspect == 0) {
        _vtail.aspect = 1.7f;	// vt_w * _wing.aspect;
    }
    if (_vtail.taper == 0) {
        _vtail.taper = 0.7f;
    }

    TR = _vtail.taper;
    _vtail.chord_mean = 0.75f*_vtail.chord*(1.0f+TR+TR*TR)/(1.0f+TR);
    _vtail.de_da = 4.0f/(_vtail.aspect+2.0f);

//***** EMPTY WEIGHT *********************************

    // estimate empty weight, based on max weight
    if (_empty_weight == 0) {
        _empty_weight = _max_weight * aircraft->get_empty_weight();
    }

//***** MOMENTS OF INERTIA ******************************

    // use Roskam's formulae to estimate moments of inertia
    if (_inertia[X] == 0.0f && _inertia[Y] == 0.0f && _inertia[Z] == 0.0f)
    {
        float slugs = (_empty_weight / 32.2f);	// sluggishness
        const float *R = aircraft->get_roskam();

        // These are for an empty airplane
        _inertia[X] = slugs * powf((R[X] * _wing.span / 2), 2);
        _inertia[Y] = slugs * powf((R[Y] * _length / 2), 2);
        _inertia[Z] = slugs * powf((R[Z] * ((_wing.span + _length)/2)/2), 2);
    }

//***** CG LOCATION ***********************************

    _cg_loc[X] = (_length - _htail.arm) * FEET_TO_INCH;
    _cg_loc[Y] = 0;
    _cg_loc[Z] = -(_length / 40.0f) * FEET_TO_INCH;

//***** AERO REFERENCE POINT **************************

    _aero_rp[X] = _cg_loc[X];
    _aero_rp[Y] = 0;
    _aero_rp[Z] = 0;

//***** PILOT EYEPOINT *********************************

    // place pilot's eyepoint based on airplane type
    const float *_eyept_loc = aircraft->get_eyept_loc();
    float eyept_loc[3];
    eyept_loc[X] = (_length * _eyept_loc[X]) * FEET_TO_INCH;
    eyept_loc[Y] = _eyept_loc[Y];
    eyept_loc[Z] = _eyept_loc[Z];

//***** PAYLOAD ***************************************

    // A point mass will be placed at the CG weighing
    // 1/2 of the usable aircraft load.
    float payload_loc[3];
    payload_loc[X] = _cg_loc[X];
    payload_loc[Y] = _cg_loc[Y];
    payload_loc[Z] = _cg_loc[Z];
    _payload -= _empty_weight;

//***** SYSTEMS ***************************************
    for (unsigned i=0; i<systems.size(); ++i)
    {
        if (systems[i]->enabled()) {
            systems[i]->set(_cg_loc);
        }
    }

//***** COEFFICIENTS **********************************
    aircraft->set_lift();
    aircraft->set_drag();
    aircraft->set_side();
    aircraft->set_roll();
    aircraft->set_pitch();
    aircraft->set_yaw();

//************************************************
//*                                              *
//*  Print out xml document                      *
//*                                              *
//************************************************

    char str[64];
    time_t t;

    time(&t);
#ifdef _MSC_VER
    struct tm ti;
    localtime_s(&ti, &t);
    strftime(str, sizeof(str), "%d %b %Y", &ti);
#else
    struct tm *ti= localtime(&t);
    strftime(str, sizeof(str), "%d %b %Y", ti);
#endif

    _dir = _subdir ? create_dir(_path, _name) : _path;
    if (_dir.empty()) {
        std::cout << "Unable to create directory: " << _path << "/" << _name << std::endl;
        return false;
    }

    std::string systems_dir;
    if (_system_files)
    {
        systems_dir = create_dir(_dir, "Systems");
        if (systems_dir.empty())
        {
            std::cout << "Unable to create directory: " << _dir<< "/Systems" << std::endl;
            _system_files = false;
        }
    }

    std::string fname = _dir + "/" + std::string(_name) + ".xml";

    std::string version = AEROMATIC_VERSION_STR;

    if (!_overwrite && overwrite(fname)) {
        std::cout << "File already exists: " << fname << std::endl;
        return false;
    }

    std::ofstream file;
    file.open(fname.c_str());
    if (file.fail() || file.bad())
    {
        file.close();
        return false;
    }

    file.precision(2);
    file.flags(std::ios::right);
    file << std::fixed << std::showpoint;

    file << "<?xml version=\"1.0\"?>" << std::endl;
    file << "<?xml-stylesheet type=\"text/xsl\" href=\"http://jsbsim.sourceforge.net/JSBSim.xsl\"?>" << std::endl;
    file << std::endl;
    file << "<fdm_config name=\"" << _name << "\" version=\"2.0\" release=\"ALPHA\"" << std::endl;
    file << "   xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"" << std::endl;
    file << "   xsi:noNamespaceSchemaLocation=\"http://jsbsim.sourceforge.net/JSBSim.xsd\">" << std::endl;
    file << std::endl;
    file << " <fileheader>" << std::endl;
    file << "  <author> Aeromatic v " << version << " </author>" << std::endl;
    file << "  <filecreationdate> " << str << " </filecreationdate>" << std::endl;
    file << "  <version>$Revision: 1.50 $</version>" << std::endl;
    file << "  <description> Models a " << _name << ". </description>" << std::endl;
    file << " </fileheader>" << std::endl;
    file << std::endl;
    file << "<!--\n  File:     " << _name << ".xml" << std::endl;
    file << "  Inputs:" << std::endl;
    file << "    name:          " << _name << std::endl;
    file << "    type:          ";
    switch(_atype)
    {
    case LIGHT:
        if (_no_engines == 0) {
            file << "glider" << std::endl;
        } else {
            file << "light commuter with " << _no_engines << " engines" << std::endl;
        }
        break;
    case PERFORMANCE:
        file << "WWII fighter, subsonic sport, aerobatic" << std::endl;
        break;
    case FIGHTER:
        file << _no_engines << " engine transonic/supersonic fighter" << std::endl;
        break;
    case JET_TRANSPORT:
        file << _no_engines << " engine transonic transport" << std::endl;
        break;
    case PROP_TRANSPORT:
        file << "multi-engine prop transport" << std::endl;
        break;
    }
    file << "    stall speed:   " << _stall_speed << "kts" << std::endl;
    file << "    max weight:    " << _max_weight << " lb" << std::endl;
    file << "    length:        " << _length << " ft" << std::endl;
    file << "    wing: " << std::endl;
    file << "     span:         " << _wing.span << " ft" << std::endl;
    file << "     area:         ";
    if (wingarea_input) {
        file << _wing.area << " sq-ft" << std::endl;
    } else {
        file << "unspecified" << std::endl;
    }
    file << "     chord:        " << _wing.chord << " ft" << std::endl;
    file << "     aspect ratio: " << _wing.aspect << ":1" << std::endl;
    file << "     taper ratio:  " << _wing.taper << ":1" << std::endl;
    file << "     incidence:    " << _wing.incidence << " degrees" << std::endl;
    file << "     dihedral:     " << _wing.dihedral << " degrees" << std::endl;
    file << "     sweep:        " << _wing.sweep << " degrees" << std::endl;
    file << std::endl;

    for (unsigned i=0; i<systems.size(); ++i)
    {
        if (systems[i]->enabled()) {
            std::string comment = systems[i]->comment();
            if (!comment.empty()) {
                file << comment << std::endl;
            }
        }
    }

    file << "  Outputs:" << std::endl;
    file << "    wing loading:  " << wing_loading << " lb/sq-ft" << std::endl;
    file << "    payload:       " << _payload << " lbs" << std::endl;
    file << "    CL-alpha:      " << _CLalpha[0] << " per radian" << std::endl;
    file << "    CL-0:          " << _CL0 << std::endl;
    file << "    CL-max:        " << _CLmax[0] << std::endl;
    file << "    CD-0:          " << _CD0 << std::endl;
    file << "    K:             " << _Kdi << std::endl;
    file << "    Mcrit:         " << _Mcrit << std::endl;
    file << "-->" << std::endl;
    file << std::endl;

//***** METRICS **********************************

    file << " <metrics>" << std::endl;
    file << "   <wingarea  unit=\"FT2\"> " << std::setw(8) << _wing.area << " </wingarea>" << std::endl;
    file << "   <wingspan  unit=\"FT\" > " << std::setw(8) << _wing.span << " </wingspan>" << std::endl;
    file << "   <wing_incidence>       " << std::setw(8) << _wing.incidence << " </wing_incidence>" << std::endl;
    file << "   <chord     unit=\"FT\" > " << std::setw(8) << _wing.chord << " </chord>" << std::endl;
    file << "   <htailarea unit=\"FT2\"> " << std::setw(8) << _htail.area << " </htailarea>" << std::endl;
    file << "   <htailarm  unit=\"FT\" > " << std::setw(8) << _htail.arm << " </htailarm>" << std::endl;
    file << "   <vtailarea  unit=\"FT2\">" << std::setw(8) << _vtail.area << " </vtailarea>" << std::endl;
    file << "   <vtailarm  unit=\"FT\" > " << std::setw(8) << _vtail.arm << " </vtailarm>" << std::endl;
    file << "   <location name=\"AERORP\" unit=\"IN\">" << std::endl;
    file << "     <x> " << std::setw(8) << _aero_rp[X] << " </x>" << std::endl;
    file << "     <y> " << std::setw(8) << _aero_rp[Y] << " </y>" << std::endl;
    file << "     <z> " << std::setw(8) << _aero_rp[Z] << " </z>" << std::endl;
    file << "   </location>" << std::endl;
    file << "   <location name=\"EYEPOINT\" unit=\"IN\">" << std::endl;
    file << "     <x> " << std::setw(8) << eyept_loc[X] << " </x>" << std::endl;
    file << "     <y> " << std::setw(8) << eyept_loc[Y] << " </y>" << std::endl;
    file << "     <z> " << std::setw(8) << eyept_loc[Z] << " </z>" << std::endl;
    file << "   </location>" << std::endl;
    file << "   <location name=\"VRP\" unit=\"IN\">" << std::endl;
    file << "     <x>     0.0 </x>" << std::endl;
    file << "     <y>     0.0 </y>" << std::endl;
    file << "     <z>     0.0 </z>" << std::endl;
    file << "   </location>" << std::endl;
    file << " </metrics>"<< std::endl;
    file << std::endl;
    file << " <mass_balance>" << std::endl;
    file << "   <ixx unit=\"SLUG*FT2\">  " << std::setw(8) << _inertia[X] << " </ixx>" << std::endl;
    file << "   <iyy unit=\"SLUG*FT2\">  " << std::setw(8) << _inertia[Y] << " </iyy>" << std::endl;
    file << "   <izz unit=\"SLUG*FT2\">  " << std::setw(8) << _inertia[Z] << " </izz>" << std::endl;
    file << "   <emptywt unit=\"LBS\" >  " << std::setw(8) << _empty_weight << " </emptywt>" << std::endl;
    file << "   <location name=\"CG\" unit=\"IN\">" << std::endl;
    file << "     <x> " << std::setw(8) << _cg_loc[X] << " </x>" << std::endl;
    file << "     <y> " << std::setw(8) << _cg_loc[Y] << " </y>" << std::endl;
    file << "     <z> " << std::setw(8) << _cg_loc[Z] << " </z>" << std::endl;
    file << "   </location>" << std::endl;
    file << "   <pointmass name=\"Payload\">" << std::endl;
    file << "    <description> " << _payload << " LBS should bring model up to entered max weight </description>" << std::endl;
    file << "    <weight unit=\"LBS\"> " << (_payload* 0.5f) << " </weight>" << std::endl;
    file << "    <location name=\"POINTMASS\" unit=\"IN\">" << std::endl;
    file << "     <x> " << std::setw(8) << payload_loc[X] << " </x>" << std::endl;
    file << "     <y> " << std::setw(8) << payload_loc[Y] << " </y>" << std::endl;
    file << "     <z> " << std::setw(8) << payload_loc[Z] << " </z>" << std::endl;
    file << "   </location>" << std::endl;
    file << "  </pointmass>" << std::endl;

    for (unsigned i=0; i<systems.size(); ++i)
    {
        if (systems[i]->enabled())
        {
            std::string mass_balance = systems[i]->mass_balance();
            if (!mass_balance.empty()) {
                file << mass_balance << std::endl;
            }
        }
    }

    file << " </mass_balance>" << std::endl;
    file << std::endl;

//***** FDM_CONFIG ********************************************

    for (unsigned i=0; i<systems.size(); ++i)
    {
        if (systems[i]->enabled())
        {
            std::string fdm = systems[i]->fdm();
            if (!fdm.empty()) {
                file << fdm << std::endl;
            }
        }
    }

//***** SYSTEMS ***********************************************

    if (_system_files == true)
    {
        for (unsigned i=0; i<systems.size(); ++i)
        {
            if (systems[i]->enabled())
            {
                std::string system = systems[i]->system();
                if (!system.empty())
                {
                    std::string sname = systems[i]->get_description();
                    std::string sfname = sname + ".xml";

                    if (!_overwrite && overwrite(sfname))
                    {
                        std::cout << "File already exists: " << fname << std::endl;
                        std::cout << "Skipping." << std::endl;
                    }
                    else
                    {
                        file << " <system file=\"" << sfname << "\"/>" << std::endl;

                        std::string sfpath = systems_dir + "/" + sfname;
                        std::ofstream sfile;
                        sfile.open(sfpath.c_str());
                        if (sfile.fail() || sfile.bad())
                        {
                            std::cout << "Error opening file: " << fname << std::endl;
                            std::cout << "Skipping." << std::endl;
                        }
                        else
                        {
                            sfile << "<?xml version=\"1.0\"?>" << std::endl;
                            sfile << "<system name=\"" << sname << "\">" << std::endl;
                            sfile << system << std::endl;
                            sfile << "</system>" << std::endl;
                        }
                        sfile.close();
                    }
                }
            }
        }
        file << std::endl;
    }

    file << " <flight_control name=\"FCS: " << _name << "\">" << std::endl;
    file << std::endl;

    if (_system_files == false)
    {
        for (unsigned i=0; i<systems.size(); ++i)
        {
            if (systems[i]->enabled())
            {
                std::string system = systems[i]->system();
                if (!system.empty()) {
                    file << system << std::endl;
                }
            }
        }
    }

    file << " </flight_control>"<< std::endl;
    file << std::endl;

//***** AERODYNAMICS ******************************************

    file << " <aerodynamics>" << std::endl;
    file << std::endl;

    // ***** LIFT ******************************************

    file << "  <axis name=\"LIFT\">" << std::endl;
    file << std::endl;

    for (unsigned i=0; i<systems.size(); ++i)
    {
        if (systems[i]->enabled())
        {
            std::string lift = systems[i]->lift();
            if (!lift.empty()) {
                file << lift << std::endl;
            }
        }
    }

    file << "  </axis>" << std::endl;
    file << std::endl;

    // ***** DRAG ******************************************

    file << "  <axis name=\"DRAG\">" << std::endl;
    file << std::endl;

    for (unsigned i=0; i<systems.size(); ++i)
    {
        if (systems[i]->enabled())
        {
            std::string drag = systems[i]->drag();
            if (!drag.empty()) {
               file << drag << std::endl;
            }
        }
    }

    file << "  </axis>" << std::endl;
    file << std::endl;

    // ***** SIDE ******************************************

    file << "  <axis name=\"SIDE\">" << std::endl;
    file << std::endl;

    for (unsigned i=0; i<systems.size(); ++i)
    {
        if (systems[i]->enabled())
        {
            std::string side = systems[i]->side();
            if (!side.empty()) {
                file << side << std::endl;
            }
        }
    }

    file << "  </axis>" << std::endl;
    file << std::endl;

    // ***** PITCH *****************************************

    file << "  <axis name=\"PITCH\">" << std::endl;
    file << std::endl;

    for (unsigned i=0; i<systems.size(); ++i)
    {
        if (systems[i]->enabled())
        {
            std::string pitch = systems[i]->pitch();
            if (!pitch.empty()) {
                file << pitch << std::endl;
            }
        }
    }

    file << "  </axis>" << std::endl;
    file << std::endl;

    // ***** ROLL ******************************************

    file << "  <axis name=\"ROLL\">" << std::endl;
    file << std::endl;

    for (unsigned i=0; i<systems.size(); ++i)
    {
        if (systems[i]->enabled())
        {
            std::string roll = systems[i]->roll();
            if (!roll.empty()) {
                file << roll << std::endl;
            }
        }
    }

    file << "  </axis>" << std::endl;
    file << std::endl;

    // ***** YAW *******************************************

    file << "  <axis name=\"YAW\">" << std::endl;
    file << std::endl;

    for (unsigned i=0; i<systems.size(); ++i)
    {
        if (systems[i]->enabled())
        {
            std::string yaw = systems[i]->yaw();
            if (!yaw.empty()) {
                file << yaw << std::endl;
            }
        }
    }

    file << "  </axis>" << std::endl;
    file << std::endl;
    
    file << " </aerodynamics>" << std::endl;
    file << std::endl;

    file << " <external_reactions>" << std::endl;

    for (unsigned i=0; i<systems.size(); ++i)
    {
        if (systems[i]->enabled())
        {
            std::string force = systems[i]->external_force();
            if (!force.empty()) {
                file << force << std::endl;
            }
        }
    }

    file << " </external_reactions>" << std::endl;

    file << std::endl;
    file << "</fdm_config>" << std::endl;

    file.close();

    return true;
}