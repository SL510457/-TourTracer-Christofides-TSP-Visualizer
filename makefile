CXX = g++
CXXFLAGS = -O3 -Wall --shared -std=c++17 -fPIC `python3 -m pybind11 --includes` `python3-config --includes --ldflags` -undefined dynamic_lookup
TARGET = Christofides.so
TEST_FILE = test

.PHONY: all run_python clean

all: $(TARGET) run_python
$(TARGET): Christofides.cpp
	$(CXX) -o $@ $(CXXFLAGS) $<

run_python: $(TARGET) TSP.py
	python3 TSP.py

clean:
	rm -rf *.o *.so 