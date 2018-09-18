#include <X11/Xlib.h>

#include <X11/fork_requests.h>
#include <X11/extensions/fork.h>

// todo:
// read from stdin "a b", and "fork a to b"

int main()
{
  // use getenv(DISPLAY):
  Display* dpy = XOpenDisplay(NULL);
  unsigned int device = 3;
  // todo
  //getopt -d number  .. the keyboard
  //
  // l f-> hyper
  ForkSetFork(dpy, device, 41, 61);
  ForkSetFork(dpy, device, 46, 61);

  // k a -> group 2
  ForkSetFork(dpy, device, 38, 66);
  ForkSetFork(dpy, device, 45, 66);

  // m c -> group 2
  ForkSetFork(dpy, device, 58, 109);
  ForkSetFork(dpy, device, 54, 109);

  // d j -> group device
  ForkSetFork(dpy, device, 40, 109);
  ForkSetFork(dpy, device, 44, 109);


  // s -> alt
  ForkSetFork(dpy, device, 39, 192);

  // space v -> shift
  ForkSetFork(dpy, device, 65, 37);
  ForkSetFork(dpy, device, 55, 37);
  ForkSetFork(dpy, device, 47, 37); // ??


  // meta/esc -> meta:
  // 64 must be Escape, and fork to some Meta.
  // Meta is

  // Control 04
  // shift   01
  // caps    02
  // 08?
  //  alt   20
  // hyper  80
  ForkSetFork(dpy, device, 64, 205);

  ForkConfigure(dpy, device, fork_configure_debug, 0);
  XFlush(dpy);
  return 0;
 }
