CXX = g++
CC = $(CXX)

CXXFLAGS = -pedantic -Wall -Werror \
           -g3 \
           -std=c++17

CPPFLAGS = -DDEBUG \
           -I$(INCLUDES_DIR)

LDFLAGS = -lgumbo -lcurl -lcurlpp -lgtest -lgtest_main

INCLUDES_DIR = ../inc
SOURCES_DIR = ../src
TEST_DIR = ../tests

# Source and Object Files
SOURCES = $(SOURCES_DIR)/crawler_mng.cpp \
          $(SOURCES_DIR)/crawler_config.cpp \
          $(SOURCES_DIR)/bfs.cpp \
          $(SOURCES_DIR)/dfs.cpp \
          $(SOURCES_DIR)/crawling_base.cpp \
          $(SOURCES_DIR)/crawler_db.cpp \
          $(SOURCES_DIR)/parser.cpp \
          $(TEST_DIR)/test.cpp

OBJECTS = $(SOURCES_DIR)/crawler_mng.o \
          $(SOURCES_DIR)/crawler_config.o \
          $(SOURCES_DIR)/bfs.o \
          $(SOURCES_DIR)/dfs.o \
          $(SOURCES_DIR)/crawling_base.o \
          $(SOURCES_DIR)/crawler_db.o \
          $(SOURCES_DIR)/parser.o \
          $(TEST_DIR)/test.o

# Target Executable
TARGET = test

# Rules
all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) -o $(TARGET) $(OBJECTS) $(LDFLAGS)

# Pattern rule for compiling .cpp to .o
$(SOURCES_DIR)/%.o: $(SOURCES_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

# Specific rule for compiling test.cpp in the test directory
$(TEST_DIR)/%.o: $(TEST_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	@$(RM) $(TARGET) $(OBJECTS)

.PHONY: all clean check
