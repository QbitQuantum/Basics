void
MiroWindow::keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27:
            exit(0);
        break;

        case 'i':
        case 'I':
        {
            char str[1024];
            sprintf(str, "miro_%d.ppm", time(0));
            if (g_camera->isOpenGL())
            {
                unsigned char* buf = new unsigned char[g_image->width()*g_image->height()*3];
                glReadPixels(0, 0, g_image->width(), g_image->height(),
                             GL_RGB, GL_UNSIGNED_BYTE, buf);
                g_image->writePPM(str, buf, g_image->width(), g_image->height());
            }
            else
            {
                g_image->writePPM(str);
            }
            break;
        }

        case 'r':
        case 'R':
            g_camera->setRenderer(Camera::RENDER_RAYTRACE);
        break;

        case 'g':
        case 'G':
            g_camera->setRenderer(Camera::RENDER_OPENGL);
        break;

        case '+':
            m_scaleFact *= 1.5;
        break;

        case '-':
            m_scaleFact /= 1.5;
        break;

        case 'w':
        case 'W':
            g_camera->setEye(g_camera->eye() + m_scaleFact*g_camera->viewDir());
        break;

        case 's':
        case 'S':
            g_camera->setEye(g_camera->eye() - m_scaleFact*g_camera->viewDir());
        break;

        case 'q':
        case 'Q':
            g_camera->setEye(g_camera->eye() + m_scaleFact*g_camera->up());
        break;

        case 'z':
        case 'Z':
            g_camera->setEye(g_camera->eye() - m_scaleFact*g_camera->up());
        break;
		case 'v':
		case 'V':
			g_scene->togglePDraw();
		break;
		case 'b':
		case 'B':
			g_scene->toggleDraw();
		break;

        case 'a':
        case 'A':
        {
            Vector3 vRight = cross(g_camera->viewDir(), g_camera->up());
            g_camera->setEye(g_camera->eye() - m_scaleFact*vRight);
            break;
        }

        case 'd':
        case 'D':
        {
            Vector3 vRight = cross(g_camera->viewDir(), g_camera->up());
            g_camera->setEye(g_camera->eye() + m_scaleFact*vRight);
            break;
        }
        break;

        default:
        break;
    }
    glutPostRedisplay();
}