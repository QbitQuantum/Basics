void cargarArchivo(FILE * archivo)
{
  char seguir;
  Paciente regi;
  
  fseek(archivo, 0, SEEK_END);
  
  do 
  {
    system("cls");     
    printf("NHC: ");
    _flushall();
    scanf("%d", &regi.nhc);
    
    printf("\nNombre: ");
    _flushall();
    gets(regi.nombre);
    
    printf("\nEdad: ");
    _flushall();
    scanf("%d", &regi.edad);
    
    printf("\nSexo: ");
    _flushall();
    scanf("%c", &regi.sexo);
    
    printf("\nDiagnostico: ");
    _flushall();
    gets(regi.diagnostico);
    
    fwrite(&regi, sizeof(regi), 1, archivo);
    
    printf("\n");
    printf("\nIngresar otro paciente? (S/N)");
    _flushall();
    scanf("%c", &seguir);
    
       
  } while (seguir == 'S' || seguir == 's');   
     
     
} // cargarArchivo