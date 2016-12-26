#pragma once
#include <gst/gst.h>
#include <glib/gi18n.h>
#define PRINT g_print
#define PRINTERR g_printerr

class GstAppBase {
protected:
  GstAppBase (void)
    : pPipeline_(NULL)
  {}
  virtual ~GstAppBase (void) {
    if (pPipeline_ != NULL)
      gst_object_unref (pPipeline_);
  }
public:
  GstStateChangeReturn startPipeline (void) {
    do {
      if (pPipeline_ == NULL) break;
      return gst_element_set_state (pPipeline_, GST_STATE_PLAYING);
    } while (0);
    return GST_STATE_CHANGE_FAILURE;
  }

  GstStateChangeReturn stopPipeline (void) {
    do {
      if (pPipeline_ == NULL) break;
      return gst_element_set_state (pPipeline_, GST_STATE_PLAYING);
    } while (0);
    return GST_STATE_CHANGE_FAILURE;
  }

  gboolean queryPipeline (GstQuery *pQuery) {
    return gst_element_query (GST_ELEMENT(pPipeline_), pQuery);
  }

  gboolean sendEventPipeline (GstEvent *pEvent) {
    return gst_element_send_event (GST_ELEMENT(pPipeline_), pEvent);
  }

  bool buildPipeline (const char * szPipeline) {
    do {
      if (pPipeline_ != NULL) break;

      GError *pError = NULL;
      if ( (pPipeline_ = gst_parse_launch (szPipeline, &pError)) == NULL )
        break;
      if (pError != NULL) {
        PRINT (_("Error: %s\n"), pError->message);
        g_error_free(pError);
        break;
      }
      return true;
    } while (0);
    return false;
  }

  bool setBusHandler (GMainLoop *pMainLoop) {
    do {
      if (pPipeline_ == NULL) break;

      GstBus *pBus = NULL;
      if ( (pBus = gst_element_get_bus (pPipeline_)) == NULL )
        break;
      gst_bus_add_watch (pBus, handleBusMessage1, this);
      gst_object_unref (pBus);
      return true;
    } while (0);
    return false;
  }

public:
  virtual gboolean handleBusMessage (GstBus *pBus, GstMessage *pMessage) {
    return FALSE;
  }
public:
  static gboolean handleBusMessage1 (GstBus *pBus, GstMessage *pMessage, gpointer data);
protected:
  GstElement *pPipeline_;
};
