bool vsx_widget_base_edit::event_key_down(signed long key, bool alt, bool ctrl, bool shift) {
  if (!editing_enabled) return true;
  std::vector<vsx_string>::iterator it = lines.begin();
  std::vector<int>::iterator itlv = lines_visible.begin();

  std::vector<vsx_string>::iterator itp = lines_p.begin();
  int c2 = 0;
  scroll_x = floor(scroll_x);
  vsx_string tempstring;
  vsx_string tempstring2;
  //printf("key: %d\n",key);
  if (ctrl && !alt && !shift) {
    //printf("ctrl! %d\n",key);
    switch(key) {
      case 10:
        //save();
      break;
      case 'v':
      case 'V':
#ifdef _WIN32
        HANDLE hData;

        LPVOID pData;
        char* pszData = 0;
        HWND hwnd = GetForegroundWindow();
        if (!IsClipboardFormatAvailable(CF_TEXT)) return false;
        OpenClipboard(hwnd);
        hData = GetClipboardData(CF_TEXT);
        pData = GlobalLock(hData);
        if (pszData) free(pszData);
        pszData = (char*)malloc(strlen((char*)pData) + 1);
        strcpy(pszData, (LPSTR)pData);
        vsx_string res = pszData;
        GlobalUnlock(hData);
        CloseClipboard();
        res = str_replace("\n","",res);
        process_characters = false;
        for (int i = 0; i < res.size(); ++i) {
          event_key_down(res[i],false,false,false);
        }
        free(pszData);
        process_characters = true;
        process_lines();
// copying
/*HGLOBAL hData;
    LPVOID pData;
    OpenClipboard(hwnd);
    EmptyClipboard();
    hData = GlobalAlloc(GMEM_DDESHARE | GMEM_MOVEABLE,
                        strlen(pszData) + 1);
    pData = GlobalLock(hData);
    strcpy((LPSTR)pData, pszData);
    GlobalUnlock(hData);
    SetClipboardData(CF_TEXT, hData);
    CloseClipboard();*/
#endif
      break;
    }
  } else
  switch(key) {
    // arrow left
    case -GLFW_KEY_LEFT:
      --caretx;
      if (caretx < 0) {
        if (scroll_x) {
          ++caretx;
          --scroll_x;
          //fix_pos();
        } else
        if (carety) {
          --carety;
        event_key_down(-GLFW_KEY_END);
        } else caretx = 0;
      }
      break;
    // arrow right
    case -GLFW_KEY_RIGHT:
      ++caretx;
      if ((size_t)caretx > lines[carety+(int)scroll_y].size()-(int)scroll_x) {
        event_key_down(-GLFW_KEY_DOWN);
        event_key_down(-GLFW_KEY_HOME);
      }
      if (caretx > characters_width-3) {
        --caretx;
        ++scroll_x;
      }
      break;
    // arrow up
    case -GLFW_KEY_UP:
      if (!single_row) {
        --carety;
        if (carety < 0) {
          carety = 0;
          if (scroll_y) {
            --scroll_y;
            //fix_pos();
          }
        }
        if ((size_t)caretx > lines[carety+(int)scroll_y].size()-(int)scroll_x)
        event_key_down(-GLFW_KEY_END);
         //caretx = lines[carety+(int)scroll_y].size()-(int)scroll_x;
        }
      break;
    // page up
    case -GLFW_KEY_PAGEUP:
      if (!single_row) {
        for (int zz = 0; zz < characters_height*0.95; ++zz) {
        event_key_down(-GLFW_KEY_UP);
        }
      }
      break;
    // arrow down
    case -GLFW_KEY_DOWN:
      if (!single_row) {
        ++carety;
        if (carety > lines.size()-1-scroll_y) carety = (int)((float)lines.size()-1.0f-scroll_y);
        if (carety > characters_height-2) {
          ++scroll_y;
          --carety;
        }
        if ((size_t)caretx > lines[carety+(int)scroll_y].size()-(int)scroll_x)
         caretx = lines[carety+(int)scroll_y].size()-(int)scroll_x;
      }
      break;
    // page down
    case -GLFW_KEY_PAGEDOWN:
      if (!single_row) {
        for (int zz = 0; zz < characters_height*0.95; ++zz) {
        event_key_down(-GLFW_KEY_DOWN,false,false,false);
        }
      }
      break;
    // home
    case -GLFW_KEY_HOME:
      scroll_x = 0;
      caretx = 0;
      //fix_pos();
      break;
    // end
    case -GLFW_KEY_END:
      caretx = lines[carety+(int)scroll_y].size()-(int)scroll_x;
      //if (caretx < 0) caretx = 0;
      if (caretx > characters_width-3) {
        scroll_x += caretx - characters_width+3;
        //fix_pos();
        caretx = (int)characters_width-3;
      }
      if (caretx < 0) {
        scroll_x += caretx-5;//lines[carety+(int)scroll_y].size()-5;
        if (scroll_x < 0) scroll_x = 0;
        caretx = lines[carety+(int)scroll_y].size()-(int)scroll_x;
      }
      //fix_pos();
    break;
    // backspace
    case -GLFW_KEY_BACKSPACE:
      if (caretx+(int)scroll_x) {
        lines[carety+(int)scroll_y].erase(caretx-1+(int)scroll_x,1);
        --caretx;
        if (caretx < 0) {--scroll_x; ++caretx;}
        process_line(carety+(int)scroll_y);
        //fix_pos();
      } else {
        if (scroll_y+carety) {
          while (c2 < carety+scroll_y) { ++c2; ++it; ++itp; ++itlv; }
          //++it;
          tempstring = lines[carety+(int)scroll_y];
          lines.erase(it);
          lines_p.erase(itp);
          lines_visible.erase(itlv);
        event_key_down(-GLFW_KEY_UP,false,false,false);
        event_key_down(-GLFW_KEY_END,false,false,false);
          lines[carety+(int)scroll_y] += tempstring;
          lines_p[carety+(int)scroll_y] += tempstring;
          process_line(carety+(int)scroll_y);
          process_line(carety+(int)scroll_y+1);
          //fix_pos();
        }
      }
      if (mirror_keystrokes_object) mirror_keystrokes_object->event_key_down(key, alt, ctrl, shift);
    break;
    // delete
    case -GLFW_KEY_DEL:
      event_key_down(-GLFW_KEY_RIGHT,false,false,false);
      event_key_down(-GLFW_KEY_BACKSPACE,false,false,false);
      process_line(carety+(int)scroll_y);
      if (mirror_keystrokes_object) mirror_keystrokes_object->event_key_down(key, alt, ctrl, shift);
    break;
    // enter
    case -GLFW_KEY_ENTER:
      if (single_row) {
        vsx_string d;
        if (command_prefix.size()) d = command_prefix+" ";
        command_q_b.add_raw(d+lines[0]);
        parent->vsx_command_queue_b(this);
      } else {
        if ((size_t)caretx+(size_t)scroll_x > lines[carety+(int)scroll_y].size()) event_key_down(-35,false,false,false);
        while (c2 < carety+(int)scroll_y) { ++c2; ++it; ++itp; ++itlv; }
        ++it;
        ++itp;
        ++itlv;
        tempstring = lines[carety+(int)scroll_y].substr(caretx+(int)scroll_x,lines[carety+(int)scroll_y].size()-(caretx+(int)scroll_x));
        tempstring2 = lines[carety+(int)scroll_y].substr(0,caretx+(int)scroll_x);
        lines[carety+(int)scroll_y] = tempstring2;
        lines.insert(it,tempstring);
        lines_visible.insert(itlv,0);

        tempstring = lines_p[carety+(int)scroll_y].substr(caretx+(int)scroll_x,lines_p[carety+(int)scroll_y].size()-(caretx+(int)scroll_x));
        tempstring2 = lines_p[carety+(int)scroll_y].substr(0,caretx+(int)scroll_x);
        lines_p[carety+(int)scroll_y] = tempstring2;
        lines_p.insert(itp,tempstring);

        event_key_down(-GLFW_KEY_DOWN,false,false,false);
        event_key_down(-GLFW_KEY_HOME,false,false,false);
        process_line(carety-1+(int)scroll_y);
        process_line(carety+(int)scroll_y);
      }
      if (mirror_keystrokes_object) mirror_keystrokes_object->event_key_down(key, alt, ctrl, shift);
    break;
    // esc
    case -GLFW_KEY_ESC:
    // da rest:
      if (single_row) {
        command_q_b.add_raw("cancel");
        parent->vsx_command_queue_b(this);
      } else
      a_focus = k_focus = parent;
    break;
    default:
      if (key > 0) {
        if (allowed_chars.size()) {
          if (allowed_chars.find(key) == -1) {
            break;
          }
        }
        lines[carety+(int)scroll_y].insert(caretx+(int)scroll_x,(char)key);
        updates++;
        ++caretx;
        if ((size_t)caretx > lines[carety+(int)scroll_y].size()-(int)scroll_x)
        caretx = lines[carety+(int)scroll_y].size()-(int)scroll_x;
        int t_scroll_x = (int)scroll_x;
        if (caretx+(int)scroll_x > characters_width) ++scroll_x;
        //fix_pos();
        //cout << scroll_x - t_scroll_x << endl;
        caretx -= (int)scroll_x - t_scroll_x;
        process_line(carety+(int)scroll_y);
        if (mirror_keystrokes_object) mirror_keystrokes_object->event_key_down(key, alt, ctrl, shift);
      }
    // FROO
  }
  calculate_scroll_size();
  //process_lines();
  if (longest_line-characters_width <= 0) {
    scrollbar_pos_x = 0;
  } else {
    scrollbar_pos_x = (float)scroll_x/(longest_line-characters_width);
  }
  if (longest_y-characters_height <= 0) {
    scrollbar_pos_y = 0;
  } else {
    scrollbar_pos_y = (float)scroll_y/(longest_y-characters_height);
  }
  //printf("scroll_x: %f scroll_y: %f\n caretx: %d  carety: %d\n",scroll_x,scroll_y,caretx,carety);
  return false;
}