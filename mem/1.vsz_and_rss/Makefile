#
# Author Feng Gao
#
#

.PHONY: all clean depend

CXXFLAGS := -Wall -shared -std=c++11 -fPIC
LDFLAGS :=
CXX := g++

SRCS := $(wildcard *.cpp)
DEPS := $(patsubst %.cpp,%.d,$(SRCS))
OBJS := $(patsubst %.cpp,%.o,$(SRCS))


TARGET := vsz_and_rss 

all: $(TARGET)

$(TARGET): $(OBJS) $(DEPS)
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS)

%.d:%.cpp
	$(CXX) -M $(CXXFLAGS) $< > $@

%.o:%.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

explain:
	@echo "The information represents in the program:"
	@echo "Final executable name: $(PRGM)"
	@echo "Source files: $(SRCS)"
	@echo "Object files: $(OBJS)"

depend:$(DEPS)
	@echo "Dependencies are now up-to-date"

clean:
	rm -f $(TARGET) $(OBJS) $(DEPS)

-include $(DEPS)  
