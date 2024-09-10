static void keyboard(unsigned char key, int x, int y) {
    
    switch (key) {
        case 'a':
            povray = pix = -9999;
            makePov(MOLDYN_EXPORT_TO_PNG);
            break;
            
        case 'r':
            if (magstep <= 10) {
                magstep++;
                magnification = pow(1.2, (double) magstep);
                zeye = -2 * range * magnification;
                glutPostRedisplay();
            }
            break;
            
        case 'm':
            if (magstep >= -10) {
                magstep--;
                magnification = pow(1.2, (double) magstep);
                zeye = -2 * range * magnification;                
                glutPostRedisplay();
            }
            break;
            
        case 's':
            if (move_stat == ROTATE) {
                move_stat = TRANSLATE;
            } else if (move_stat == TRANSLATE) {
                move_stat = ROTATE;
            }
            break;
            
        case 'n':
            if (file_done && last_init_done) {
                break;
            } else {
                show_stat = SHOW_NEXT;
                read_cycle();
                moldyn_update_graphics();
                glutPostRedisplay();
                break;
            }
            
        case 'b':
            if (current_cycle == 1) {
                break;
            }
            show_stat = SHOW_PREV;
            current_cycle -= 2;
            file_done = 0;
            if (feof(fptr))
                rewind(fptr);
            
            if (fsetpos(fptr, &cycle_position[current_cycle]))
                moldyn_error("can't position file");
            
            read_cycle();
            moldyn_update_graphics();
            glutPostRedisplay();
            break;
            
        case 'h':
        case 'j':
            if (show_stat == HOLD && !file_done)
            {
                if (key == 'j')
                {
                    jpeg = True;
                    moldyn_export_(MOLDYN_EXPORT_TO_JPEG, window_width, window_height);
                }
                
                glutIdleFunc(animate);
                show_stat = SHOW_ALL;
            }
            else if (show_stat == SHOW_ALL)
            {
                jpeg = False;
                show_stat = HOLD;
                moldyn_update_graphics();
                glutPostRedisplay();
            }
            break;
            
        case 'c':
        case 'C':
            moldyn_export_(MOLDYN_EXPORT_TO_JPEG, 800, 800);
            break;
            
        case 'J':
            moldyn_export_(MOLDYN_EXPORT_TO_JPEG, window_width, window_height);
            break;
            
        case 'p':
        {
            char *argv[] = {"jpeg2ps", "-o", "moldyn.eps", path};
            moldyn_export_(MOLDYN_EXPORT_TO_JPEG, 2000, 2000);
            jpeg2ps_main(sizeof(argv)/sizeof(char *),argv);
        }
#ifdef _WIN32
            system("copy moldyn.eps %PRINTER%");
#else
            system("lpr -h moldyn.eps");
#endif
            break;
            
        case '0':
            xeye = 0.0;
            yeye = 0.0;
            zeye = -2.0 * range;
            glutPostRedisplay();
            break;
            
        case '?':
            hint = (hint) ? False : True;
            glutPostRedisplay();
            break;
            
        case 'T':
        case 't':
            numbers = (numbers) ? False : True;
            glutPostRedisplay();
            break;
            
        case 'q':
        case 'Q':
        case GLUT_KEY_ESCAPE:
            moldyn_exit(0);
            break;
            
    }
}