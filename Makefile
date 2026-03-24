CXXFLAGS += -Wall -Wextra -std=c++14 -MMD

main: main.o
	$(CXX) $^ -o $@

-include main.d

clean:
	@$(RM) *.o *.d main

run:
	@make main > /dev/null 2>&1
	./main