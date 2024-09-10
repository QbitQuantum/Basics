void glutIdle (void){
    if (b_quit) {
        g_Context.Shutdown();
        exit (1);
    }
// Display the frame
    glutPostRedisplay();
}//glutIdle