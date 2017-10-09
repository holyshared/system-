.PHONY: build clean

POLL = poll
SELECT = select
STREAM = stream
SOURCE_FILES = $(POLL) $(SELECT) $(STREAM)

build:
	gcc $(POLL).c -o $(POLL)
	gcc $(SELECT).c -o $(SELECT)
	gcc $(STREAM).c -o $(STREAM)

clean:
	rm $(SOURCE_FILES)
