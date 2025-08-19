# Define targets
all: minicalc stringbuilder

#compile minicalc executable first
minicalc: minicalc.c
	@gcc -Wall -g -o minicalc minicalc.c -lm

#same with stringbuilder:
stringbuilder: stringbuilder.c stringbuilder.h
	@gcc -Wall -g -o stringbuilder stringbuilder.c
 
.PHONY: test
test: minicalc
	@./run-tests

#to clean generated files
.PHONY: clean
clean:
	rm -f minicalc stringbuilder

