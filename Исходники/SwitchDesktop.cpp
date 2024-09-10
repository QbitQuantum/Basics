int main(int argc, char* argv[])
{
  if (argc < 2)
  {
     printf("Usage:SwitchDesktop <Desktop Name>\n");
  }
  
  HDESK desk = OpenDesktop(argv[1], 0, FALSE, DESKTOP_SWITCHDESKTOP);
  if (desk == NULL)
  {
    printf("切换桌面失败：%d\n",  GetLastError());
    getchar();
    return 1;
  }
  
  if (SwitchDesktop(desk))
  {
    printf("切换桌面成功");    
  } 
  else
  {
    printf("切换桌面失败：%d\n",  GetLastError());  
  }
    getchar();
}