# point this to wherever your app is installed, probably /Applications/BinaryNinja.app
PATH_BINJA_APP = $(HOME)/repos/vector35/binaryninja/ui/binaryninja.app/Contents/MacOS

# point this to wherever you cloned https://github.com/Vector35/binaryninja-api and built
PATH_API = $(HOME)/repos/vector35/binaryninja/api

# point this to your plugin path
PATH_PLUGINS = $(HOME)/Library/Application Support/Binary Ninja/plugins

all: libhello.dylib

libhello.dylib: hello.cpp
	g++ -std=gnu++11 -I$(PATH_API) hello.cpp $(PATH_API)/libbinaryninjaapi.a $(PATH_BINJA_APP)/libbinaryninjacore.dylib -fPIC -shared -o libhello.dylib

clean:
	rm -f libhello.dylib

install:
	cp libhello.dylib "$(PATH_PLUGINS)"

uninstall:
	rm "$(PATH_PLUGINS)/libhello.dylib"
