void Test_xyz_serverTAOLayer::init_QOS()
{
    CORBA::Object_var object = orb()->resolve_initial_references("ORBPolicyManager");
    policy_manager_ = CORBA::PolicyManager::_narrow(object.in());

    object = orb()->resolve_initial_references("PolicyCurrent");
    policy_current_ = CORBA::PolicyCurrent::_narrow(object.in());

    // Disable all default policies.
    CORBA::PolicyList policies;
    policies.length(0);
    policy_manager_->set_policy_overrides(policies, CORBA::SET_OVERRIDE);
    policy_current_->set_policy_overrides(policies, CORBA::SET_OVERRIDE);
}