HuboDataModel::HuboDataModel(const HuboPlus& h, QObject* parent): 
  QAbstractTableModel(parent), hplus(h) 

{
  
  const char* all_joint_names[] = {

    "RHY", "RHR", "RHP", "RKP", "RAP", "RAR",
    "LHY", "LHR", "LHP", "LKP", "LAP", "LAR",
    "RSP", "RSR", "RSY", "REP", "RWY", "RWP",
    "LSP", "LSR", "LSY", "LEP", "LWY", "LWP",
    "HPY",

    0
  };

#ifdef HAVE_HUBO_ACH
  const size_t hubo_joint_indices[] = { 
    RHY, RHR, RHP, RKN, RAP, RAR,
    LHY, LHR, LHP, LKN, LAP, LAR,
    RSP, RSR, RSY, REB, RWY, RWP,
    LSP, LSR, LSY, LEB, LWY, LWP,
    WST,
  };
#endif

  for (int i=0; all_joint_names[i]; ++i) {
    size_t ji = hplus.kbody.lookupJoint(all_joint_names[i]);
    jnames.push_back(all_joint_names[i]);
    jidx.push_back(ji);
#ifdef HAVE_HUBO_ACH
    hidx.push_back(hubo_joint_indices[i]);
#endif
  }

  cmdState = HuboPlus::KState();

  const KinBody& b = hplus.kbody;

  cmdState.jvalues.resize(b.joints.size(), 0.0);

  cmdState.body_pos = vec3(0,0,1.05);

  curState = cmdState;

  legIKEnabled = false;

  // get the fk for the foot
  size_t manip = hplus.kbody.lookupManipulator("leftFootManip");
  assert( manip != size_t(-1) );

  Transform3Array xforms;
  hplus.kbody.transforms(curState.jvalues, xforms);

  Transform3 lfoot = hplus.kbody.manipulatorFK(xforms, manip);

  defaultFootSep = lfoot.translation().y();
  ikBodyPos = defaultBodyPos = vec3(0,0,1.02);
  ikBodyRot = defaultBodyRot = quat();


#ifdef HAVE_HUBO_ACH

  hubo_state_t state;


  ach_status_t r = achDriver.get(&state);
  assert(HuboAchDriver::useable(r));

  if (HuboAchDriver::useable(r)) {
    for (size_t i=0; i<hidx.size(); ++i) {
      curState.jvalues[jidx[i]] = state.joint[hidx[i]].ref;
      cmdState.jvalues[jidx[i]] = state.joint[hidx[i]].ref;
    }
  }

  r = achDriver.get(&href);
  if (!HuboAchDriver::useable(r)) {
    std::cerr << "warning: couldn't get the first ref!!!!\n";
    for (size_t i=0; i<hidx.size(); ++i) {
      href.ref[hidx[i]] = cmdState.jvalues[jidx[i]];
    }
  }


#endif

}