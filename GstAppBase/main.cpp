#include <gst/gst.h>
#include "GstApp.hpp"

static void
print_pos (gpointer data) {
  gint64 npos = 0;
  gint64 ndur = 0;
  GstQuery *ppos = gst_query_new_position (GST_FORMAT_TIME);
  GstQuery *pdur = gst_query_new_duration (GST_FORMAT_TIME);
  GstPipelineBase *a = static_cast<GstPipelineBase*> (data);
  a->sendQuery (ppos);
  a->sendQuery (pdur);
  gst_query_parse_position (ppos, NULL, &npos);
  gst_query_parse_duration (pdur, NULL, &ndur);
  g_print ("%" GST_TIME_FORMAT "/%" GST_TIME_FORMAT "\r",
          GST_TIME_ARGS(npos), GST_TIME_ARGS(ndur));
}

static gboolean
cb_timeout (gpointer data) {
  static guint count = 0;
  GstPipelineBase *a = static_cast<GstPipelineBase*> (data);
  if (++count == 10)
    a->sendEvent (gst_event_new_eos());
  else
    print_pos (data);

  return count == 10 ? FALSE : TRUE;
}

int main (int argc, char ** argv) {
  GMainLoop *pMainLoop = NULL;
  gst_init (&argc, &argv);

  pMainLoop = g_main_loop_new (NULL, TRUE);

  GstApp a(pMainLoop);
  if (!a.start ())
    return -1;

  g_timeout_add_seconds (1, cb_timeout, &a);
  g_main_loop_run (pMainLoop);

  a.stop ();

  if (pMainLoop != NULL) g_main_loop_unref (pMainLoop);

  return 0;
}
