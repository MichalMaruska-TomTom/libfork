#include <stdio.h>
#include <unistd.h>

#include <X11/Xlib.h>

#include <X11/fork_requests.h>
#include <X11/extensions/fork.h>


// read from stdin "a b", and "fork a to b"
void fork_from_stdin(Display *dpy, unsigned int device)
{
  int from, to;
  int count;

  while (EOF != (count = scanf("%d %d\n", &from, &to))) {
      // printf("items %d\n", count);
      if (count == 2) {
        printf("fork %d to %d\n", from, to);
        ForkSetFork(dpy, device, from, to);
      } else {
          // skip to \n
          char c;
          while ((c = getchar()) != '\n'){
              if (c == EOF) {
                break;
              }
          }
      }
  }
}



int main(int argc, char * const argv[])
{
  // use getenv(DISPLAY):
  int debug = 0;

  int next;
  while ((next = getopt(argc, argv, "d")) > -1) {
    if (next == '\?') {
      printf("unexpected option \n");
      return 1;
    } else if (next == 'd') {
      // printf("next: %d %c\n", optind, next);
      debug = 1;
    }
  }

  printf("now reading the config on stdin\n");
  Display* dpy = XOpenDisplay(NULL);
  unsigned int device = 3;

  fork_from_stdin(dpy, device);

  ForkConfigure(dpy, device, fork_configure_debug, debug);

  XFlush(dpy);
  return 0;
 }
