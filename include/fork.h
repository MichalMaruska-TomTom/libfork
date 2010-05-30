#ifndef FORK_H
#define FORK_H

/* server */
/* #include <X11/Xlibint.h> */

/* XkbUseCoreKbd */
/* this needs stuff from Xlibint.h */
/* #include <X11/XKBlibint.h> */


/* stuff shared with the server */
#include <xorg/fork_requests.h>


extern	Bool    ForkSetFork(
   Display *		/* dpy */,
   unsigned int 		/* deviceSpec */,
   KeyCode		        /* code */,
   KeyCode		        /* forkcode */
   );



/* the request (sub-)structure */
extern Bool     ForkSetForkRepeat(
   Display *		/* dpy */,
   unsigned int         /* deviceSpec */,
   KeyCode              /* code */,
   Bool		        /* forkcode */
   );



#if 1
extern Bool
ForkGetLastEvents(Display *dpy, unsigned int deviceSpec, int count,
		  int* returned, archived_event** events);
#endif








extern int
ForkGetConfigure(Display *dpy,unsigned int device,int what, int* ret);
//   unsigned int deviceSpec,

extern int
ForkGetConfigureKey(Display *dpy, unsigned int device, int what, KeyCode code, int* ret);

extern int
ForkGetConfigureKeyTwin(Display *dpy, unsigned int device, int what, KeyCode code,
			KeyCode twin, int* ret);




extern Bool ForkConfigure(
   Display *dpy,
   unsigned int deviceSpec,
   int what,
   int value);


extern Bool
ForkConfigureKey(Display *dpy,
		 unsigned int device, int what, KeyCode code, int value);

extern Bool
ForkConfigureKeyTwin(Display *dpy, unsigned int device,
		     int what, KeyCode code, KeyCode twin, int value);



#endif /* FORK_H */


