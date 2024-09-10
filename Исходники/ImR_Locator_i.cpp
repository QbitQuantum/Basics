CORBA::Object_ptr
ImR_Locator_i::set_timeout_policy (CORBA::Object_ptr obj, const ACE_Time_Value& to)
{
  CORBA::Object_var ret (CORBA::Object::_duplicate (obj));

  try
    {
      TimeBase::TimeT timeout;
      ORBSVCS_Time::Time_Value_to_TimeT (timeout, to);
      CORBA::Any tmp;
      tmp <<= timeout;

      CORBA::PolicyList policies (1);
      policies.length (1);
      policies[0] = orb_->create_policy (Messaging::RELATIVE_RT_TIMEOUT_POLICY_TYPE,
                                         tmp);

      ret = obj->_set_policy_overrides (policies, CORBA::ADD_OVERRIDE);

      policies[0]->destroy ();

      if (CORBA::is_nil (ret.in ()))
        {
          if (debug_ > 0)
            {
              ORBSVCS_DEBUG ((LM_DEBUG,
                          ACE_TEXT ("(%P|%t) ImR: Unable to set timeout policy.\n")));
            }
          ret = CORBA::Object::_duplicate (obj);
        }
    }
  catch (const CORBA::Exception& ex)
    {
      ex._tao_print_exception (
        ACE_TEXT ("(%P|%t) ImR_Locator_i::set_timeout_policy ()"));
    }

  return ret._retn ();
}