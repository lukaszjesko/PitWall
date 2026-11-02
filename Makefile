# PitWall — budowanie projektu
#   Windows (g++ z MinGW):  mingw32-make  ->  pitwall.exe
#   Linux:                  make          ->  pitwall

CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -pedantic -Iinclude
SOURCES  := $(wildcard src/*.cpp)
HEADERS  := $(wildcard include/*.h)

ifeq ($(OS),Windows_NT)
  TARGET := pitwall.exe
else
  TARGET := pitwall
endif

$(TARGET): $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)
