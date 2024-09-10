void CTcpClientDlg::OnGetSource() 
{
	 CSocket s;
	 
	 if(!s.Create()) {
		 AfxMessageBox("소켓 생성 실패");
		 return;
	 }

	 if(!s.Connect("www.google.com", 80)) {
		 AfxMessageBox("접속 실패!");
		 return ;
	 }

	 //GET 명령으로 데이터를 얻어옴
	 //GET 명령 형식 : GET 대상URL HTTP/1.0 <enter><enter>
	 char * cmd = "GET / HTTP/1.0\r\n\r\n";

	 s.Send(cmd, strlen(cmd));

	 char buf[100];
	 ZeroMemory(buf, 100);
	 while(s.Receive(buf, 1000)) {
		 AfxMessageBox(buf);
		 ZeroMemory(buf, 1000);
	 }
}