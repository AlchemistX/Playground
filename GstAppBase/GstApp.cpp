#include "GstApp.hpp"

gboolean GstApp::handleBusMessage (GstBus *pBus, GstMessage *pMessage) {
  gboolean ret = TRUE;
  switch (GST_MESSAGE_TYPE (pMessage)) {
    case GST_MESSAGE_EOS: {
      PRINT ("End-of-stream\n");
      ret = FALSE;
      break;
    }
    case GST_MESSAGE_ERROR: {
      gchar *debug;
      GError *err;

      gst_message_parse_error (pMessage, &err, &debug);
      PRINTERR (_("Debugging info: %s\n"), (debug) ? debug : "none");
      g_free (debug);

      PRINT (_("Error: %s\n"), err->message);
      g_error_free (err);

      ret = FALSE;
      break;
    }
    default:
      ret = TRUE;
      break;
  }

  return ret;
}
