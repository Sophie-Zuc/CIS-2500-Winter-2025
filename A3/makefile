bin/musicalLL: mainA3.o createPlayList.o playPlayList.o addNewSong.o playSongGivenId.o deletePlayList.o deleteASongGivenId.o countNotesInASong.o playSongGivenName.o
	gcc mainA3.o createPlayList.o playPlayList.o addNewSong.o playSongGivenId.o deletePlayList.o deleteASongGivenId.o countNotesInASong.o playSongGivenName.o -o bin/musicalLL

mainA3.o: src/mainA3.c include/givenA3.h
	gcc -Wall -std=c99 -c src/mainA3.c

createPlayList.o: src/createPlayList.c include/givenA3.h
	gcc -Wall -std=c99 -c src/createPlayList.c

playPlayList.o: src/playPlayList.c include/givenA3.h
	gcc -Wall -std=c99 -c src/playPlayList.c

addNewSong.o: src/addNewSong.c include/givenA3.h
	gcc -Wall -std=c99 -c src/addNewSong.c

playSongGivenId.o: src/playSongGivenId.c include/givenA3.h
	gcc -Wall -std=c99 -c src/playSongGivenId.c

deletePlayList.o: src/deletePlayList.c include/givenA3.h
	gcc -Wall -std=c99 -c src/deletePlayList.c

deleteASongGivenId.o: src/deleteASongGivenId.c include/givenA3.h
	gcc -Wall -std=c99 -c src/deleteASongGivenId.c

countNotesInASong.o: src/countNotesInASong.c include/givenA3.h
	gcc -Wall -std=c99 -c src/countNotesInASong.c

playSongGivenName.o: src/playSongGivenName.c include/givenA3.h
	gcc -Wall -std=c99 -c src/playSongGivenName.c

clean:
	rm *.o bin/musicalLL

