NOTESAVE = notesave
NOTESHOW = noteshow
SRC = write.c show.c ./lib/e_malloc.c 

INSTALL = /usr/bin/

FILE_NOTESAVE = write.o
FILE_NOTESHOW = show.o

FILE_LIB = e_malloc.o

ALL: compile $(NOTESAVE) $(NOTESHOW) install clean 

compile:
	gcc -c $(SRC) 

$(NOTESAVE): compile
	gcc $(FILE_NOTESAVE) $(FILE_LIB)

$(NOTESHOW): compile
	gcc -o $(FILE_NOTESHOW) $(FILE_LIB)

install: $(NOTESAVE) $(NOTESHOW)
	mv ./$(NOTESAVE) $(INSTALL)
	mv ./$(NOTESHOW) $(INSTALL)
	chmod u+x $(INSTALL)$(NOTESHOW) $(INSTALL)$(NOTESAVE)

clean: 
	/bin/rm -rf $(FILE_LIB) $(FILE_NOTESAVE) $(FILE_NOTESHOW)


