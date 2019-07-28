# point this to wherever your app is installed, probably /Applications/BinaryNinja.app
PATH_BINJA_APP = $(HOME)/repos/vector35/binaryninja/ui/binaryninja.app/Contents/MacOS

# point this to wherever you cloned https://github.com/Vector35/binaryninja-api and built
PATH_API = $(HOME)/repos/vector35/binaryninja/api

# point this to your plugin path
PATH_PLUGINS = $(HOME)/Library/Application Support/Binary Ninja/plugins

all: arch_hello.dylib

arch_hello.dylib: arch_hello.cpp
	g++ -std=gnu++11 -I$(PATH_API) arch_hello.cpp $(PATH_API)/libbinaryninjaapi.a $(PATH_BINJA_APP)/libbinaryninjacore.dylib -fPIC -shared -o arch_hello.dylib

clean:
	rm -f arch_hello.dylib

install:
	cp arch_hello.dylib "$(PATH_PLUGINS)"

uninstall:
	rm "$(PATH_PLUGINS)/arch_hello.dylib"
