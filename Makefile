ifeq ($(OS),Windows_NT)     # is Windows_NT on XP, 2000, 7, Vista, 10...
	OUT_FILE=a
else
	OUT_FILE=a.out
endif

${OUT_FILE}:
	gcc -o ${OUT_FILE} src/main.c  src/wordle.c

clean:
	rm ${OUT_FILE}

test: ${OUT_FILE}
	bash test.sh
