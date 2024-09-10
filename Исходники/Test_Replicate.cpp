NTL_CLIENT

#include "FHE.h"
#include "replicate.h"
#include "timing.h"

static bool check_replicate(const Ctxt& c1, const Ctxt& c0, long i,
			    const FHESecKey& sKey, const EncryptedArray& ea)
{
  PlaintextArray pa0(ea), pa1(ea);
  ea.decrypt(c0, sKey, pa0);
  ea.decrypt(c1, sKey, pa1);
  pa0.replicate(i);
  
  return pa1.equals(pa0); // returns true if replication succeeded
}