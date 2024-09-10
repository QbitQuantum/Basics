// Better version of above one. 
// Stolen and butchered from AltDrag's code
HWND GetRealParent(HWND hWnd)
{
      HWND root = GetAncestor(hWnd, GA_ROOT);

        while (hWnd != root) {
          HWND parent = GetParent(hWnd);
          LONG_PTR exstyle = GetWindowLongPtr(hWnd, GWL_EXSTYLE);
          if ((exstyle & WS_EX_MDICHILD)) {
            break;
          }
          hWnd = parent;
        }
      return hWnd;
}