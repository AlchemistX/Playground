GUPNP=gupnp
SSDP_BROWSER=ssdp_browser
CFLAGS=`pkg-config --cflags gupnp-1.0`
LIBS=`pkg-config --libs glib-2.0 gobject-2.0 gio-2.0 gssdp-1.0 gupnp-1.0`
GUPNP_SRCS=gupnp.c
GUPNP_OBJS=gupnp.o
SSDP_BROWSER_SRCS=ssdp_browser.c
SSDP_BROWSER_OBJS=ssdp_browser.o

all:$(GUPNP) $(SSDP_BROWSER)
$(GUPNP):$(GUPNP_OBJS)
		$(CC) -o $@ $(GUPNP_OBJS) $(LIBS)
$(SSDP_BROWSER):$(SSDP_BROWSER_OBJS)
		$(CC) -o $@ $(SSDP_BROWSER_OBJS) $(LIBS)

clean:
		rm -rf $(GUPNP) $(GUPNP_OBJS) $(SSDP_BROWSER) $(SSDP_BROWSER_OBJS) core
