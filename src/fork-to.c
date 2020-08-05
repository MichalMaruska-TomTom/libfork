#define _GNU_SOURCE
#include <errno.h>

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <X11/Xlib.h>

// X11/extensions/
#include <fork.h>


// read from stdin "a b", and "fork a to b"
static
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

static
void usage(FILE* out)
{
  fprintf(out, "usage: %s [-d] [-k num] < {config-file}\n", program_invocation_short_name);
}


int main(int argc, char * const argv[])
{
  int debug = 0;
  unsigned int keyboard = 3;
  Display* dpy = NULL;

  int next;
  while ((next = getopt(argc, argv, "hdk:")) > -1) {
    if (next == '\?') {
      printf("unexpected option \n");
      usage(stderr);
      return 1;
    } else if (next == 'h') {
      usage(stdout);
      exit(0);
    } else if (next == 'd') {
      // printf("next: %d %c\n", optind, next);
      debug = 1;
    } else if (next == 'k') {
      // printf("next: %d %c\n", optind, next);
      keyboard = atoi(optarg);
    }
  }

  printf("now reading the config on stdin\n");
  dpy = XOpenDisplay(NULL); // uses getenv(DISPLAY):

  fork_from_stdin(dpy, keyboard);

  ForkConfigure(dpy, keyboard, fork_configure_debug, debug);

  XFlush(dpy);
  return 0;
 }
