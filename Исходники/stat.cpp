int main(int argc, char** argv)
{
   if (argc != 2)
   {
      cerr << "USAGE: sector_stat file\n";
      return -1;
   }

   Sector client;
   if (Utility::login(client) < 0)
      return -1;

   SNode attr;
   int result = client.stat(argv[1], attr);

   if (result < 0)
   {
      Utility::print_error(result);
   }
   else
   {
      cout << "File Name: " << attr.m_strName << endl;
      if (attr.m_bIsDir)
         cout << "DIR: TRUE\n";
      else
         cout << "DIR: FALSE\n";
      cout << "Size: " << attr.m_llSize << " bytes" << endl;
      time_t ft = attr.m_llTimeStamp;
      cout << "Last Modified: " << ctime(&ft);
      if (!attr.m_bIsDir)
      {
         cout << "Total Number of Replicas: " << attr.m_sLocation.size() << "  (target: " << attr.m_iReplicaNum << ")" << endl;
         cout << "Location:" << endl;
         for (set<Address, AddrComp>::iterator i = attr.m_sLocation.begin(); i != attr.m_sLocation.end(); ++ i)
         {
            cout << i->m_strIP << ":" << i->m_iPort << "\t" << getDNSName(i->m_strIP) << endl;
         }
      }
   }

   Utility::logout(client);

   return result;
}