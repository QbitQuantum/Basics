int main(int argc, char ** argv)
{
  
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

  glutInitWindowSize(500,500); /*se voce deseja deixar em fullscreen comente essa linha
                                 e descomente a glutFullScreen(). Se quer só aumentar o
                                 tamanho inicial da janela, basta trocar os valores*/
  glutCreateWindow("EP 2 - Fractais");  
/*    glutFullScreen();   */

  init();
  createMenu();
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);

  glutMainLoop(); /*O OpenGL passa a tomar controle total do programa*/
  
  return 0;
}