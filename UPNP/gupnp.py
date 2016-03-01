#!/usr/local/bin/python
import gi
gi.require_version('GUPnP', '1.0')
from gi.repository import GLib, GUPnP

def handler(cp, proxy):
    print "HHHHHHH"

def timeout_cb(data):
    print data 
    loop.quit()

context = GUPnP.Context.new(None, None, 0)
cp = GUPnP.ControlPoint.new(context,"upnp:rootdevice")
cp.connect("service-proxy-available", handler)
cp.set_active(True)

GLib.timeout_add(1000, timeout_cb, "hello")

loop = GLib.MainLoop.new(None, False)
loop.run()

