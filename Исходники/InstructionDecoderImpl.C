 Expression::Ptr InstructionDecoderImpl::makeRegisterExpression(MachRegister registerID)
 {
     int newID = registerID.val();
     int minusArch = newID & ~(registerID.getArchitecture());
     int convertedID = minusArch | m_Arch;
     MachRegister converted(convertedID);
     return make_shared(singleton_object_pool<RegisterAST>::construct(converted, 0, registerID.size() * 8));
 }