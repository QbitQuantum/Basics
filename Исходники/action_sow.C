 void doIt (Daisy& daisy, const Scope&, Treelog& msg)
 { 
   msg.message ("Sowing " + crop->type_name ());      
   daisy.field ().sow (metalib, *crop, row_width, row_pos, seed, 
                     daisy.time (), msg); 
 }