// cl.exe overdraw_win.c /Feoverdraw.exe /link user32.lib gdi32.lib
// gcc overdraw_win.c -o overdraw.exe -lgdi32
#include <windows.h>

COLORREF cols[4]={RGB(255,0,0),RGB(0,0,255),RGB(0,255,0),RGB(255,255,0)};
int col=0,on=0,er=0,lx=0,ly=0;

LRESULT CALLBACK WndProc(HWND hw,UINT m,WPARAM w,LPARAM l){
    static HDC hdc,hdcMem;static HBITMAP bmp;static int W,H;
    switch(m){
        case WM_CREATE:{
            RECT r;GetClientRect(GetDesktopWindow(),&r);W=r.right;H=r.bottom;
            HDC dc=GetDC(0);hdc=CreateCompatibleDC(dc);bmp=CreateCompatibleBitmap(dc,W,H);
            SelectObject(hdc,bmp);BitBlt(hdc,0,0,W,H,dc,0,0,SRCCOPY);ReleaseDC(0,dc);
            SetWindowPos(hw,HWND_TOPMOST,0,0,W,H,SWP_SHOWWINDOW);
            SetLayeredWindowAttributes(hw,0,1,LWA_ALPHA);break;
        }
        case WM_LBUTTONDOWN:case WM_RBUTTONDOWN:
            on=1;lx=LOWORD(l);ly=HIWORD(l);er=m==WM_RBUTTONDOWN;break;
        case WM_MOUSEMOVE:if(!on)break;{
            int x=LOWORD(l),y=HIWORD(l);
            HDC dc=GetDC(hw);
            if(er){BitBlt(dc,x-15,y-15,30,30,hdc,x-15,y-15,SRCCOPY);}
            else{HPEN p=CreatePen(PS_SOLID,4,cols[col]);SelectObject(dc,p);MoveToEx(dc,lx,ly,0);LineTo(dc,x,y);DeleteObject(p);}
            ReleaseDC(hw,dc);lx=x;ly=y;
        }break;
        case WM_LBUTTONUP:case WM_RBUTTONUP:on=0;break;
        case WM_KEYDOWN:
            if(w==VK_ESCAPE)PostQuitMessage(0);
            if(w=='C'){InvalidateRect(hw,0,1);}
            if(w=='R')col=0;if(w=='B')col=1;if(w=='G')col=2;if(w=='Y')col=3;
            break;
        case WM_PAINT:{PAINTSTRUCT ps;BeginPaint(hw,&ps);BitBlt(ps.hdc,0,0,W,H,hdc,0,0,SRCCOPY);EndPaint(hw,&ps);}break;
        case WM_DESTROY:PostQuitMessage(0);break;
    }
    return DefWindowProcW(hw,m,w,l);
}

int WINAPI WinMain(HINSTANCE hInst,HINSTANCE hPrev,LPSTR cmd,int show){
    WNDCLASSW wc={0};wc.lpfnWndProc=WndProc;wc.hInstance=hInst;wc.hCursor=LoadCursor(0,IDC_CROSS);
    wc.lpszClassName=L"OverDraw";RegisterClassW(&wc);
    HWND hw=CreateWindowExW(WS_EX_LAYERED|WS_EX_TRANSPARENT|WS_EX_TOPMOST,L"OverDraw",L"OverDraw",
        WS_POPUP,0,0,400,300,0,0,hInst,0);
    ShowWindow(hw,SW_SHOWMAXIMIZED);
    MSG msg;while(GetMessage(&msg,0,0,0)){TranslateMessage(&msg);DispatchMessage(&msg);}
    return 0;
}
