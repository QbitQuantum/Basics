/* ----------------------------- MNI Header -----------------------------------
@NAME       : acr_lookup_vr_name
@INPUT      : vr_name - the 2-letter VR name to look up
@OUTPUT     : (none)
@RETURNS    : Internal VR code
@DESCRIPTION: Looks up a VR name in the table. If it does not exist, the
              name is added to the unknown table.
@METHOD     : 
@GLOBALS    : 
@CALLS      : 
@CREATED    : January 31, 1997 (Peter Neelin)
@MODIFIED   : 
---------------------------------------------------------------------------- */
Acr_VR_Type acr_lookup_vr_name(char *vr_name)
{
   Acr_VR_Type vr_code;
   int ientry;
   char *string;

   /* Look up the name and return the matching code if found */
   vr_code = find_vr_name(vr_name);
   if (vr_code >= 0) {
      return vr_code;
   }

   /* If name is not found, add it to the unknown table */
   if (unknown_VR_table_length <= 0) {
      unknown_VR_table_length = 1;
      unknown_VR_table = MALLOC((size_t) unknown_VR_table_length * 
                                sizeof(*unknown_VR_table));
   }
   else {
      unknown_VR_table_length++;
      unknown_VR_table = REALLOC(unknown_VR_table,
                                 (size_t) unknown_VR_table_length * 
                                 sizeof(*unknown_VR_table));
   }

   /* Fill in the entry */
   ientry = unknown_VR_table_length-1;
   unknown_VR_table[ientry].vr_code = ientry + ACR_VR_NUM_TYPES;
   string = MALLOC(3);
   string[0] = vr_name[0];
   string[1] = vr_name[1];
   string[2] = '\0';
   unknown_VR_table[ientry].vr_name = string;
   unknown_VR_table[ientry].convert_to_numeric = return_zero;
   unknown_VR_table[ientry].convert_to_string = return_empty_string;

   /* Return the code */
   return unknown_VR_table[ientry].vr_code;

}