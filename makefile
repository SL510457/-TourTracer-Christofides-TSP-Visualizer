CXX = g++
CXXFLAGS = -O3 -Wall --shared -std=c++17 -fPIC `python3 -m pybind11 --includes` `python3-config --includes --ldflags` -undefined dynamic_lookup
TARGET = DP.so
TEST_FILE = test

.PHONY: all run_python clean

all: $(TARGET) run_python
$(TARGET): DP.cpp
	$(CXX) -o $@ $(CXXFLAGS) $<

run_python: $(TARGET) test_dp.py
	python3 test_dp.py

clean:
	rm -rf *.o *.so 