//----------------------------------------------------------------------------------------------------------------------------------------------------------------
//FUNCION BAJA
int borrarPelicula(EMovie* movie, int length, int index)
{
 int i, auxReturn=-1, flag=-1;
 char activate;
 if(movie!=NULL && length>0)
 {
     for(i=0;i<length;i++)
     {
         if((movie+i)->isEmpty==0)
         {
             if((movie+i)->index==index)
             {
                 printf("el registro es:\nindice: %d, titulo: %s, genero: %s, puntaje: %d\n",(movie+i)->index,(movie+i)->titulo, (movie+i)->genero, (movie+i)->puntaje);
                 activate=getChar("Esta seguro que quiere modificar este registro?(s/n)\n");
                 if(activate=='s')
                 {
                     flag=0;
                     break;
                 }
             }
         }
         else
         {
             printf("El registro no existe o ya fue eliminado.\n");
             break;
         }
     }
     if(flag!=-1)
     {
         (movie+i)->isEmpty=1;
         printf("el registro se elimino correctamente.\n");
     }
     auxReturn=0;
 }
 return auxReturn;
}