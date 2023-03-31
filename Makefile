pa13b: pa13b.o Container.hpp
	$(CXX) $(CXXFLAGS) pa13b.o -o pa13b

pa13b.o: pa13b.cpp
	$(CXX) $(CXXFLAGS) pa13b.cpp -c

clean:
	rm -f pa13b.o pa13b

turnin:
	turnin -c cs202 -p pa13b -v Container.hpp pa13b.cpp Makefile
