.PHONY: build clean

READ_FILE = read_file
READV = readv
WRITE_FILE = write_file
WRITE_V = writev
SOURCE_FILES = $(READ_FILE) $(READV) $(WRITE_FILE) $(WRITE_V)

build:
	gcc $(READ_FILE).c -o $(READ_FILE)
	gcc $(READV).c -o $(READV)
	gcc $(WRITE_FILE).c -o $(WRITE_FILE)
	gcc $(WRITE_V).c -o $(WRITE_V)

clean:
	rm $(SOURCE_FILES)
