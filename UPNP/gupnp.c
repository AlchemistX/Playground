#include <libgupnp/gupnp-control-point.h>

static GMainLoop *main_loop;

static void
device_proxy_available_cb (GUPnPControlPoint *cp,
                           GUPnPDeviceProxy *proxy,
                           gpointer           userdata)
{
  GUPnPServiceProxy *cd = GUPNP_SERVICE_PROXY(gupnp_device_info_get_service(GUPNP_DEVICE_INFO(proxy), "urn:schemas-upnp-org:service:ContentDirectory"));

  g_print("==============================\n");
  g_print("Name : %s\n", gupnp_device_info_get_friendly_name(GUPNP_DEVICE_INFO(proxy)));
  g_print("Location : %s\n", gupnp_service_info_get_location(GUPNP_SERVICE_INFO(cd)));
  g_print("udn : %s\n", gupnp_service_info_get_udn(GUPNP_SERVICE_INFO(cd)));
  g_print("type : %s\n", gupnp_service_info_get_service_type(GUPNP_SERVICE_INFO(cd)));



  const char *location;
  char *result = NULL;
  guint count, total;
  GError *error = NULL;

  location = gupnp_service_info_get_location (GUPNP_SERVICE_INFO (cd));

  g_print ("ContentDirectory available:\n");
  g_print ("\tlocation: %s\n", location);

  /* We want to be notified whenever SystemUpdateID (of type uint)
   * changes */
/*
  gupnp_service_proxy_add_notify (proxy,
          "SystemUpdateID",
          G_TYPE_UINT,
          notify_cb,
          (gpointer) "Test");
*/

  /* Subscribe */
/*
  g_signal_connect (proxy,
          "subscription-lost",
          G_CALLBACK (subscription_lost_cb),
          NULL);

  gupnp_service_proxy_set_subscribed (proxy, TRUE);
*/

  /* And test action IO */
  gupnp_service_proxy_send_action (cd,
          "Browse",
          &error,
          /* IN args */
          "ObjectID",
          G_TYPE_STRING,
          "0",
          "BrowseFlag",
          G_TYPE_STRING,
          "BrowseDirectChildren",
          "Filter",
          G_TYPE_STRING,
          "*",
          "StartingIndex",
          G_TYPE_UINT,
          0,
          "RequestedCount",
          G_TYPE_UINT,
          0,
          "SortCriteria",
          G_TYPE_STRING,
          "",
          NULL,
          /* OUT args */
          "Result",
          G_TYPE_STRING,
          &result,
          "NumberReturned",
          G_TYPE_UINT,
          &count,
          "TotalMatches",
          G_TYPE_UINT,
          &total,
          NULL);

  if (error) {
      g_printerr ("Error: %s\n", error->message);
      g_error_free (error);

      return;
  }

  g_print ("Browse returned:\n");
  g_print ("\tResult:         %s\n", result);
  g_print ("\tNumberReturned: %u\n", count);
  g_print ("\tTotalMatches:   %u\n", total);

  g_free (result);
  //g_main_loop_quit(main_loop);
}

int
main (int argc, char **argv)
{
  GUPnPContext *context;
  GUPnPControlPoint *cp;

  /* Required initialisation */
#if !GLIB_CHECK_VERSION(2,35,0)
  g_type_init ();
#endif

  /* Create a new GUPnP Context.  By here we are using the default GLib main
   *      context, and connecting to the current machine's default IP on an
   *           automatically generated port. */
  context = gupnp_context_new (NULL, NULL, 0, NULL);

  /* Create a Control Point targeting WAN IP Connection services */
  cp = gupnp_control_point_new
    (context, "urn:schemas-upnp-org:device:MediaServer:1");

  /* The service-proxy-available signal is emitted when any services which match
   *      our target are found, so connect to it */
  g_signal_connect (cp,
      "device-proxy-available",
      G_CALLBACK (device_proxy_available_cb),
      NULL);

  /* Tell the Control Point to start searching */
  gssdp_resource_browser_set_active (GSSDP_RESOURCE_BROWSER (cp), TRUE);

  /* Enter the main loop. This will start the search and result in callbacks to
   *      service_proxy_available_cb. */
  main_loop = g_main_loop_new (NULL, FALSE);
  g_main_loop_run (main_loop);

  /* Clean up */
  g_main_loop_unref (main_loop);
  g_object_unref (cp);
  g_object_unref (context);

  return 0;
}
