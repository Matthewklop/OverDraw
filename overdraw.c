#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>
int main(){
    Display*d=XOpenDisplay(0);int s=DefaultScreen(d);
    int W=DisplayWidth(d,s),H=DisplayHeight(d,s);
    Window root=RootWindow(d,s);
    XImage*img=XGetImage(d,root,0,0,W,H,AllPlanes,ZPixmap);
    Pixmap bg=XCreatePixmap(d,root,W,H,DefaultDepth(d,s));
    GC bgc=XCreateGC(d,bg,0,0);XPutImage(d,bg,bgc,img,0,0,0,0,W,H);XFreeGC(d,bgc);XDestroyImage(img);
    XSetWindowAttributes aw={.background_pixmap=bg,.event_mask=KeyPressMask|PointerMotionMask|ButtonPressMask|ButtonReleaseMask};
    Window w=XCreateWindow(d,root,0,0,W,H,0,0,InputOutput,CopyFromParent,CWBackPixmap|CWEventMask,&aw);
    Atom wm=XInternAtom(d,"_NET_WM_STATE",0),fs=XInternAtom(d,"_NET_WM_STATE_FULLSCREEN",0),ab=XInternAtom(d,"_NET_WM_STATE_ABOVE",0);
    Atom st[2]={fs,ab};XChangeProperty(d,w,wm,XA_ATOM,32,PropModeReplace,(unsigned char*)st,2);
    XMapWindow(d,w);XFlush(d);
    XGrabKeyboard(d,w,1,GrabModeAsync,GrabModeAsync,CurrentTime);
    GC g=XCreateGC(d,w,0,0);XSetForeground(d,g,0xFF0000);XSetLineAttributes(d,g,4,LineSolid,CapRound,JoinRound);
    unsigned int cols[4]={0xFF0000,0x0000FF,0x00FF00,0xFFFF00};
    XEvent e;int on=0,er=0,color=0,lx=0,ly=0;
    while(1){
        XNextEvent(d,&e);
        if(e.type==MotionNotify&&on){
            if(er){XCopyArea(d,bg,w,g,e.xmotion.x-10,e.xmotion.y-10,20,20,e.xmotion.x-10,e.xmotion.y-10);XFlush(d);}
            else{XSetForeground(d,g,cols[color]);XDrawLine(d,w,g,lx,ly,e.xmotion.x,e.xmotion.y);lx=e.xmotion.x;ly=e.xmotion.y;XFlush(d);}
        }else if(e.type==ButtonPress){on=1;lx=e.xbutton.x;ly=e.xbutton.y;er=e.xbutton.button==3;XSetForeground(d,g,cols[color]);XFillArc(d,w,g,lx-2,ly-2,4,4,0,360*64);XFlush(d);}
        else if(e.type==ButtonRelease){on=0;}
        else if(e.type==KeyPress){
            int k=XLookupKeysym(&e.xkey,0);
            if(k==XK_Escape)break;
            if(k==XK_c){XClearWindow(d,w);}
            if(k==XK_r&&!on){color=0;XSetForeground(d,g,cols[0]);}
            if(k==XK_b&&!on){color=1;XSetForeground(d,g,cols[1]);}
            if(k==XK_g&&!on){color=2;XSetForeground(d,g,cols[2]);}
            if(k==XK_y&&!on){color=3;XSetForeground(d,g,cols[3]);}
        }
    }
    XFreePixmap(d,bg);XCloseDisplay(d);
}
