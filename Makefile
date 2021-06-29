CC := gcc

asl:main.o elfFile.o ir.o readfile.o list.o
	gcc -g  -o $@ $^
main.o:main.c elfFile.h
	gcc -c  $<
elfFile.o:elfFile.c elfFile.h ir.h
	gcc -c  $<
ir.o:ir.c  ir.h readfile.h
	gcc -c  $<
readfile.o: readfile.c readfile.h list.h
	gcc -c  $<
list.o: list.c list.h
	gcc -c  $<	
.PHONY:clean
clean:
	@rm -fr $(OBJ)/*.o $(BIN_DIR)
