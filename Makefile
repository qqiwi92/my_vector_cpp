CXXFLAGS += -Wall -Wextra -std=c++14 -MMD

SRCS = main.cpp tests.cpp
OBJS = $(SRCS:.cpp=.o)

main: $(OBJS)
	$(CXX) $(OBJS) -o $@

-include $(SRCS:.cpp=.d)

clean:
	@$(RM) *.o *.d main

run:
	@make main > /dev/null 2>&1
	./main
