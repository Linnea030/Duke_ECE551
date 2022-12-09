CCFLAGS=--std=gnu++98 -pedantic -Wall -Werror -ggdb3
PROGS=cyoa-step1 cyoa-step2 cyoa-step3 cyoa-step4
OBJS=$(patsubst %,%.o,$(PROGS)) readStory.o pstory.o page.o choice.o
all: $(PROGS)
cyoa-step%: cyoa-step%.o readStory.o pstory.o page.o choice.o
	g++ -o $@ $^
%.o: %.cpp
	g++ $(CFLAGS) -c $<

.PHONY: clean
clean:
	rm -f *~ $(PROGS) $(OBJS)

readStory.o: readStory.hpp
pstory.o: pstory.hpp
page.o: page.hpp
choice.o: choice.hpp
#cite makefile from eval2
