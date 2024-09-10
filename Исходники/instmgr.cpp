string InstanceManager::CreateId()
{
   // Create binary UUID
   UUID uuid;
   UuidCreate(&uuid);

   // Convert binary UUID to RPC string
   RPC_CSTR tmpstr;
   UuidToStringA(&uuid, &tmpstr);   
  
   // Copy string UUID to string and free RPC version
   string uuidstr((char*)tmpstr);
   RpcStringFreeA(&tmpstr);

   return uuidstr;
}