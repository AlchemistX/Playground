#pragma once
#include <gst/gst.h>

class GstPipelineMessageBase {
protected:
  GstPipelineMessageBase (void);
  virtual ~GstPipelineMessageBase (void);
public:
  bool initMessageHandler(GstElement* pPipeline);
public:
  virtual gboolean message_unknown (GstMessage *pMessage);
  virtual gboolean message_eos (GstMessage *pMessage);
  virtual gboolean message_error (GstMessage *pMessage);
  virtual gboolean message_warning (GstMessage *pMessage);
  virtual gboolean message_info (GstMessage *pMessage);
  virtual gboolean message_tag (GstMessage *pMessage);
  virtual gboolean message_buffering (GstMessage *pMessage);
  virtual gboolean message_state_changed (GstMessage *pMessage);
  virtual gboolean message_state_dirty (GstMessage *pMessage);
  virtual gboolean message_step_done (GstMessage *pMessage);
  virtual gboolean message_clock_provide (GstMessage *pMessage);
  virtual gboolean message_clock_lost (GstMessage *pMessage);
  virtual gboolean message_new_clock (GstMessage *pMessage);
  virtual gboolean message_structure_change (GstMessage *pMessage);
  virtual gboolean message_stream_status (GstMessage *pMessage);
  virtual gboolean message_application (GstMessage *pMessage);
  virtual gboolean message_element (GstMessage *pMessage);
  virtual gboolean message_segment_start (GstMessage *pMessage);
  virtual gboolean message_segment_done (GstMessage *pMessage);
  virtual gboolean message_duration_changed (GstMessage *pMessage);
  virtual gboolean message_latency (GstMessage *pMessage);
  virtual gboolean message_async_start (GstMessage *pMessage);
  virtual gboolean message_async_done (GstMessage *pMessage);
  virtual gboolean message_request_state (GstMessage *pMessage);
  virtual gboolean message_step_start (GstMessage *pMessage);
  virtual gboolean message_qos (GstMessage *pMessage);
  virtual gboolean message_progress (GstMessage *pMessage);
  virtual gboolean message_toc (GstMessage *pMessage);
  virtual gboolean message_reset_time (GstMessage *pMessage);
  virtual gboolean message_stream_start (GstMessage *pMessage);
  virtual gboolean message_need_context (GstMessage *pMessage);
  virtual gboolean message_have_context (GstMessage *pMessage);
  virtual gboolean message_device_added (GstMessage *pMessage);
  virtual gboolean message_device_removed (GstMessage *pMessage);
  virtual gboolean message_property_notify (GstMessage *pMessage);
  virtual gboolean message_stream_collection (GstMessage *pMessage);
  virtual gboolean message_streams_selected (GstMessage *pMessage);
  virtual gboolean message_redirect (GstMessage *pMessage);
public:
  static gboolean message (GstBus *pBus, GstMessage *pMessage, gpointer *data);
private:
  guint idBusWatch_;
};
