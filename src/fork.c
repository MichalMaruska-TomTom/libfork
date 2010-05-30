
#include <X11/Xlib.h>

#include <X11/XKBlib.h>
#include <X11/extensions/XKB.h>


/* shared with the server-side plugin: */
#include <xorg/fork_requests.h>
#include <X11/extensions/XKBproto.h>

#include "fork.h"
#include <stdlib.h>
#include <string.h>

extern
void XkbFreePipelineList(XkbPipelineListPtr list);
extern
Bool XkbPluginConfigure(Display *dpy, unsigned int deviceSpec, int plugin, int data[5]);


/* dpy->xkb_info->codes    needs -I /p/xfree-4.3.99.901/work/xc/lib/X11/XKBlibint.h */

static unsigned int
find_plugin(Display* dpy, unsigned int device, char* name)
{
   int i;
   XkbPipelineListPtr p = XkbListPipeline(dpy, device);
   
   if (!p)
      exit(0);
   
#if DEBUG
   fprintf(stderr, "%d plugin%s in the pipeline\n",
           p->num_plugins,
           (p->num_plugins==0)?"":"s");
#endif
   
   for(i= 0; i < p->num_plugins; i++)
     {                       /* flags ? */

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


// return the # of the "fork" plugin
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


#if 0
/* todo: put in the core! */
Bool
XkbPluginConfig(Display* dpy, unsigned int deviceSpec, char* plugin_name, int len, char* data)
{
   return XkbPluginCommand(dpy, deviceSpec, plugin_name, len, data, False, NULL, NULL, False);
}


/* data is  COMMAND (4 bytes)  which encodes the # of args & type of config (set/get) */
Bool
XkbPluginGetConfig(Display* dpy, unsigned int deviceSpec, char* plugin_name, int len, char* data)
{
   int value;
   /* fixme: check for errors! */
   /* True not False!  we want to wait for answer!  */
   XkbPluginCommand(dpy, deviceSpec, plugin_name, len, data, True, &value, NULL, True);
   return value;
}
#endif


/* Since there are similar/same options  either Global or Local, or Twin-related (specific to 2 keys),
   the command -- data[0] is composed of the indication G or L in 2 lower bits, and
   the option specifiction is in the rest (shifted <<2)   */

/* todo: device! */
Bool 
ForkConfigure(Display *dpy, unsigned int device, int what, int value)
{

   int data[5];
   data[0] = what << 2 | 0;     /* mmc:  why? */
   data[1] = value;
   
   return XkbPluginConfigure(dpy, device, fork_plugin_id(dpy, device), data);
}


int
ForkGetConfigure(Display *dpy, unsigned int device, int what, int* ret)
{
   int data[5];
   data[0] = what << 2 | 0;     /* mmc:  why? */
   int rets[3];
   
   int status = XkbPluginGetConfigure(dpy, device, fork_plugin_id(dpy, device), data, rets);
   *ret = rets[0];
   return status;
}


/* config of 2 keys: overlap between them, or ?? whatever !! */
Bool 
ForkConfigureKeyTwin(Display *dpy, unsigned int device, int what,
		     KeyCode code, KeyCode twin, int value)
{
   int data[5];
   data[0] = what << 2 | 2;     /* mmc:  why? */
   data[1] = code;
   data[2] = twin;
   data[3] = value;
   
   return XkbPluginConfigure(dpy, device, fork_plugin_id(dpy, device), data);
}

int
ForkGetConfigureKeyTwin(Display *dpy, unsigned int device, int what, KeyCode code, KeyCode twin, int* ret)
{
   int data[5];
   data[0] = what << 2 | 2;     /* mmc:  why? */
   data[1] = code;
   data[2] = twin;

   int rets[3];

   int status = XkbPluginGetConfigure(dpy, device, fork_plugin_id(dpy, device),  data, rets);
   *ret = rets[0];
   return status;
}





Bool 
ForkConfigureKey(Display *dpy, unsigned int device, int what, KeyCode code, int value)
{
   int data[5];
   data[0] = what << 2 | 1;     /* mmc:  why? */
   data[1] = code;
   data[2] = value;
   
   return XkbPluginConfigure(dpy, device, fork_plugin_id(dpy, device), data);
}


ForkGetConfigureKey(Display *dpy, unsigned int device, int what, KeyCode code, int* ret)
{
   int data[5];
   data[0] = what << 2 | 1;     /* mmc:  why? */
   data[1] = code;

   int rets[3];

   int status = XkbPluginGetConfigure(dpy, device, fork_plugin_id(dpy, device), data, rets);
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

/* Reading XReply: XKB /x/cvs/xfree/xc/lib/X11/XKBRdBuf.c  */


/* fixme:   GetReq  adds  x.....Req !
 *     and wants   X_.....    the number of the request!
 *
 * */

Bool                            /* todo:   `PluginCommand_get_reply' */
ForkGetLastEvents(Display *dpy, unsigned int device, int count,
		  int* returned, archived_event** events)
{
   fork_events_reply* reply;
   int answer_len;

   /* The magic command: */
   int data[2]; /* = "abcd";              fixme:count!  nothning */
   /* int len = strlen(data);*/
   
   /* fixme: byte-swap! */
   data[0] = fork_client_dump_keys; /* what << 2 | 0;*/
   data[1] = count;

   Status status = XkbPluginCommand(dpy, device,
				    fork_plugin_id(dpy, device),
				    2 * sizeof(int), data,
                                    &answer_len, &reply);

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

