unsigned short getCpuHash()          
{
   int cpuinfo[4] = { 0, 0, 0, 0 };
   unsigned short hash = 0;

   __cpuid(cpuinfo, 0);
   unsigned short* ptr = (unsigned short*)(&cpuinfo[0]);
   for (unsigned int i = 0; i < 8; i++ )
      hash += ptr[i];

   return hash;
} 