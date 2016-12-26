#pragma once
#include "GstAppBase.hpp"

class GstApp : public GstAppBase {
public:
  GstApp(void) {}
  virtual ~GstApp(void) {}
public:
  virtual gboolean handleBusMessage (GstBus *pBus, GstMessage *pMessage);
};
