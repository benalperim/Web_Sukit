# Copyright 2018 Darik Harter
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Wpedantic -Werror -ggdb

OBJS = $(patsubst src/%.cpp, build/%.o, $(wildcard src/*.cpp))
HDRS = $(wildcard include/*.h)

VPATH = src

.PHONY: all
all: bin/main

bin/main: $(OBJS)
	@$(CXX) $(CXXFLAGS) $^ -o $@
	@echo "  LINK     $@"

build/%.o: %.cpp $(HDRS) | dirs
	@$(CXX) $(CXXFLAGS) -Iinclude/ -c $< -o $@
	@echo "  CXX      $@"

.PHONY: dirs
dirs:
	@mkdir -p bin/ build/

.PHONY: clean
clean:
	@rm -rf bin/
	@rm -rf build/
	@rm -rf docs/html/

.PHONY: docs
docs:
	@doxygen docs/Doxyfile &> /dev/null
	@firefox docs/html/index.html &
