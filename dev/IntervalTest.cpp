#include "Interval.h"
#include "Note.h"
#include <iostream>
#include <vector>

using namespace std;

void invalidConstructorsIntervalByNotesTest(){
	//titulo
	cout << endl << endl << "- SETINTERVAL CON NOTAS CON ENTRADAS INVALIDAS" << endl << endl;
	//test
	Note note1, note2;
	Interval interval;
	
	note1.setNote("do","",3);
	
	note2.setNote("do", "", 4);
	cout << interval.setInterval(note1, note2) << endl;
	note2.setNote("do", "", 2);
	cout << interval.setInterval(note1,note2) << endl;
	note2.setNote("mi", "", 4);
	cout << interval.setInterval(note1,note2) << endl;
	note2.setNote("la", "", 1);
	cout << interval.setInterval(note1,note2) << endl;
	note2.setNote("do", "bb");
	cout << interval.setInterval(note1,note2) << endl;
	note2.setNote("mi", "x");
	cout << interval.setInterval(note1,note2) << endl;
	note2.setNote("la", "bb", 2);
	cout << interval.setInterval(note1,note2) << endl;
	
	note1.setNote("fa","#",3);
	
	note2.setNote("fa", "#", 4);
	cout << interval.setInterval(note1,note2) << endl;
	note2.setNote("fa", "#", 2);
	cout << interval.setInterval(note1,note2) << endl;
	note2.setNote("la", "", 4);
	cout << interval.setInterval(note1,note2) << endl;
	note2.setNote("re", "", 2);
	cout << interval.setInterval(note1,note2) << endl;
	note2.setNote("fa", "");
	cout << interval.setInterval(note1,note2) << endl;
	note2.setNote("si", "bb");
	cout << interval.setInterval(note1,note2) << endl;
	note2.setNote("la", "x", 2);
	cout << interval.setInterval(note1,note2) << endl;
	
	note1.setNote("si","",3);
	
	note2.setNote("si", "", 4);
	cout << interval.setInterval(note1,note2) << endl;
	note2.setNote("si", "", 2);
	cout << interval.setInterval(note1,note2) << endl;
	note2.setNote("re", "", 5);
	cout << interval.setInterval(note1,note2) << endl;
	note2.setNote("sol", "", 2);
	cout << interval.setInterval(note1,note2) << endl;
	note2.setNote("fa", "b", 4);
	cout << interval.setInterval(note1,note2) << endl;
	note2.setNote("fa", "bb", 4);
	cout << interval.setInterval(note1,note2) << endl;
	note2.setNote("re", "x");
	cout << interval.setInterval(note1,note2) << endl;
	
	cout << interval << endl;
}

void validConstructorsIntervalByNotesTest(){
	//titulo
	cout << endl << endl << "- SETINTERVAL CON NOTAS CON ENTRADAS VALIDAS" << endl << endl;
	//test
	Note note1, note2;
	Interval interval;
	
	note1.setNote("do", "", 3);
	
	note2.setNote("do", "", 3);
	interval.setInterval(note1, note2);
	cout << interval << endl;
	note2.setNote("re", "", 3);
	interval.setInterval(note1, note2);
	cout << interval << endl;
	note2.setNote("re", "#", 3);
	interval.setInterval(note1, note2);
	cout << interval << endl;
	note2.setNote("mi", "b", 2);
	interval.setInterval(note1, note2);
	cout << interval << endl;
	
	note1.setNote("fa","#",3);
	
	note2.setNote("mi", "#", 3);
	interval.setInterval(note1, note2);
	cout << interval << endl;
	note2.setNote("si", "#", 2);
	interval.setInterval(note1, note2);
	cout << interval << endl;
	note2.setNote("la", "", 3);
	interval.setInterval(note1, note2);
	cout << interval << endl;
	note2.setNote("do", "#", 4);
	interval.setInterval(note1, note2);
	cout << interval << endl;
	
	note1.setNote("si", "", 3);
	
	note2.setNote("do", "", 3);
	interval.setInterval(note1, note2);
	cout << interval << endl;
	note2.setNote("re", "#", 4);
	interval.setInterval(note1, note2);
	cout << interval << endl;
	note2.setNote("la", "b", 4);
	interval.setInterval(note1, note2);
	cout << interval << endl;
	note2.setNote("fa", "", 3);
	interval.setInterval(note1, note2);
	cout << interval << endl;
}

void invalidConstructorsIntervalByNameTest(){
	//titulo
	cout << endl << endl << "- SETINTERVAL CON NOMBRE CON ENTRADAS INVALIDAS" << endl << endl;
	//test
	Note note;
	Interval interval;
	
	note.setNote("do", "", 3);
	
	cout << interval.setInterval(note, "2daa", "mayor", "asc") << endl;
	cout << interval.setInterval(note, "2da", "mayorr", "asc") << endl;
	cout << interval.setInterval(note, "2da", "mayor", "ascc") << endl;
	cout << interval.setInterval(note, "2da", "disminuida", "asc") << endl;
	
	note.setNote("do","",-2);
	cout << interval.setInterval(note, "3ra", "mayor", "desc") << endl;
	note.setNote("sol","",8);
	cout << interval.setInterval(note, "3ra", "mayor", "asc") << endl;
	
}


