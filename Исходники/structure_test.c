main() {
//y x = {25,10,10,1000};
FILE *fp = fopen("test","rb");
//fwrite(&x,sizeof(y),1,fp);

int x1;
x1 = getw(fp);
printf("%d",x1);
}