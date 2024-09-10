bool Persona::validarCI(String ci)
{
        if(ci.Length()==0){
                ShowMessage("La Cédula es obligatoria, no puede estar vacia...");
                return 0;
        }
        if(ci.Length()<6||ci.Length()>8){
                ShowMessage("El campo Cédula admite entre 6 y 8 digitos");
                return 0;
        }
        char *a=ci.c_str();
        for(int i=0;i<=ci.Length()-1;i++){
                if(!IsCharAlphaNumericA(a[i])){
                        ShowMessage("El campo Cédula admite solo números entre 0 y 9");
                        return 0;
                }
        }
        return 1;
}