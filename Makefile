CC := gcc

cpServe:main.o compilerlf.o cmpl.o x64.o
	gcc -g  -o $@ $^
main.o:main.c model.h
	gcc -c  $<
compilerlf.o:compilerlf.c model.h
	gcc -c $<
cmpl.o:cmpl.c model.h
	gcc -c $<
x64.o:x64.c model.h
	gcc -c $<
.PHONY:clean
clean:
	@rm -fr $(OBJ)/*.o $(BIN_DIR)
