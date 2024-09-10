   virtual void keyPressed(const KeyEventPtr e)
   {
       if(e->getKey() == KeyEvent::KEY_Q && e->getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL)
       {
            TutorialWindowEventProducer->closeWindow();
       }
       switch(e->getKey())
       {
            case KeyEvent::KEY_UP:
                {
                    Color4f Col(TheLight->getDiffuse());
                    Col += Color4f(0.2,0.2,0.2,0.0);

                    std::cout << "Diffuse Color : " << Col  << std::endl;

                    beginEditCP(TheLight);
                        TheLight->setAmbient(Col*0.1);
                        TheLight->setDiffuse(Col);
                        TheLight->setSpecular(Col);
                    endEditCP(TheLight);

                    MaxLuminance =  Col.red();
                    std::cout << "MaxLuminance : " << MaxLuminance  << std::endl;
                    HDRTextureFilter->setUniformParameter("MaxLuminance", MaxLuminance);
                }
                break;
            case KeyEvent::KEY_DOWN:
                {
                    Color4f Col(TheLight->getDiffuse());
                    Col -= Color4f(0.2,0.2,0.2,0.0);
                    std::cout << "Diffuse Color : " << Col  << std::endl;

                    beginEditCP(TheLight);
                        TheLight->setDiffuse(Col);
                    endEditCP(TheLight);

                    MaxLuminance =  Col.red() + 1.0f;
                    std::cout << "MaxLuminance : " << MaxLuminance  << std::endl;
                    HDRTextureFilter->setUniformParameter("MaxLuminance", MaxLuminance);
                }
                break;
            case KeyEvent::KEY_RIGHT:
                {
                    Exposure +=  0.1f;
                    std::cout << "Exposure : " << Exposure  << std::endl;
                    HDRTextureFilter->setUniformParameter("Exposure", Exposure);
                }
                break;
            case KeyEvent::KEY_LEFT:
                {
                    Exposure -=  0.1f;
                    std::cout << "Exposure : " << Exposure  << std::endl;
                    HDRTextureFilter->setUniformParameter("Exposure", Exposure);
                }
                break;
            case KeyEvent::KEY_8:
                {
                    Gamma +=  0.05f;
                    std::cout << "Gamma : " << Gamma  << std::endl;
                    HDRTextureFilter->setUniformParameter("Gamma", Gamma);
                }
                break;
            case KeyEvent::KEY_7:
                {
                    Gamma -=  0.05f;
                    std::cout << "Gamma : " << Gamma  << std::endl;
                    HDRTextureFilter->setUniformParameter("Gamma", Gamma);
                }
                break;
       }
   }