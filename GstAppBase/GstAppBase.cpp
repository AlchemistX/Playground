#include "GstAppBase.hpp"
void show_message_in_detail (GstMessage * message) {
  GstObject *src_obj;
  const GstStructure *s;
  guint32 seqnum;

  seqnum = gst_message_get_seqnum (message);

  s = gst_message_get_structure (message);

  src_obj = GST_MESSAGE_SRC (message);

  if (GST_IS_ELEMENT (src_obj)) {
    PRINT (_("Got message #%u from element \"%s\" (%s): "),
        (guint) seqnum, GST_ELEMENT_NAME (src_obj),
        GST_MESSAGE_TYPE_NAME (message));
  } else if (GST_IS_PAD (src_obj)) {
    PRINT (_("Got message #%u from pad \"%s:%s\" (%s): "),
        (guint) seqnum, GST_DEBUG_PAD_NAME (src_obj),
        GST_MESSAGE_TYPE_NAME (message));
  } else if (GST_IS_OBJECT (src_obj)) {
    PRINT (_("Got message #%u from object \"%s\" (%s): "),
        (guint) seqnum, GST_OBJECT_NAME (src_obj),
        GST_MESSAGE_TYPE_NAME (message));
  } else {
    PRINT (_("Got message #%u (%s): "), (guint) seqnum,
        GST_MESSAGE_TYPE_NAME (message));
  }

  if (s) {
    gchar *sstr;

    sstr = gst_structure_to_string (s);
    PRINT ("%s\n", sstr);
    g_free (sstr);
  } else {
    PRINT ("no message details\n");
  }
}

gboolean GstAppBase::handleBusMessage1 (GstBus *pBus, GstMessage *pMessage, gpointer data) {
  gboolean bRet = TRUE;
  do {
    GstAppBase *pThis = static_cast<GstAppBase*> (data);
    show_message_in_detail (pMessage);
    if ( (bRet = pThis->handleBusMessage(pBus, pMessage)) == FALSE )
      break;
    return bRet;
  } while (0);
  return bRet;
}

