#pragma once
#include <gst/gst.h>
#include "GstPipelineMessageBase.hpp"

class GstPipelineBase : public GstPipelineMessageBase {
protected:
  GstPipelineBase (void);
  virtual ~GstPipelineBase (void);
public: // Construct/get/set elements in the pipeline.
 bool build (const char * szPipeline);
 GstElement* get (const char * szElementName);
public: // Manipulate the pipeline.
  GstStateChangeReturn start (void);
  GstStateChangeReturn stop (void);
  gboolean sendQuery (GstQuery *pQuery);
  gboolean sendEvent (GstEvent *pEvent);
protected:
  GstElement *pPipeline_;
};
