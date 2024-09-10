int main(int argc, char *argv[])
{
  FILE *ft,*fd;

  while (1) {
    switch(getmenu("Import DB from NokiaDB.dat;Print data;Insert data;Delete data;Search Data & modify data;Devide list & Extract List;Reverse list;Save to file;Quit",9,0))
      {  mfflush();
      case 1:
        if((fd = fopen(DAT,"r+b")) == NULL) printf("\t\tCan't read file %s",DAT);
        else {
          if(getmenu("Insert Whole;Insert Part",2,0) == 1) {
              importfdat(fd,1,1);
          } else {
            if(getmenu("From Begin;From ending",2,0) == 1) importfdat(fd,2,1);
            else importfdat(fd,2,2);
          }
            printf("\t\tImport DB complete !!\n");
            fclose(fd);
        } break;
      case 2:if(root == NULL && root2 == NULL) {
          indent(2); printf("Import data first !!\n");
        } else {
          if(root2 == NULL) printdat(root);
          else {
            int c ;
            if((c = getmenu("Print data of first list;Print data of second list",2,0)) == 1)
              printdat(root); else printdat(root2);
          }
        }
        break;
      case 3:if(root == NULL){
          indent(2); printf("Import data first !!\n");
        } else {
          int c;
          VARTYPE p;
          printf("\t\tModel of phone :");scanf("%[^\n]",p.model);mfflush();
          printf("\t\tSize of phone :");scanf("%d",&p.size);mfflush();
          printf("\t\tPhone's size of screen :");scanf("%f",&p.screen);mfflush();
          printf("\t\tPhone's price :");scanf("%d",&p.price);mfflush();
          if((c = getmenu("Insert at Begining;Insert at Ending;Insert at Position",3,0)) == 1) {
            insertB(p);
          } else if (c == 2) insertE(p);
          else {
            int z;
            node *g;
            do {
            printf("\t\t Where you want to insert (if you don't want to insert anymore input -1 !! 1st = 0 postion) :");scanf("%d",&z);mfflush();
            g = insertAtPosition(p,z);
            } while (g == NULL && z != -1);
          }
        }break;
      case 4:if(root == NULL) {
          indent(2); printf("Import data first !!\n");
        } else {
          int c;
          if((c = getmenu("Delete at Postion;Delete current;Delete first",3,0))==1)  {
            int p;
            printf("\t\t Where you want to delelte (if you don't want to insert anymore input -1 !! 1st = 0 postion) :");scanf("%d",&p);mfflush();
            deleteAtPosition(p);
          } else if(c == 2) delNode(cur);
          else if(c == 3) delNode(root);
        } break;
      case 5:
        if(root == NULL) {
          indent(2); printf("Import data first !!\n");
        } else {
          int cc;
          if((cc = getmenu("Search data;Modify data",2,0)) == 1){
            int c;
            if((c = getmenu("Search By name;Search By Price",2,0)) ==1)
              search(root,1);
            else search(root,2);
          } else {
            modify();
          }
        } break;
      case 6:
        if(root == NULL) {
          indent(2); printf("Import data first !!\n");
        } else {
          int c;
          if((c = getmenu("Devide List;Extract list",2,0))==1){
            int p;
            printf("\t\tPostion you want to devide list : ");scanf("%d",&p);mfflush();
            root2 = devideList(root,last,p);
          } else {
            int p,n;
            printf("\t\tPostion you want to start extract list : ");scanf("%d",&p);mfflush();
            printf("\t\tLength of extract list : ");scanf("%d",&n);mfflush();
            extractList(p,n);
          }
        }break;
        case 7:if(root == NULL) {
          indent(2); printf("Import data first !!\n");
        } else {
          reversel();
        }break;
      case 8:if(root == NULL) {
          indent(2); printf("Import data first !!\n");
        } else {
          if((fd = fopen(DAT,"w+b")) == NULL) printf("Can't create file %s",DAT);
          else {
            exporttdat(fd);
          }
        }break;
      case 9:
        freelist(root);
        freelist(root2);
        indent(2);printf("Exit Program !!\n");
        return 0;
      }
  }
}