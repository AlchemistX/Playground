#!/usr/bin/env python
# -*- coding: utf-8 -*-

import gi
gi.require_version('Gtk', '3.0')
from gi.repository import Gtk

class Application:
    def __init__(self):
        win = Gtk.Window()
        win.set_title("My awesome window")
        win.connect('destroy', self.destroy)
        win.set_default_size(300, 200)
        win.set_position(Gtk.WindowPosition.CENTER)

        btn = Gtk.Button("Hit ME!")
        btn.connect_after("clicked", self.btn_clicked)

        win.add(btn)

        win.show_all()

    def destroy(self, win):
        Gtk.main_quit()
        print("QUIT")

    def btn_clicked(self, btn):
        print("OK")

def main():
    app = Application()
    Gtk.main()

if __name__ == '__main__':
    main()

