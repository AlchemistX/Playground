#!/usr/bin/env python3

import sys, os, time, _thread
import gi
gi.require_version('Gst', '1.0')
from gi.repository import Gst, GLib

class CLI_Main(object):
    def __init__(self, loop):
        self.loop = loop
        self.player = Gst.ElementFactory.make("playbin", "player")
        fakesink = Gst.ElementFactory.make("fakesink", "fakesink")
        self.player.set_property("video-sink", fakesink)
        bus = self.player.get_bus()
        bus.add_signal_watch()
        bus.connect("message", self.on_message)

    def on_message(self, bus, message):
        t = message.type
        if t == Gst.MessageType.EOS:
            self.player.set_state(Gst.State.NULL)
            self.playmode = False
        elif t == Gst.MessageType.ERROR:
            self.player.set_state(Gst.State.NULL)
            err, debug = message.parse_error()
            print (("Error: %s"%(err, debug)))
            self.playmode = False

    def start(self):
        for filepath in sys.argv[1:]:
            if os.path.isfile(filepath):
                filepath = os.path.realpath(filepath)
                self.playmode = True
                self.player.set_property("uri", "file://" + filepath)
                self.player.set_state(Gst.State.PLAYING)
                while self.playmode:
                    time.sleep(1)
        time.sleep(1)
        self.loop.quit()

def main():
    Gst.init(None)
    loop = GLib.MainLoop()
    mainclass = CLI_Main(loop)
    _thread.start_new_thread(mainclass.start, ())
    loop.run()

if __name__ == "__main__":
    main()
    