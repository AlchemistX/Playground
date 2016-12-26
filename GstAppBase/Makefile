TARGET=GstAppBase
SRCS=main.cpp GstAppBase.cpp GstApp.cpp
OBJS=$(SRCS:%cpp=%o)
CFLAGS=$(shell pkg-config --cflags gstreamer-1.0) -g
CXXFLAGS=$(CFLAGS)
LDLIBS=$(shell pkg-config --libs gstreamer-1.0)

$(TARGET): $(OBJS)
	c++ -o $@ $^ $(LDLIBS)

clean:
	rm *.o $(TARGET)
