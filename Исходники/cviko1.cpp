int main()
{
   

   Socket socket;
   socket.bind(8001);
   socket.connect("192.168.0.1", 1989);

	

   socket.close();

   return 0;
}