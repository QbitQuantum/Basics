 void initDif()
 {
      memset(dif,0,sizeof(dif));
      for (int i=0;i<line;i++)
          for (int j=0;j<id_len;j++)
              for (int k=0;k<MAXLINE;k++)
                  dif[i][j][k]=different(font[SET[j]][k],in[i]);
 }