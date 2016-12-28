#include "GstPipelineMessageBase.hpp"
GST_DEBUG_CATEGORY_EXTERN (gst_pipe);
#define GST_CAT_DEFAULT gst_pipe
static void show_message_in_detail (GstMessage * message);

GstPipelineMessageBase::GstPipelineMessageBase (void) : idBusWatch_(0) {}

GstPipelineMessageBase::~GstPipelineMessageBase (void) {
  if (idBusWatch_)
    g_source_remove (idBusWatch_);
}

bool GstPipelineMessageBase::initMessageHandler(GstElement* pPipeline) {
  do {
    if (pPipeline == NULL) break;
    if (!GST_IS_BIN(pPipeline)) break;

    GstBus *pBus = NULL;
    if ( (pBus = gst_element_get_bus (pPipeline)) == NULL )
      break;
    idBusWatch_ = gst_bus_add_watch (pBus, (GstBusFunc)message, (gpointer)this);
    gst_object_unref (pBus);

    return true;
  } while (0);
  return false;
}

gboolean GstPipelineMessageBase::message_unknown (GstMessage *pMessage) {
  return TRUE;
}

gboolean GstPipelineMessageBase::message_eos (GstMessage *pMessage) {
  return TRUE;
}

gboolean GstPipelineMessageBase::message_error (GstMessage *pMessage) {
  return TRUE;
}

gboolean GstPipelineMessageBase::message_warning (GstMessage *pMessage) {
  return TRUE;
}

gboolean GstPipelineMessageBase::message_info (GstMessage *pMessage) {
  return TRUE;
}

gboolean GstPipelineMessageBase::message_tag (GstMessage *pMessage) {
  return TRUE;
}

gboolean GstPipelineMessageBase::message_buffering (GstMessage *pMessage) {
  return TRUE;
}

gboolean GstPipelineMessageBase::message_state_changed (GstMessage *pMessage) {
  return TRUE;
}

gboolean GstPipelineMessageBase::message_state_dirty (GstMessage *pMessage) {
  return TRUE;
}

gboolean GstPipelineMessageBase::message_step_done (GstMessage *pMessage) {
  return TRUE;
}

gboolean GstPipelineMessageBase::message_clock_provide (GstMessage *pMessage) {
  return TRUE;
}

gboolean GstPipelineMessageBase::message_clock_lost (GstMessage *pMessage) {
  return TRUE;
}

gboolean GstPipelineMessageBase::message_new_clock (GstMessage *pMessage) {
  return TRUE;
}

gboolean GstPipelineMessageBase::message_structure_change (GstMessage *pMessage) {
  return TRUE;
}

gboolean GstPipelineMessageBase::message_stream_status (GstMessage *pMessage) {
  return TRUE;
}

gboolean GstPipelineMessageBase::message_application (GstMessage *pMessage) {
  return TRUE;
}

gboolean GstPipelineMessageBase::message_element (GstMessage *pMessage) {
  return TRUE;
}

gboolean GstPipelineMessageBase::message_segment_start (GstMessage *pMessage) {
  return TRUE;
}

gboolean GstPipelineMessageBase::message_segment_done (GstMessage *pMessage) {
  return TRUE;
}

gboolean GstPipelineMessageBase::message_duration_changed (GstMessage *pMessage) {
  return TRUE;
}

gboolean GstPipelineMessageBase::message_latency (GstMessage *pMessage) {
  return TRUE;
}

gboolean GstPipelineMessageBase::message_async_start (GstMessage *pMessage) {
  return TRUE;
}

gboolean GstPipelineMessageBase::message_async_done (GstMessage *pMessage) {
  return TRUE;
}

gboolean GstPipelineMessageBase::message_request_state (GstMessage *pMessage) {
  return TRUE;
}

gboolean GstPipelineMessageBase::message_step_start (GstMessage *pMessage) {
  return TRUE;
}

gboolean GstPipelineMessageBase::message_qos (GstMessage *pMessage) {
  return TRUE;
}

gboolean GstPipelineMessageBase::message_progress (GstMessage *pMessage) {
  return TRUE;
}

gboolean GstPipelineMessageBase::message_toc (GstMessage *pMessage) {
  return TRUE;
}

gboolean GstPipelineMessageBase::message_reset_time (GstMessage *pMessage) {
  return TRUE;
}

gboolean GstPipelineMessageBase::message_stream_start (GstMessage *pMessage) {
  return TRUE;
}

gboolean GstPipelineMessageBase::message_need_context (GstMessage *pMessage) {
  return TRUE;
}

gboolean GstPipelineMessageBase::message_have_context (GstMessage *pMessage) {
  return TRUE;
}

gboolean GstPipelineMessageBase::message_device_added (GstMessage *pMessage) {
  return TRUE;
}

gboolean GstPipelineMessageBase::message_device_removed (GstMessage *pMessage) {
  return TRUE;
}

gboolean GstPipelineMessageBase::message_property_notify (GstMessage *pMessage) {
  return TRUE;
}

gboolean GstPipelineMessageBase::message_stream_collection (GstMessage *pMessage) {
  return TRUE;
}

gboolean GstPipelineMessageBase::message_streams_selected (GstMessage *pMessage) {
  return TRUE;
}

gboolean GstPipelineMessageBase::message_redirect (GstMessage *pMessage) {
  return TRUE;
}

