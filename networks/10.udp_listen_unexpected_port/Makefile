#
# Author Feng Gao
#
#

.PHONY: all clean depend

CFLAGS := -Wall -g -fPIC -std=gnu99
LDFLAGS := -lpthread
CC := gcc

SRCS := $(wildcard *.c)
DEPS := $(patsubst %.c,%.d,$(SRCS))
OBJS := $(patsubst %.c,%.o,$(SRCS))


TARGET := udp_listen_unexpected_port

all: $(TARGET)

$(TARGET): $(OBJS) $(DEPS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

%.d:%.c
	$(CC) -M $(CFLAGS) $< > $@

%.o:%.c
	$(CC) -c $(CFLAGS) $< -o $@

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
