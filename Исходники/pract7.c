int menu(int *f){
    int op,i,opcion,x,columna=43,fila=6;
    int pos;
    char nombre[20];
    char aapp[15];
    static  Alumno Alum[Max];
    static int contAlum=0;

    system("cls");
    switch(*f){
        case INICIO+3:
            system("cls");
            gotoxy(50,10);printf("AGREGAR ALUMNO");
            Captura(Alum,&contAlum);
            gotoxy(43,27);printf("...PRESIONA UNA TECLA PARA CONTINUAR...");
            getch();
        break;
        case INICIO+6:
            system("cls");
            if(band == 1){
                gotoxy(columna,fila+3);printf("ELIMINAR ALUMNO");
                gotoxy(columna-25,fila+6);printf("APELLIDO PATERNO ");
                fflush(stdin);
                gotoxy(columna-23,fila+8);gets(aapp);
                strupr(aapp);
                gotoxy(columna+5,fila+6);printf("NOMBRE ");
                fflush(stdin);
                gotoxy(columna,fila+8);gets(nombre);
                strupr(nombre);
                for(i=0; i<contAlum; i++)
                    if(Alum[i].Edad != 0)
                        Eliminar(Alum,&contAlum,i,nombre,aapp);
                    else
                        gotoxy(columna,fila+24);printf("EL ALUMNO NO EXISTE");
                gotoxy(40,27);printf("...PRESIONA UNA TECLA PARA CONTINUAR...");
                getch();
            }
            else{
                gotoxy(40,7);printf("...NO HAY DATOS CAPTURADOS...");
                getch();
            }
        break;
        case INICIO+9:
            if(band == 1){
                do{
                    system("cls");
                    gotoxy(columna,fila+3);printf("MOSTRAR ALUMNO");
                    gotoxy(columna,fila+6);printf("1. NOMBRE");
                    gotoxy(columna,fila+9);printf("2. APELLIDO PATERNO");
                    gotoxy(columna,fila+12);printf("3. APELLIDO MATERNO");
                    gotoxy(columna,fila+15);printf("4. EDAD");
                    gotoxy(columna,fila+18);printf("5. SEMESTRE");
                    gotoxy(columna,fila+21);printf("6. SALIR");
                    gotoxy(columna,fila+24);printf("Elige una Opcion: ");
                    scanf("%d",&opcion);
                    switch(opcion){
                        case 1:
                            system("cls");
                            gotoxy(columna+5,fila);printf("ALUMNOS");
                            insercionNom(Alum,contAlum);
                            i=0;
                            do{
                                mostrarAlum(Alum,i);
                                i++;
                            }while(i<contAlum);
                            gotoxy(columna,fila+(i+15));printf("...PRESIONA UNA TECLA PARA CONTINUAR...");
                            getch();
                        break;
                        case 2:
                            system("cls");
                            gotoxy(columna+5,fila);printf("ALUMNOS");
                            quickSortAP(Alum,0,(contAlum-1));
                            for(i=0; i<contAlum; i++)
                                mostrarAlum(Alum,i);
                            gotoxy(columna,fila+(i+15));printf("...PRESIONA UNA TECLA PARA CONTINUAR...");
                            getch();
                        break;
                        case 3:
                            system("cls");
                            gotoxy(columna+5,fila);printf("ALUMNOS");
                            burbujaMejoradoAM(Alum,contAlum);
                            for(i=0; i<contAlum; i++)
                                mostrarAlum(Alum,i);
                            gotoxy(columna,fila+(i+15));printf("...PRESIONA UNA TECLA PARA CONTINUAR...");
                            getch();
                        break;
                        case 4:
                            system("cls");
                            gotoxy(columna+5,fila);printf("ALUMNOS");
                            seleccionEdad(Alum,contAlum);
                            for(i=0; i<contAlum; i++)
                                mostrarAlum(Alum,i);
                            gotoxy(columna,fila+(i+15));printf("...PRESIONA UNA TECLA PARA CONTINUAR...");
                            getch();
                        break;
                        case 5:
                            system("cls");
                            gotoxy(columna+5,fila);printf("ALUMNOS");
                            shellSortSem(Alum,contAlum);
                            for(i=0; i<contAlum; i++)
                                mostrarAlum(Alum,i);
                            gotoxy(columna,fila+(i+15));printf("...PRESIONA UNA TECLA PARA CONTINUAR...");
                            getch();
                        break;
                        case 6:
                            system("cls");
                            gotoxy(columna+5,fila);printf("ABANDONAR MENU MOSTRAR...");
                            gotoxy(columna,fila+(i+15));printf("...PRESIONA UNA TECLA PARA CONTINUAR...");
                            getch();
                        break;
                        default:
                            system("cls");
                            gotoxy(columna+5,fila);printf("OPCION INCORRECTA");
                            gotoxy(columna,fila+(i+15));printf("...PRESIONA UNA TECLA PARA CONTINUAR...");
                            getch();
                    }
                }while(opcion != 6);
            }
            else{
                gotoxy(40,7);printf("...NO HAY DATOS CAPTURADOS...");
                getch();
            }
        break;
        case INICIO+12:
            if(band == 1){
                system("cls");
                gotoxy(columna,fila+3);printf("BUSQUEDA");
                gotoxy(columna-25,fila+6);printf("APELLIDO PATERNO");
                fflush(stdin);
                gotoxy(columna-23,fila+8);gets(aapp);
                strupr(aapp);
                gotoxy(columna-10,fila+6);printf("NOMBRE:");
                fflush(stdin);
                gotoxy(columna-10,fila+6);gets(nombre);
                strupr(nombre);
                pos=busquedaBinaria(Alum,contAlum,aapp,nombre);
                if(x != -1){
                    if(Alum[pos].Edad != 0){
                        system("cls");
                        printf("ALUMNOS ENCONTRADOS");
                        mostrarAlum(Alum,pos);
                        gotoxy(40,7);printf("...PRESIONA UNA TECLA PARA CONTINUAR...");
                        getch();
                    }
                    else
                        gotoxy(43,23);printf("ALUMNO NO ENCONTRADO");
                }
                else
                    gotoxy(43,23);printf("ALUMNO NO ENCONTRADO");
                gotoxy(40,7);printf("...PRESIONA UNA TECLA PARA CONTINUAR...");
                getch();
            }
            else{
                gotoxy(40,7);printf("...NO HAY DATOS CAPTURADOS...");
                getch();
            }
        break;
        case INICIO+15:
            system("cls");
            gotoxy(columna+15,fila);printf("...ABANDONAR PROGRAMA...");
            gotoxy(columna+5,fila+2);printf("...PRESIONA UNA TECLA PARA CONTINUAR...\n");
            getch();
            return 27;
        break;
    }
    return 0;
}