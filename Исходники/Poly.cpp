//assumes a specific format for the file
//why is this method static in the header file?
Poly* Poly::readPoly(const char* file_name)
{
   ReadFile* rf = new ReadFile(file_name); //for reading
   String* degree_str = rf->readLine();
   int degree = degree_str->a_to_i();
   delete degree_str;

   Poly* poly = new Poly(degree);
   
   for (int i = 0; i <= degree; i++)
   {
      String* coeff_str = rf->readLine();
      float coeff = coeff_str->a_to_f();
      delete coeff_str;

      poly->setCoeff(i, (double) coeff);
   }

   delete rf;
   return poly;
}