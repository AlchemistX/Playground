#!/usr/bin/env python
import sys

from gi.repository import Gst

def main(args):
    args = Gst.init(args)
    _, uri = args
    pipeline = Gst.parse_launch('playbin')
    pipeline.set_property('uri', uri)

    print("PLAY : %s"%(uri))
    pipeline.set_state(Gst.State.PLAYING)
    pipeline.get_bus().poll(Gst.MessageType.EOS | Gst.MessageType.ERROR, Gst.CLOCK_TIME_NONE)
    print("END : %s"%(uri))
    pipeline.set_state(Gst.State.NULL)

if __name__ == '__main__':
    main(sys.argv)

