#pragma once
#include "GstPipelineBase.hpp"

class GstApp : public GstPipelineBase {
public:
  GstApp(GMainLoop *pMainLoop);
  virtual ~GstApp(void);
public:
  virtual gboolean message_eos (GstMessage *pMessage);
  virtual gboolean message_error (GstMessage *pMessage);
private:
  GMainLoop *pMainLoop_;
};
