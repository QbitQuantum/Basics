void registrasi_anggota()
{
    int i;
    if(node_index==0)
    {
        reg_input();
        awal=temp;
        temp->next=NULL;
        akhir=temp;
        node_index++;


        baca=fopen("db_akun.dat","w+");
        fseek(stdin,0,SEEK_END);
        fwrite(temp,sizeof(struct akun),1,baca);
        fclose(baca);


        baca=fopen("people_index.dat","w+");
        fseek(stdin,0,SEEK_END);
        _putw(node_index,baca);
        fclose(baca);
    }
    else if(node_index>0)
    {
        reg_input();
        temp->next=NULL;
        akhir->next=temp;
        akhir=temp;
        node_index++;

        baca=fopen("db_akun.dat","w+");
        fseek(stdin,0,SEEK_END);
        fwrite(temp,sizeof(struct akun),1,baca);
        fclose(baca);


        baca=fopen("people_index.dat","w+");
        fseek(stdin,0,SEEK_END);
        _putw(node_index,baca);
        fclose(baca);
    }
    printf("\nMenyimpan data");
    for(i=0; i<3; i++)
    {
        printf(".");
        Sleep(900);
    }
    printf("\n\nData anda telah disimpan !");
    getch();
    system("cls");
    menu_utama();
}