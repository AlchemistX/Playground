#!/usr/bin/env python3
import gi
gi.require_version('GUPnP', '1.0')
from gi.repository import GLib, GObject, GUPnP, GUPnPAV

def action_browse(cd, obj_id):
    in_name = ["ObjectID","BrowseFlag","Filter","StartingIndex","RequestedCount", "SortCriteria"]
    in_val  = [obj_id, "BrowseDirectChildren", "*", "0", "0", ""]
    ou_name = ["Result"]
    ou_type = [GObject.TYPE_STRING.name]
    return cd.send_action_list(action="Browse", in_names=in_name, in_values=in_val, out_names=ou_name, out_types=ou_type)

def container_available_cb(parser, obj, cd):
    print(("%s\%s")%('\t'*obj.get_id().count('$'),obj.get_title()))
    if obj.get_child_count() > 0:
        ret, lst = action_browse(cd, obj.get_id())
        if ret :
            parse = GUPnPAV.DIDLLiteParser()
            parse.connect("container-available", container_available_cb, cd)
            parse.connect("item-available", item_available_cb, cd)
            parse.connect("object-available", object_available_cb, cd)
            parse.parse_didl(lst[0])

def item_available_cb(parser, obj, cd):
    #print(("%s, %s")%(obj.get_title(), obj.get_resources()[0].get_uri()))
    print(("%s%s")%('\t'*obj.get_id().count('$'),obj.get_title()))

def object_available_cb(parser, obj, cd):
    #print(obj.get_title())
    pass

def device_proxy_available_cb(cp, proxy, data):
    cd = proxy.get_service("urn:schemas-upnp-org:service:ContentDirectory")
    print ("="*40)
    print (("Name     : %s")%(proxy.get_friendly_name()))
    print (("Location : %s")%(cd.get_location()))
    print (("udn      : %s")%(cd.get_udn()))
    print (("type     : %s")%(cd.get_service_type()))

    ret, lst = action_browse(cd, "0")

    if ret :
        parse = GUPnPAV.DIDLLiteParser()
        parse.connect("container-available", container_available_cb, cd)
        parse.connect("item-available", item_available_cb, cd)
        parse.connect("object-available", object_available_cb, cd)
        parse.parse_didl(lst[0])

def main():
    loop = GLib.MainLoop.new(None, False)
    context = GUPnP.Context.new(None, None, 0)
    cp = GUPnP.ControlPoint.new(context,"urn:schemas-upnp-org:device:MediaServer:1")
    cp.connect("device-proxy-available", device_proxy_available_cb, loop)
    cp.set_active(True)
    loop.run()

if __name__ == "__main__":
    main()