gboolean GstPipelineMessageBase::message (GstBus *pBus, GstMessage *pMessage, gpointer *data) {
  gboolean bRet = FALSE;
  GstPipelineMessageBase *p = reinterpret_cast<GstPipelineMessageBase*>(data);
  show_message_in_detail (pMessage);
  switch (GST_MESSAGE_TYPE(pMessage)) {
    case GST_MESSAGE_UNKNOWN:
      bRet = p->message_unknown (pMessage);
      break;
    case GST_MESSAGE_EOS:
      bRet = p->message_eos (pMessage);
      break;
    case GST_MESSAGE_ERROR:
      bRet = p->message_error (pMessage);
      break;
    case GST_MESSAGE_WARNING:
      bRet = p->message_warning (pMessage);
      break;
    case GST_MESSAGE_INFO:
      bRet = p->message_info (pMessage);
      break;
    case GST_MESSAGE_TAG:
      bRet = p->message_tag (pMessage);
      break;
    case GST_MESSAGE_BUFFERING:
      bRet = p->message_buffering (pMessage);
      break;
    case GST_MESSAGE_STATE_CHANGED:
      bRet = p->message_state_changed (pMessage);
      break;
    case GST_MESSAGE_STATE_DIRTY:
      bRet = p->message_state_dirty (pMessage);
      break;
    case GST_MESSAGE_STEP_DONE:
      bRet = p->message_step_done (pMessage);
      break;
    case GST_MESSAGE_CLOCK_PROVIDE:
      bRet = p->message_clock_provide (pMessage);
      break;
    case GST_MESSAGE_CLOCK_LOST:
      bRet = p->message_clock_lost (pMessage);
      break;
    case GST_MESSAGE_NEW_CLOCK:
      bRet = p->message_new_clock (pMessage);
      break;
    case GST_MESSAGE_STRUCTURE_CHANGE:
      bRet = p->message_structure_change (pMessage);
      break;
    case GST_MESSAGE_STREAM_STATUS:
      bRet = p->message_stream_status (pMessage);
      break;
    case GST_MESSAGE_APPLICATION:
      bRet = p->message_application (pMessage);
      break;
    case GST_MESSAGE_ELEMENT:
      bRet = p->message_element (pMessage);
      break;
    case GST_MESSAGE_SEGMENT_START:
      bRet = p->message_segment_start (pMessage);
      break;
    case GST_MESSAGE_SEGMENT_DONE:
      bRet = p->message_segment_done (pMessage);
      break;
    case GST_MESSAGE_DURATION_CHANGED:
      bRet = p->message_duration_changed (pMessage);
      break;
    case GST_MESSAGE_LATENCY:
      bRet = p->message_latency (pMessage);
      break;
    case GST_MESSAGE_ASYNC_START:
      bRet = p->message_async_start (pMessage);
      break;
    case GST_MESSAGE_ASYNC_DONE:
      bRet = p->message_async_done (pMessage);
      break;
    case GST_MESSAGE_REQUEST_STATE:
      bRet = p->message_request_state (pMessage);
      break;
    case GST_MESSAGE_STEP_START:
      bRet = p->message_step_start (pMessage);
      break;
    case GST_MESSAGE_QOS:
      bRet = p->message_qos (pMessage);
      break;
    case GST_MESSAGE_PROGRESS:
      bRet = p->message_progress (pMessage);
      break;
    case GST_MESSAGE_TOC:
      bRet = p->message_toc (pMessage);
      break;
    case GST_MESSAGE_RESET_TIME:
      bRet = p->message_reset_time (pMessage);
      break;
    case GST_MESSAGE_STREAM_START:
      bRet = p->message_stream_start (pMessage);
      break;
    case GST_MESSAGE_NEED_CONTEXT:
      bRet = p->message_need_context (pMessage);
      break;
    case GST_MESSAGE_HAVE_CONTEXT:
      bRet = p->message_have_context (pMessage);
      break;
    case GST_MESSAGE_DEVICE_ADDED:
      bRet = p->message_device_added (pMessage);
      break;
    case GST_MESSAGE_DEVICE_REMOVED:
      bRet = p->message_device_removed (pMessage);
      break;
    case GST_MESSAGE_PROPERTY_NOTIFY:
      bRet = p->message_property_notify (pMessage);
      break;
    case GST_MESSAGE_STREAM_COLLECTION:
      bRet = p->message_stream_collection (pMessage);
      break;
    case GST_MESSAGE_STREAMS_SELECTED:
      bRet = p->message_streams_selected (pMessage);
      break;
    case GST_MESSAGE_REDIRECT:
      bRet = p->message_redirect (pMessage);
      break;
    default:
      break;
  }
  return bRet;
}

static void
show_message_in_detail (GstMessage * message) {
  GstObject *src_obj;
  const GstStructure *s;
  guint32 seqnum;

  seqnum = gst_message_get_seqnum (message);

  s = gst_message_get_structure (message);

  src_obj = GST_MESSAGE_SRC (message);

  if (GST_IS_ELEMENT (src_obj)) {
    GST_TRACE ("Got message #%u from element \"%s\" (%s): ",
        (guint) seqnum, GST_ELEMENT_NAME (src_obj),
        GST_MESSAGE_TYPE_NAME (message));
  } else if (GST_IS_PAD (src_obj)) {
    GST_TRACE ("Got message #%u from pad \"%s:%s\" (%s): ",
        (guint) seqnum, GST_DEBUG_PAD_NAME (src_obj),
        GST_MESSAGE_TYPE_NAME (message));
  } else if (GST_IS_OBJECT (src_obj)) {
    GST_TRACE ("Got message #%u from object \"%s\" (%s): ",
        (guint) seqnum, GST_OBJECT_NAME (src_obj),
        GST_MESSAGE_TYPE_NAME (message));
  } else {
    GST_TRACE ("Got message #%u (%s): ", (guint) seqnum,
        GST_MESSAGE_TYPE_NAME (message));
  }

  if (s) {
    gchar *sstr;

    sstr = gst_structure_to_string (s);
    GST_TRACE ("%s\n", sstr);
    g_free (sstr);
  } else {
    GST_TRACE ("no message details\n");
  }
}