void validConstructorsIntervalByNameTest(){
	//titulo
	cout << endl << endl << "- CONSTRUCTOR CON NOMBRE CON ENTRADAS VALIDAS" << endl << endl;
	//test
	Note note;
	Interval interval;
	
	note.setNote("do", "", 3);
	
	interval.setInterval(note, "unisono", "", "");
	cout << interval << endl;
	interval.setInterval(note, "2da", "mayor", "asc");
	cout << interval << endl;
	interval.setInterval(note, "2da", "aumentada", "asc");
	cout << interval << endl;
	interval.setInterval(note, "6ta", "mayor", "desc");
	cout << interval << endl;
	
	note.setNote("fa", "#", 3);
	
	interval.setInterval(note, "2da", "menor", "desc");
	cout << interval << endl;
	interval.setInterval(note, "5ta", "disminuida", "desc");
	cout << interval << endl;
	interval.setInterval(note, "3ra", "menor", "asc");
	cout << interval << endl;
	interval.setInterval(note, "5ta", "justa", "asc");
	cout << interval << endl;

	note.setNote("si", "", 3);
	
	interval.setInterval(note, "7ma", "mayor", "desc");
	cout << interval << endl;
	interval.setInterval(note, "3ra", "mayor", "asc");
	cout << interval << endl;
	interval.setInterval(note, "7ma", "disminuida", "asc");
	cout << interval << endl;
	interval.setInterval(note, "4ta", "aumentada", "desc");
	cout << interval << endl;
}

void gettersTest(){
	//titulo
	cout << endl << endl << "- GETTERS" << endl << endl;
	//test
	Interval interval, invertion;
	Note note1, note2;
	
	note1.setNote("do", "", 3);
	
	note2.setNote("do", "", 3);
	interval.setInterval(note1, note2);
	invertion = interval.getInvertion();
	cout << invertion << endl;
	note2.setNote("re", "", 3);
	interval.setInterval(note1, note2);
	invertion = interval.getInvertion();
	cout << invertion << endl;
	note2.setNote("re", "#", 3);
	interval.setInterval(note1, note2);
	invertion = interval.getInvertion();
	cout << invertion << endl;
	note2.setNote("mi", "b", 2);
	interval.setInterval(note1, note2);
	invertion = interval.getInvertion();
	cout << invertion << endl;	
	
	note1.setNote("fa", "#", 3);
	
	note2.setNote("mi", "#", 3);
	interval.setInterval(note1, note2);
	invertion = interval.getInvertion();
	cout << invertion << endl;
	note2.setNote("si", "#", 2);
	interval.setInterval(note1, note2);
	invertion = interval.getInvertion();
	cout << invertion << endl;
	note2.setNote("la", "", 3);
	interval.setInterval(note1, note2);
	invertion = interval.getInvertion();
	cout << invertion << endl;
	note2.setNote("do", "#", 4);
	interval.setInterval(note1, note2);
	invertion = interval.getInvertion();
	cout << invertion << endl;	
	
	note1.setNote("si", "", 3);
	
	note2.setNote("do", "", 3);
	interval.setInterval(note1, note2);
	invertion = interval.getInvertion();
	cout << invertion << endl;
	note2.setNote("re", "#",4);
	interval.setInterval(note1, note2);
	invertion = interval.getInvertion();
	cout << invertion << endl;
	note2.setNote("la", "b", 4);
	interval.setInterval(note1, note2);
	invertion = interval.getInvertion();
	cout << invertion << endl;
	note2.setNote("fa", "", 3);
	interval.setInterval(note1, note2);
	invertion = interval.getInvertion();
	cout << invertion << endl;	
}

void othersTest(){
	//titulo
	cout << endl << endl << "- OTHERS" << endl << endl;
	//test
	Interval interval;
	Note note1, note2;
	
	note1.setNote("do", "", 3);
	
	note2.setNote("do", "", 3);
	interval.setInterval(note1, note2);
	interval.invert();
	cout << interval << endl;
	note2.setNote("re", "", 3);
	interval.setInterval(note1, note2);
	interval.invert();
	cout << interval << endl;
	note2.setNote("re", "#", 3);
	interval.setInterval(note1, note2);
	interval.invert();
	cout << interval << endl;
	note2.setNote("mi", "b", 2);
	interval.setInterval(note1, note2);
	interval.invert();
	cout << interval << endl;
	
	note1.setNote("fa", "#", 3);

	note2.setNote("mi", "#", 3);
	interval.setInterval(note1, note2);
	interval.invert();
	cout << interval << endl;
	note2.setNote("si", "#", 2);
	interval.setInterval(note1, note2);
	interval.invert();
	cout << interval << endl;
	note2.setNote("la", "", 3);
	interval.setInterval(note1, note2);
	interval.invert();
	cout << interval << endl;
	note2.setNote("do", "#", 4);
	interval.setInterval(note1, note2);
	interval.invert();
	cout << interval << endl;
	
	note1.setNote("si", "", 3);
	
	note2.setNote("do", "", 3);
	interval.setInterval(note1, note2);
	interval.invert();
	cout << interval << endl;
	note2.setNote("re", "#", 4);
	interval.setInterval(note1, note2);
	interval.invert();
	cout << interval << endl;
	note2.setNote("la", "b", 4);
	interval.setInterval(note1, note2);
	interval.invert();
	cout << interval << endl;
	note2.setNote("fa", "", 3);
	interval.setInterval(note1, note2);
	interval.invert();
	cout << interval << endl;
}

void intervalTest(){
	invalidConstructorsIntervalByNotesTest();
	validConstructorsIntervalByNotesTest();
	invalidConstructorsIntervalByNameTest();
	validConstructorsIntervalByNameTest();
	gettersTest();
	othersTest();
}
