NOTESAVE = notesave
NOTESHOW = noteshow
SRC = write.c show.c ./lib/e_malloc.c 

INSTALL = /usr/bin/


FILE_NOTESAVE = write.o
FILE_NOTESHOW = show.o

FILE_LIB = e_malloc.o

all: ALL

ALL: compile $(NOTESAVE) $(NOTESHOW) install clean 

compile:
	gcc -c $(SRC) 

$(NOTESAVE): compile
	gcc -o $(NOTESAVE) $(FILE_NOTESAVE) $(FILE_LIB)

$(NOTESHOW): compile
	gcc -o $(NOTESHOW) $(FILE_NOTESHOW) $(FILE_LIB)

install: $(NOTESAVE) $(NOTESHOW)
	mv ./$(NOTESAVE) $(INSTALL)
	mv ./$(NOTESHOW) $(INSTALL)
	sudo chmod 100 $(INSTALL)$(NOTESHOW) $(INSTALL)$(NOTESAVE)
	sudo chown root:root $(INSTALL)$(NOTESHOW) $(INSTALL)$(NOTESAVE)
	sudo chmod u+x $(INSTALL)$(NOTESHOW) $(INSTALL)$(NOTESAVE)

clean: 
	/bin/rm -rf $(FILE_LIB) $(FILE_NOTESAVE) $(FILE_NOTESHOW)

uninstall: 
	/bin/rm -rf $(INSTALL)$(NOTESAVE) $(INSTALL)$(NOTESHOW)
