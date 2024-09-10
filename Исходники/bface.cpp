bool
Bface_list::grow_connected(Bface* f, CSimplexFilter& pass)
{
   // Collect all reachable faces whose flag == 1, starting at f,
   // crossing only edges that are accepted by the given filter.

   if (!(f && f->flag() == 1))
      return false;

   f->set_flag(2);
   push_back(f);

   // check each neighboring edge:
   for (int i=1; i<4; i++) {
      Bedge* e = f->e(i);
      if (pass.accept(e)) {
         // check each adjacent face
         // (includes this, but that will be a no-op):
         for (int j=1; j<=e->num_all_faces(); j++)
            grow_connected(e->f(j), pass);
      }
   }

   return true;
}