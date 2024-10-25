ASSIGN    = a3
BREWPATH  = $(shell brew --prefix)
CXX       = $(shell fltk-config --cxx) -std=c++11 -D_CRT_SECURE_NO_WARNINGS -DGL_SILENCE_DEPRECATION -Wno-macro-redefined -O2 # Without -O2, the compiler may not enable advanced optimizations, resulting in a larger and slower executable but making it easier to debug.
CXXFLAGS  = $(shell fltk-config --cxxflags) -I$(BREWPATH)/include
LDFLAGS   = $(shell fltk-config --ldflags --use-gl --use-images) -L$(BREWPATH)/lib
POSTBUILD = fltk-config --post # build .app folder for osx. (does nothing on pc)

$(ASSIGN): % : main.o MyGLCanvas.o Camera.o ./scene/SceneParser.o ./scene/tinyxmlparser.o ./scene/tinyxmlerror.o ./scene/tinyxml.o ./scene/tinystr.o objects/construct.o
	$(CXX) $(LDFLAGS) $^ -o $@
	$(POSTBUILD) $@

# Used to compile main.cpp to generate the object file main.o
main.o: main.cpp *.h
	$(CXX) $(CXXFLAGS) -c main.cpp -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $^ -o $@

clean:
	rm -rf $(ASSIGN) $(ASSIGN).app *.o *~ *.dSYM
