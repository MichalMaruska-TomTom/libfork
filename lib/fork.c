#include <X11/Xlib.h>
#include <X11/XKBlib.h>
#include <X11/extensions/XKB.h>
/* dpy->xkb_info->codes    needs -I /p/xfree-4.3.99.901/work/xc/lib/X11/XKBlibint.h */


/* shared with the server-side plugin: */
#include <X11/fork_requests.h>
#include <X11/extensions/XKBproto.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "fork.h"

/* return the ID of the plugin NAME, associated with XI DEVICE,
 * or 0 if not found. */
static unsigned int
find_plugin(Display* dpy, unsigned int device, const char* name)
{
    int i;
    XkbPipelineListPtr p = XkbListPipeline(dpy, device);

    assert (p);
#if DEBUG
    fprintf(stderr, "%d plugin%s in the pipeline\n",
            p->num_plugins,
            (p->num_plugins==0)?"":"s");
#endif

    for(i= 0; i < p->num_plugins; i++)
    {
        if (strcmp(name, p->plugins[i].name) == 0)
        {
            unsigned int res = p->plugins[i].id;
            XkbFreePipelineList(p);
            return res;
        }
    }
    XkbFreePipelineList(p);
    return 0;
}


// return the id of the "fork" plugin
static unsigned int
fork_plugin_id(Display* dpy, unsigned int device)
{
    static unsigned int plugin = 0;

    if (plugin)
        return plugin;
    else
    {
        return plugin = find_plugin(dpy, device, FORK_PLUGIN_NAME);
    }
}

/**
   Since there are similar/same options either Global or Local, or Twin-related
   (specific to 2 keys), the command -- data[0] is composed of the indication G
   or L in 2 lower bits, and the option specifiction is in the rest (shifted
   <<2)
**/
#define GLOBAL_OPTION 0
#define LOCAL_OPTION 1
#define TWIN_OPTION 2

Bool
ForkConfigure(Display *dpy, unsigned int device, int what, int value)
{

   int data[5];
   data[0] = what << 2 | GLOBAL_OPTION;
   data[1] = value;

   return XkbPluginConfigure(dpy, device, fork_plugin_id(dpy, device), data);
}


int
ForkGetConfigure(Display *dpy, unsigned int device, int what, int* ret)
{
   int data[5];
   int rets[3];
   int status;

   data[0] = what << 2 | GLOBAL_OPTION;
   status = XkbPluginGetConfigure(dpy, device, fork_plugin_id(dpy, device), data, rets);
   *ret = rets[0];
   return status;
}


/* config of 2 keys: overlap between them, or ?? whatever !! */
Bool
ForkConfigureKeyTwin(Display *dpy, unsigned int device, int what,
                     KeyCode code, KeyCode twin, int value)
{
   int data[5];
   data[0] = what << 2 | TWIN_OPTION;
   data[1] = code;
   data[2] = twin;
   data[3] = value;

   return XkbPluginConfigure(dpy, device, fork_plugin_id(dpy, device), data);
}

int
ForkGetConfigureKeyTwin(Display *dpy, unsigned int device, int what, KeyCode code, KeyCode twin, int* ret)
{
   int data[5];
   int rets[3];
   int status;

   data[0] = what << 2 | TWIN_OPTION;
   data[1] = code;
   data[2] = twin;
   status = XkbPluginGetConfigure(dpy, device, fork_plugin_id(dpy, device),  data, rets);
   *ret = rets[0];
   return status;
}

Bool
ForkConfigureKey(Display *dpy, unsigned int device, int what, KeyCode code,
                 int value)
{
   int data[5];
   data[0] = what << 2 | LOCAL_OPTION;
   data[1] = code;
   data[2] = value;

   return XkbPluginConfigure(dpy, device, fork_plugin_id(dpy, device), data);
}


int
ForkGetConfigureKey(Display *dpy, unsigned int device, int what, KeyCode code,
                    int* ret)
{
   int data[5];
   int rets[3];

   int status;
   data[0] = what << 2 | LOCAL_OPTION;
   data[1] = code;

   status = XkbPluginGetConfigure(dpy, device, fork_plugin_id(dpy, device), data, rets);
   *ret = rets[0];
   return status;
}


/*  */



Bool
ForkSetFork(Display *dpy, unsigned int deviceSpec, KeyCode code, KeyCode fork)
{
   /* deviceSpec */
  ForkConfigureKey(dpy, deviceSpec, fork_configure_key_fork, code, fork); /*  Boll -> int -> int16 */
  return True;
}



Bool
ForkSetForkRepeat(Display *dpy, unsigned int deviceSpec, KeyCode code, Bool repeat)
{
   /* deviceSpec */
   ForkConfigureKey(dpy, deviceSpec,fork_configure_key_fork_repeat, code, repeat);
   /*  Boll -> int -> int16 */
   return True;
}

Bool
ForkSetLastKeysCount(Display *dpy, unsigned int deviceSpec, int count)
{
  return ForkConfigure(dpy, deviceSpec, fork_configure_last_events, count);
}


/* Reading XReply, copied from XKB xc/lib/X11/XKBRdBuf.c */

/* fixme:   GetReq  adds  x.....Req !
 *     and wants   X_.....    the number of the request!
 */

Bool                            /* todo:   `PluginCommand_get_reply' */
ForkGetLastEvents(Display *dpy, unsigned int device, int count,
                  int* returned, archived_event** events)
{
    fork_events_reply* reply;
    int answer_len;
    Status status;
    /* The magic command: */
    int data[2]; /* = "abcd";              fixme:count!  nothning */
    /* int len = strlen(data);*/

    /* fixme: byte-swap! */
    data[0] = fork_client_dump_keys; /* what << 2 | 0;*/
    data[1] = count;

    status = XkbPluginCommand(dpy, device,
                              fork_plugin_id(dpy, device),
                              2 * sizeof(int), (char*) data, /* fixme! */
                              &answer_len, (char**) &reply);  /* fixme! */

    /* todo! */
    /* Check that the # of events < count */
    if (status == Success)
    {
        *returned = answer_len / sizeof(archived_event);


        printf("got %d  == %d events.\n",  *returned, reply->count);
        /* fixme: */
        *events = malloc(*returned * sizeof(archived_event));
        memcpy(*events, reply->e, *returned * sizeof(archived_event));
        /* XKBFree ? */
        XFree(reply);
#if 0
        /* extract the events! */
        int i;
        for(i = 0; i < *returned; i++)
        {
        }
#endif
    }
    return True;
}
