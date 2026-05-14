# Compiler to use
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -Wextra -std=c++17 -IClasses/headers

# External libraries to link
LDLIBS = -lsqlite3 -lcurl

# The name of the final executable
TARGET = app

# List of all source files
SRCS = main.cpp \
       Classes/database.cpp \
       Classes/location.cpp \
       Classes/login.cpp \
       Classes/prayer_records.cpp \
       Classes/prayer_time.cpp \
       Classes/user.cpp

# Generate a list of object files by replacing .cpp with .o
OBJS = $(SRCS:.cpp=.o)

# Default target
all: $(TARGET)

# Rule to link the object files into the final executable (Notice $(LDLIBS) added here)
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LDLIBS)

# Rule to compile each .cpp file into a .o object file
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean