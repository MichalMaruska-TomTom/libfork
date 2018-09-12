#include <X11/Xlib.h>
#include <X11/extensions/fork.h>

// todo:
// read from stdin "a b", and "fork a to b"

int main()
{
  Display* x=XOpenDisplay(":0");
  // l f-> hyper
  ForkSetFork(x, 3, 41, 61);
  ForkSetFork(x, 3, 46, 61);

  // k a -> group 2
  ForkSetFork(x, 3, 38, 66);
  ForkSetFork(x, 3, 45, 66);

  // m c -> group 2
  ForkSetFork(x, 3, 58, 109);
  ForkSetFork(x, 3, 54, 109);

  // d j -> group 3
  ForkSetFork(x, 3, 40, 109);
  ForkSetFork(x, 3, 44, 109);


  // s -> alt
  ForkSetFork(x, 3, 39, 192);

  // space v -> shift
  ForkSetFork(x, 3, 65, 37);
  ForkSetFork(x, 3, 55, 37);
  ForkSetFork(x, 3, 47, 37); // ??


  // meta/esc -> meta:
  // 64 must be Escape, and fork to some Meta.
  // Meta is

  // Control 04
  // shift   01
  // caps    02
  // 08?
  //  alt   20
  // hyper  80
  ForkSetFork(x, 3, 64, 205);
  XFlush(x);
  // XClose(x);

  return 0;
 }
