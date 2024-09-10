NodoArbol * Recursiva(NodoArbol ** ptr_NodoActual)
{
  char opc='\0';
  char animalNvo[100], preguntaNvo[100];
  char * preguntaN, * animalN;
    
  NodoArbol * ptr_NodoPadreNvo = (NodoArbol *) NULL;
  NodoArbol * ptr_NodoHijoNvo = (NodoArbol *) NULL;
   
    if(   ( (*ptr_NodoActual)->ptr_izquierdo) && ( (*ptr_NodoActual)->ptr_derecho)  ) //si llego a una pregunta
      {  
	
	do{
		printf("[PREGUNTA]");
		
		printf("\n\n\t==>Es un Animal -%s- ?[ s/n ]",(char *) (*ptr_NodoActual)->dato );
		printf("-->"); 
	     opc=getc(stdin);
	     while(getchar()!='\n');
		 switch( opc )
		{
		  
		  case 's' ://(*ptr_NodoActual)->ptr_izquierdo=
		     return Recursiva(&((*ptr_NodoActual)->ptr_izquierdo));
		  break;
		  
		  case 'n' ://(*ptr_NodoActual)->ptr_derecho=
		    return Recursiva(&((*ptr_NodoActual)->ptr_derecho) );
		  break;
		  
		  case 'q':
		    return (NodoArbol *) NULL;
		  break;
		  
		  default:printf("\n<Opcion Incorrecta>\n");
		}
		
	}while( 1 );
	
      }
      else //si llego a una hoja
      {
		
	do{
		printf("[HOJA]");
		printf("\n\n\t(Hoja)El animal que pensaste es -%s- ?[ s/n ]",(char *) ((*ptr_NodoActual)->dato));
		printf("-->"); //scanf("%c",&opc); 
	   
	     opc=getc(stdin);
	     while(getchar()!='\n');
		 switch( opc )
		{
		   
		    case 's' : printf("\n\t\t~El programa adivino exitosamente el animal que pensaste~\n");return *ptr_NodoActual; 
		     break;
		  
		    case 'n' :
		      printf("\n\t\t=>Ok, en que animal pensaste-->");
				  scanf("%s",animalNvo);
		      printf("\n\t\t=>Menciona una dierencia entre %s y %s-->",(char * ) (*ptr_NodoActual)->dato, animalNvo);
				  scanf("%s",preguntaNvo);
		     
				   preguntaN = strdup(&preguntaNvo);
				   animalN = strdup(&animalNvo);
		      
			  ptr_NodoHijoNvo = CreaNodoArb( (void *) (animalN), (NodoArbol * ) NULL ,  (NodoArbol * )NULL );
			  ptr_NodoPadreNvo = CreaNodoArb( (void *) (preguntaN), ptr_NodoHijoNvo,  *ptr_NodoActual);
					      
			  *ptr_NodoActual =  ptr_NodoPadreNvo;
					
					      
			printf("\n\t\t~El programa a aprendido un nuevo animal llamado %s y es %s~\n\n",  animalN, preguntaN);
				
				return *ptr_NodoActual;
		  break;
		  
		    case 'q':
			    return (NodoArbol *) NULL;
		    break;
		  
		    default:printf("\n<Opcion Incorrecta>\n");
		}
		
	}while( 1 );
	
      }
      
  }