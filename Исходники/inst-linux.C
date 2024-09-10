//  This seems redunant now with getProcessStatusAsString().
pdstring process::getProcessStatus() const 
{
   char ret[80];

   switch (status()) {
	case running:
	    sprintf(ret, "%d running", getPid());
	    break;
	case neonatal:
	    sprintf(ret, "%d neonatal", getPid());
	    break;
	case stopped:
	    sprintf(ret, "%d stopped", getPid());
	    break;
	case exited:
	    sprintf(ret, "%d exited", getPid());
	    break;
	default:
	    sprintf(ret, "%d UNKNOWN State", getPid());
	    break;
    }
    return(ret);
}