#!/usr/bin/python
from upnp import upnp


client = upnp(None, None, None)
client.msearch("device", "MediaServer")
print client.upnpRequest
