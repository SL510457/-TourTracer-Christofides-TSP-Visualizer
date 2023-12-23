CXX = g++
CXXFLAGS = -O3 -Wall --shared -std=c++17 -fPIC `python3 -m pybind11 --includes` `python3-config --includes --ldflags` -undefined dynamic_lookup
TARGET = Christofide.so
TEST_FILE = test

.PHONY: all run_python clean

all: $(TARGET) run_python
$(TARGET): Christofide.cpp
	$(CXX) -o $@ $(CXXFLAGS) $<

run_python: Christofide.so test_tsp.py
	python3 test_tsp.py

clean:
	rm -rf *.o *.so __pycache__ .pytest_cache/