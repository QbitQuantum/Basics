void AsiMS2000::selectCommand(int commandNum)
{
  switch(commandNum)
  {
      case 0:
          accel();
          break;
      case 1:
          aalign();
          break;
      case 2:
          afcont();
          break;
      case 3:
          aflim();
          break;
      case 4:
          afocus();
          break;
      case 5:
          afset();
          break;
      case 6:
          afmove();
          break;
      case 7:
          ahome();
          break;
      case 8:
          aij();
          break;
      case 9:
          array();
          break;
      case 10:
          azero();
          break;
      case 11:
          backlash();
          break;
      case 12:
          bcustom();
          break;
      case 13:
          benable();
          break;
      case 14:
          build();
          break;
      case 15:
          cdate();
          break;
      case 16:
          cnts();
          break;
      case 17:
          customa();
          break;
      case 18:
          customb();
          break;
      case 19:
          dack();
          break;
      case 20:
          dump();
          break;
      case 21:
          ensync();
          break;
      case 22:
          epolarity();
          break;
      case 23:
          error();
          break;
      case 24:
          halt();
          break;
      case 25:
          here();
          break;
      case 26:
          home();
          break;
      case 27:
          info();
          break;
      case 28:
          joystick();
          break;
      case 29:
          jsspd();
          break;
      case 30:
          kadc();
          break;
      case 31:
          kd();
          break;
      case 32:
          ki();
          break;
      case 33:
          kp();
          break;
      case 34:
          lcd();
          break;
      case 35:
          led();
          break;
      case 36:
          lladdr();
          break;
      case 37:
          load();
          break;
      case 38:
          lock();
          break;
      case 39:
          lockrg();
          break;
      case 40:
          lockset();
          break;
      case 41:
          maintain();
          break;
      case 42:
          motctrl();
          break;
      case 43:
          move();
          break;
      case 44:
          movrel();
          break;
      case 45:
          pcros();
          break;
      case 46:
          pedal();
          break;
      case 47:
          rbmode();
          break;
      case 48:
          rdadc();
          break;
      case 49:
          rdsbyte();
          break;
      case 50:
          rdstat();
          break;
      case 51:
          relock();
          break;
      case 52:
          reset();
          break;
      case 53:
          rt();
          break;
      case 54:
          runaway();
          break;
      case 55:
          saveset();
          break;
      case 56:
          savepos();
          break;
      case 57:
          scan();
          break;
      case 58:
          scanr();
          break;
      case 59:
          scanv();
          break;
      case 60:
          secure();
          break;
      case 61:
          sethome();
          break;
      case 62:
          setlow();
          break;
      case 63:
          setup();
          break;
      case 64:
          si();
          break;
      case 65:
          speed();
          break;
      case 66:
          spin();
          break;
      case 67:
          status();
          break;
      case 68:
          stopbits();
          break;
      case 69:
          ttl();
          break;
      case 70:
          um();
          break;
      case 71:
          units();
          break;
      case 72:
          unlock();
          break;
      case 73:
          vb();
          break;
      case 74:
          vector();
          break;
      case 75:
          version();
          break;
      case 76:
          wait();
          break;
      case 77:
          where();
          break;
      case 78:
          who();
          break;
      case 79:
          wrdac();
          break;
      case 80:
          zero();
          break;
      case 81:
          z2b();
          break;
      case 82:
          zs();
          break;
      case 83:
          overshoot();
          break;
  }
}