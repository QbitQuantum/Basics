LRESULT CALLBACK VolumeMeterProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    VolumeMeterData *meter;

    switch(message)
    {
        case WM_NCCREATE:
            {
                CREATESTRUCT *pCreateData = (CREATESTRUCT*)lParam;

                meter = (VolumeMeterData*)malloc(sizeof(VolumeMeterData));
                zero(meter, sizeof(VolumeMeterData));
                SetWindowLongPtr(hwnd, 0, (LONG_PTR)meter);

                meter->curVolume = VOL_MIN;
                meter->curMax = VOL_MIN;
                meter->curPeak = VOL_MIN;
                
                meter->cx = pCreateData->cx;
                meter->cy = pCreateData->cy;

                for(int i = 0; i < 16; i++)
                {
                    meter->graduations[i] = (DBtoLog(-96.0f + 6.0f * (i+1)) - minLinear) / (maxLinear - minLinear);
                }

                /*create color brushes*/
                meter->hRed  = CreateSolidBrush(0x2929f4);
                meter->hGreen  = CreateSolidBrush(0x2bf13e);
                meter->hGreenDark  = CreateSolidBrush(0x177d20);
                meter->hBlack = CreateSolidBrush(0x000000);
                meter->hGray = CreateSolidBrush(0x777777);
                meter->hLightGray = CreateSolidBrush(0xCCCCCC);
                
                return TRUE;
            }

        case WM_DESTROY:
            {
                meter = GetVolumeMeterData(hwnd);
                
                DeleteObject(meter->hRed);
                DeleteObject(meter->hGreen);
                DeleteObject(meter->hGreenDark);
                DeleteObject(meter->hBlack);
                DeleteObject(meter->hGray);
                DeleteObject(meter->hLightGray);
                
                if(meter)
                    free(meter);

                break;
            }

        case WM_PAINT:
            {
                meter = GetVolumeMeterData(hwnd);

                PAINTSTRUCT ps;

                HDC hDC = BeginPaint(hwnd, &ps);
                meter->DrawVolumeMeter(hDC);
                EndPaint(hwnd, &ps);

                break;
            }

        case WM_SIZE:
            {
                meter = GetVolumeMeterData(hwnd);
                meter->cx = LOWORD(lParam);
                meter->cy = HIWORD(lParam);

                HDC hDC = GetDC(hwnd);
                meter->DrawVolumeMeter(hDC);
                ReleaseDC(hwnd, hDC);
                break;
            }

        default:
            return DefWindowProc(hwnd, message, wParam, lParam);
    }

    return 0;
}