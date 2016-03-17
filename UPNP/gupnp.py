#!/usr/bin/env python3
import gi
gi.require_version('GUPnP', '1.0')
gi.require_version('GUPnPAV', '1.0')
from gi.repository import GLib, GObject, GUPnP, GUPnPAV

class UPnP_Finder:
    def __init__(self, loop, search):
        self.loop = loop
        self.search = search
        self.contents = []
        self.context = GUPnP.Context.new(None, None, 0)
        self.control_point = GUPnP.ControlPoint.new(self.context,"urn:schemas-upnp-org:device:MediaServer:1")
        self.control_point.connect("device-proxy-available", self.device_proxy_available_cb, loop)
        self.control_point.set_active(True)

    def action_browse(self, obj_id="0"):
        in_name = ["ObjectID","BrowseFlag","Filter","StartingIndex","RequestedCount", "SortCriteria"]
        in_val  = [obj_id, "BrowseDirectChildren", "*", "0", "0", ""]
        ou_name = ["Result"]
        ou_type = [GObject.TYPE_STRING.name]
        return self.content_directory.send_action_list(action="Browse", in_names=in_name, in_values=in_val, out_names=ou_name, out_types=ou_type)

    def print_server_info(self, proxy):
        print ("="*40)
        print (("Name     : %s")%(proxy.get_friendly_name()))
        print (("Location : %s")%(self.content_directory.get_location()))
        print (("udn      : %s")%(self.content_directory.get_udn()))
        print (("type     : %s")%(self.content_directory.get_service_type()))

    def device_proxy_available_cb(self, cp, proxy, data):
        self.content_directory = proxy.get_service("urn:schemas-upnp-org:service:ContentDirectory")

        ret, lst = self.action_browse()
        if ret :
            parse = GUPnPAV.DIDLLiteParser()
            parse.connect("container-available", self.container_available_cb, None)
            parse.parse_didl(lst[0])

        if (len(self.contents) != 0):
            self.loop.quit()

    def container_available_cb(self, parser, obj, data):
        if obj.get_child_count() > 0:
            ret, lst = self.action_browse(obj.get_id())
            if ret :
                parse = GUPnPAV.DIDLLiteParser()
                if obj.get_title().startswith(self.search):
                    parse.connect("container-available", self.container_found_cb, None)
                    parse.connect("item-available", self.item_found_cb, None)
                else:
                    parse.connect("container-available", self.container_available_cb, None)
                parse.parse_didl(lst[0])

    def container_found_cb(self, parser, obj, cd):
        if self.contents.count((obj.get_title(), ">")) == 0:
            self.contents.append((obj.get_title(), ">"))
        if obj.get_child_count() > 0:
            ret, lst = self.action_browse(obj.get_id())
            if ret :
                parse = GUPnPAV.DIDLLiteParser()
                parse.connect("container-available", self.container_found_cb, None)
                parse.connect("item-available", self.item_found_cb, None)
                parse.parse_didl(lst[0])
        if self.contents.count((obj.get_title(), "<")) == 0:
            self.contents.append((obj.get_title(), "<"))

    def item_found_cb(self, parser, obj, cd):
        if self.contents.count((obj.get_title(), obj.get_resources()[0].get_uri())) == 0:
            self.contents.append((obj.get_title(), obj.get_resources()[0].get_uri()))

    def __str__(self):
        ret = ""
        tab = 0
        for v1, v2 in self.contents:
            if v2 == '>':
                ret += ("%s%s:\n")%('\t'*tab,v1)
                tab = tab + 1
            elif v2 == '<':
                tab = tab - 1
            else:
                ret += ("%s%s\t%s\n")%('\t'*tab,v2,v1)
        return ret

def main():
    loop = GLib.MainLoop.new(None, False)
    fin = UPnP_Finder(loop, "SALMON")
    loop.run()
    print("="*40, "TEST CONTENTS", "="*40)
    print(fin)

if __name__ == "__main__":
    main()

