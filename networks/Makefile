SRCMODULES = server.cpp sockets.cpp
OBJMODULES = $(SRCMODULES:.cpp=.o)

CXX = g++
CXXFLAGS = -ggdb -Wall

%.o: %.cpp %.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

prog: main.cpp $(OBJMODULES)
	$(CXX) $(CXXFLAGS) $^ -o $@

ifneq (clean, $(MAKECMDGOALS))
-include deps.mk
endif

deps.mk: $(SRCMODULES)
	$(CXX) -MM $^ > $@

clean:
	rm -f prog *.o deps.mk
