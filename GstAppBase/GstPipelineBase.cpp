#include "GstPipelineBase.hpp"
GST_DEBUG_CATEGORY (gst_pipe);
#define GST_CAT_DEFAULT gst_pipe

GstPipelineBase::GstPipelineBase (void)
  : pPipeline_(NULL) {
  GST_DEBUG_CATEGORY_INIT (gst_pipe, "gst_pipe", 0, "GST_PIPE");
}

GstPipelineBase::~GstPipelineBase (void) {
  if (pPipeline_ != NULL) {
    gst_object_unref (pPipeline_);
    pPipeline_ = NULL;
  }
}

bool GstPipelineBase::build (const char * szPipeline) {
  do {
    if (pPipeline_ != NULL) break;

    { // 1. Build pipeline
      GError *pError = NULL;
      GST_INFO ("Launching : %s", szPipeline);
      if ( (pPipeline_ = gst_parse_launch (szPipeline, &pError)) == NULL ) {
        GST_ERROR ("Launching is failed.");
        break;
      }
      if (pError != NULL) {
        GST_ERROR ("Error: %s\n", pError->message);
        g_error_free(pError);
        break;
      }
    }

    { // 2. Connect handlers to the bus of the pipeline.
      if (initMessageHandler (pPipeline_) == false)
        break;
    }
    return true;
  } while (0);
  return false;
}

GstElement* GstPipelineBase::get (const char * szElementName) {
  do {
    if (pPipeline_ == NULL) break;
    if (!GST_IS_BIN(pPipeline_)) break;
    return gst_bin_get_by_name (GST_BIN(pPipeline_), szElementName);
  } while (0);
  return NULL;
}

GstStateChangeReturn GstPipelineBase::start (void) {
  do {
    if (pPipeline_ == NULL) break;
    return gst_element_set_state (pPipeline_, GST_STATE_PLAYING);
  } while (0);
  return GST_STATE_CHANGE_FAILURE;
}

GstStateChangeReturn GstPipelineBase::stop (void) {
  do {
    if (pPipeline_ == NULL) break;
    return gst_element_set_state (pPipeline_, GST_STATE_NULL);
  } while (0);
  return GST_STATE_CHANGE_FAILURE;
}

gboolean GstPipelineBase::sendQuery (GstQuery *pQuery) {
  return gst_element_query (GST_ELEMENT(pPipeline_), pQuery);
}

gboolean GstPipelineBase::sendEvent (GstEvent *pEvent) {
  return gst_element_send_event (GST_ELEMENT(pPipeline_), pEvent);
}
