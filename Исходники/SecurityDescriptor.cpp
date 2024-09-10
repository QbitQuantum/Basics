void SecurityDescriptor::clearOwner()
{
  SetSecurityDescriptorOwner(&m_sd, 0, TRUE);
}