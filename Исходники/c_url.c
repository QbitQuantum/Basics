int main(int argc, char *argv[])

{

 struct sockaddr_in    pin;

  int   mysock;

  char  buf[8192];

  char  *str="http://140.116.226.211/123.txt 0 0";
  char  *str1="tt 0 0";
  int flag = 0;

  /* 建立server IPv4位址 */

  bzero(&pin, sizeof(pin));

  pin.sin_family = AF_INET;

  pin.sin_addr.s_addr = inet_addr("140.116.226.205");

  pin.sin_port = htons(port);





  /* 建立socket */

while(1){


  mysock = socket(AF_INET, SOCK_STREAM, 0);

  if (mysock == -1) {

        perror("call to socket");

        exit(1);

  }

  /* 連結server */

  if (connect(mysock, (void *)&pin, sizeof(pin)) == -1) {

        perror("call to connect");

        exit(1);

  }

  /* 將str字串傳給 server */

  //printf("Sending message %s to server ...\n", str);

if(flag ==0){

  if (send(mysock, str, strlen(str), 0) == -1) {

        perror("Error in send\n");

        exit(1);

  }
flag = 1;

}

while(1)
{


  /* 接收 server 回傳的訊息 */
  if (recv(mysock, buf, 8192, 0) == -1) {
        perror("Error in receiving\n");
        exit(1);
  }
printf("@%c",buf[0]);
  if(buf[0]=='g'){
    if (send(mysock, str1, strlen(str1), 0) == -1) {
        perror("Error in send\n");
        exit(1);
   buf[0]=='z';
  }

}

  printf("\nResponse from server: \n\n%s\n", buf);
 }
}


  /* 關閉與server的連線 */

  close(mysock);

  return 0;

}