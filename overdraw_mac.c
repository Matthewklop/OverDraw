// gcc overdraw_mac.c -o overdraw -framework Cocoa -framework CoreGraphics
// macOS version — transparent overlay, same controls
#include <Cocoa/Cocoa.h>
#include <CoreGraphics/CoreGraphics.h>

@interface OverDrawView : NSView {
    CGImageRef bg;
    int col,on,er,lx,ly;
    NSColor *cols[4];
}
@end

@implementation OverDrawView
- (id)initWithFrame:(NSRect)f{
    self=[super initWithFrame:f];
    col=0;on=0;er=0;
    cols[0]=[NSColor redColor];cols[1]=[NSColor blueColor];
    cols[2]=[NSColor greenColor];cols[3]=[NSColor yellowColor];
    // Capture desktop
    CGImageRef img=CGDisplayCreateImage(CGMainDisplayID());
    bg=CGImageCreateCopy(img);CGImageRelease(img);
    return self;
}
- (void)drawRect:(NSRect)r{
    CGContextRef ctx=[[NSGraphicsContext currentContext] CGContext];
    if(bg){
        CGContextDrawImage(ctx,self.bounds,bg);
    }
}
- (void)mouseDown:(NSEvent*)e{on=1;er=0;NSPoint p=e.locationInWindow;lx=p.x;ly=p.y;}
- (void)rightMouseDown:(NSEvent*)e{on=1;er=1;NSPoint p=e.locationInWindow;lx=p.x;ly=p.y;}
- (void)mouseUp:(NSEvent*)e{on=0;}
- (void)rightMouseUp:(NSEvent*)e{on=0;}
- (void)mouseDragged:(NSEvent*)e{
    if(!on)return;
    NSPoint p=e.locationInWindow;int x=p.x,y=p.y;
    CGContextRef ctx=[[NSGraphicsContext currentContext] CGContext];
    if(er){
        CGContextDrawImage(ctx,CGRectMake(x-15,y-15,30,30),bg);
    }else{
        CGContextSetStrokeColorWithColor(ctx,[cols[col] CGColor]);
        CGContextSetLineWidth(ctx,4);
        CGContextMoveToPoint(ctx,lx,ly);
        CGContextAddLineToPoint(ctx,x,y);
        CGContextStrokePath(ctx);
    }
    lx=x;ly=y;
    [self setNeedsDisplay:NO];
}
- (void)keyDown:(NSEvent*)e{
    NSString *k=e.characters;
    if([k isEqualToString:@"\e"])[NSApp terminate:self];
    if([k isEqualToString:@"c"]){
        [self setNeedsDisplay:YES];
    }
    if([k isEqualToString:@"r"])col=0;
    if([k isEqualToString:@"b"])col=1;
    if([k isEqualToString:@"g"])col=2;
    if([k isEqualToString:@"y"])col=3;
}
- (BOOL)acceptsFirstResponder{return YES;}
@end

int main(){
    @autoreleasepool{
        NSApp=[NSApplication sharedApplication];
        NSRect r=NSScreen.mainScreen.frame;
        NSWindow *win=[[NSWindow alloc] initWithContentRect:r styleMask:NSWindowStyleMaskBorderless
            backing:NSBackingStoreBuffered defer:NO];
        win.level=NSMainMenuWindowLevel+1;
        win.backgroundColor=[NSColor clearColor];
        win.opaque=NO;
        win.ignoresMouseEvents=NO;
        OverDrawView *view=[[OverDrawView alloc] initWithFrame:r];
        win.contentView=view;
        [win makeFirstResponder:view];
        [win makeKeyAndOrderFront:nil];
        [NSApp run];
    }
    return 0;
}
