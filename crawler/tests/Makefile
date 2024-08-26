CXX = g++
CC = $(CXX)

CXXFLAGS = -pedantic -Wall -Werror
CXXFLAGS += -g3
CXXFLAGS += -std=c++17

CPPFLAGS = -DDEBUG
CPPFLAGS += -I$(INCLUDES_DIR)

LDFLAGS = -lgumbo -lcurl -lcurlpp

INCLUDES_DIR = ../inc
SOURCES_DIR = ../src

# Source and Object Files
SOURCES = $(SOURCES_DIR)/crawler.cpp $(SOURCES_DIR)/crawler_config.cpp
OBJECTS = $(SOURCES:.cpp=.o) $(SOURCES_DIR)/test.o

# Target Executable
TARGET = test

# Rules
all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) -o $(TARGET) $(OBJECTS) $(LDFLAGS)

# Pattern rule for compiling .cpp to .o
$(SOURCES_DIR)/%.o: $(SOURCES_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

# Specific rule for compiling test.cpp
$(SOURCES_DIR)/test.o: test.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $(SOURCES_DIR)/test.o

check: $(TARGET)
	@./$(TARGET) -v

clean:
	@$(RM) $(TARGET) $(OBJECTS)

.PHONY: all clean check
