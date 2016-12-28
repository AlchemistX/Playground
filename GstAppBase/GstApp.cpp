#include "GstApp.hpp"
GST_DEBUG_CATEGORY_EXTERN (gst_pipe);
#define GST_CAT_DEFAULT gst_pipe

GstApp::GstApp(GMainLoop *pMainLoop) : pMainLoop_(pMainLoop) {
  build ("playbin uri=https://www.freedesktop.org/software/gstreamer-sdk/data/media/sintel_cropped_multilingual.webm");
}

GstApp::~GstApp(void) {
}

gboolean GstApp::message_eos (GstMessage *pMessage) {
  GST_INFO ("End-of-stream\n");
  g_main_loop_quit (pMainLoop_);
  return TRUE;
}

gboolean GstApp::message_error (GstMessage *pMessage) {
  gchar *debug;
  GError *err;

  gst_message_parse_error (pMessage, &err, &debug);
  GST_ERROR ("Debugging info: %s\n", (debug) ? debug : "none");
  g_free (debug);

  GST_ERROR ("Error: %s\n", err->message);
  g_error_free (err);
  g_main_loop_quit (pMainLoop_);
  return TRUE;
}

