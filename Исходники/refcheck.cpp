/*===========================================================================*\
 | Dialog Procs and related functions
\*===========================================================================*/
void FormatObjectDisplay(int i, ReferenceMaker* rm, bool showaddress, TSTR& buf) {
   TSTR str;
   if (rm) {
      rm->GetClassName(str);
      buf.printf(_T("%d: %s (0x%08x) "), i, str.data(), rm->SuperClassID());
      if (str == _T("Node")) 
			{
         INode* node = (INode*)rm;
         str = buf;
         buf.printf(_T("%s \"%s\""), str.data(), node->GetName());
      }
			else 
			{
				str = buf;
				if (rm->ClassID() == Class_ID(0,0))
					buf.printf(_T("%s (0,0)"), str.data());
				else
					buf.printf(_T("%s (0x%08x, 0x%08x)"), str.data(), rm->ClassID().PartA(), rm->ClassID().PartB());
			}
      if (showaddress) {
         str = buf;
         buf.printf(_T("%s at 0x%08x"), str.data(), rm);
      }
   }
   else
      buf.printf(_T("%d: NULL"), i);
}