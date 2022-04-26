#include "NoteTest.h"
#include <iostream>
#include "Note.h"
#include "Globals.h"

using namespace std;

void invalidConstructorsNoteTest(){
	//titulo
	cout << endl << endl << "- SETNOTE CON ENTRADAS INVALIDAS" << endl << endl;
	//test
	Note note;
	cout << note.setNote("", "") << endl << note << endl;
	cout << note.setNote("do#") << endl << note << endl;
	cout << note.setNote("mii") << endl << note << endl;
	cout << note.setNote("fa","##") << endl << note << endl;
	cout << note.setNote("do","", 10) << endl << note << endl;
	cout << note.setNote("do","", -3) << endl << note << endl;
	cout << note.setNote("do","b",-2) << endl << note << endl;
	cout << note.setNote("sol", "#", 8) << endl << note << endl;
}

void validConstructorsNoteTest(){
	//titulo
	cout << endl << endl << "- SETNOTE CON ENTRADAS VALIDAS" << endl << endl;
	//test
	Note note;
	cout << note.setNote() << endl << note << endl;
	cout << note.setNote("do") << endl << note << endl;
	cout << note.setNote("re", "") << endl << note << endl;
	cout << note.setNote("mi", "bb") << endl << note << endl;
	cout << note.setNote("fa", "b", 6) << endl << note << endl;
	cout << note.setNote("sol", "#", -2) << endl << note << endl;
	cout << note.setNote("si", "x", 0) << endl << note << endl;
}

void invalidSettersNoteTest(){
	//titulo
	cout << endl << endl << "- SETTERS CON ENTRADAS INVALIDAS" << endl << endl;
	//aux
	Note do3;
	Note note;
	vector<Note> specialNotes;		//some kind of extremes notes
	note.setNote("re","b",-2);
	specialNotes.push_back(note);
	note.setNote("fa", "#", 8);
	specialNotes.push_back(note);
	note.setNote("do","", -2);
	specialNotes.push_back(note);
	note.setNote("sol","", 8);
	specialNotes.push_back(note);
	note.setNote("do","b",-1);
	specialNotes.push_back(note);
	note.setNote("sol","#", 7);
	specialNotes.push_back(note);
	//test
	cout << do3.setName("") << endl;
	cout << do3.setName("do#") << endl;
	cout << do3.setName("mii") << endl;
	cout << do3.setSignature("##") << endl;
	cout << do3.setOctave(10) << endl;
	cout << do3.setOctave(-3) << endl;
	cout << specialNotes[0].setName("do") << endl;
	cout << specialNotes[1].setName("sol") << endl;
	cout << specialNotes[2].setSignature("b") << endl;
	cout << specialNotes[3].setSignature("#") << endl;
	cout << specialNotes[4].setOctave(-2) << endl;
	cout << specialNotes[5].setOctave(8) << endl;
	//salida
	//(extra a las advertencias, para verificar)
	for (Note note : specialNotes){
		cout << note << endl;
	}
}

void validSettersNoteTest(){
	//titulo
	cout << endl << endl << "- SETTERS CON ENTRADAS VALIDAS" << endl << endl;
	//aux
	vector<Note> do3Copies;
	for(int i=0;i<12;i++) { 
		do3Copies.push_back(Note());
	}
	vector<string> strParameters = {"do", "mi", "si", "", "bb", "b", "#", "x"};
	vector<int> intParameters = {8, 3, 0, -2};
	//test
	for(size_t i=0;i<do3Copies.size();i++) { 
		if (i < 3){
			do3Copies[i].setName(strParameters[i]);
		}
		else if (i < 8){
			do3Copies[i].setSignature(strParameters[i]);
		}
		else {
			do3Copies[i].setOctave(intParameters[i-8]);
		}
	}
	//salida
	for(Note note : do3Copies){
		cout << note << endl;
	}
}

void invalidOtherNoteTest(){
	//titulo
	cout << endl << endl << "- OTHERS CON ENTRADAS INVALIDAS" << endl << endl;
	//aux
	Note do3;
	Note note;
	vector<Note> specialNotes;		//some kind of extremes notes
	note.setNote("re","b",-2);
	specialNotes.push_back(note);
	note.setNote("fa", "#", 8);
	specialNotes.push_back(note);
	note.setNote("do","", -2);
	specialNotes.push_back(note);
	note.setNote("sol","", 8);
	specialNotes.push_back(note);
	note.setNote("do","b",-1);
	specialNotes.push_back(note);
	note.setNote("sol","#", 7);
	specialNotes.push_back(note);
	//test
	cout << do3.shiftName(-50) << endl;
	cout << do3.shiftName(70) << endl;
	cout << do3.shiftSignature(-10) << endl;
	cout << do3.shiftSignature(10) << endl;
	cout << do3.shiftOctave(-6) << endl;
	cout << do3.shiftOctave(7) << endl;
	cout << specialNotes[0].shiftName(-1) << endl;
	cout << specialNotes[1].shiftName(1) << endl;
	cout << specialNotes[2].shiftSignature(-1) << endl;
	cout << specialNotes[3].shiftSignature(1) << endl;
	cout << specialNotes[4].shiftOctave(-1) << endl;
	cout << specialNotes[5].shiftOctave(1) << endl;
	//salida
	//(extra a las advertencias, para verificar)
	for (Note note : specialNotes){
		cout << note << endl;
	}
}

void validOtherNoteTest(){
	//titulo
	cout << endl << endl << "- OTHERS CON ENTRADAS VALIDAS" << endl << endl;
	//aux
	vector<Note> fa3Copies;
	Note note;
	for(int i=0;i<8;i++) {
		note.setNote("fa");
		fa3Copies.push_back(note);
	}
	vector<Note> do3Copies;
	for(int i=0;i<8;i++) {
		note.setNote("do");
		do3Copies.push_back(note);
	}
	
	vector<int> nameParameters = {-2, 2, -3, 3, -4, 4, -9, 10};
	vector<int> signatureParameters = {-2, -1, 1, 2};
	vector<int> octaveParameters = {5,0,-3,-5};
	
	//test
	for(size_t i=0;i<fa3Copies.size();i++) { 
		fa3Copies[i].shiftName(nameParameters[i]);
	}
	for(size_t i=0;i<4;i++) { 
		do3Copies[i].shiftSignature(signatureParameters[i]);
	}
	for(size_t i=4;i<do3Copies.size();i++) { 
		do3Copies[i].shiftOctave(octaveParameters[i-4]);
	}
	
	//salida
	for(size_t i=0;i<fa3Copies.size();i++) { 
		cout << fa3Copies[i] << endl;
	}
	cout << endl;
	for(size_t i=0;i<4;i++) { 
		cout << do3Copies[i] << endl;
	}
	cout << endl;
	for(size_t i=4;i<do3Copies.size();i++) { 
		cout << do3Copies[i] << endl;
	}
	cout << endl;
}

void validGetNotesByPositionsTest(){
	//titulo
	cout << endl << endl << "- GETNOTESBYPOSITION CON ENTRADAS VALIDAS" << endl << endl;
	
	//primeros
	vector<Note> firstNotes = getNotesByPosition(60);
	for (Note note : firstNotes){
		cout << note << endl;
	}
	cout << endl;
	//ultimos
	vector<Note> lastNotes = getNotesByPosition(71);
	for (Note note : lastNotes){
		cout << note << endl;
	}
	cout << endl;
	//del medio
	vector<Note> middleNotes = getNotesByPosition(63);
	for (Note note : middleNotes){
		cout << note << endl;
	}
	cout << endl;
}




void noteTest(){
	invalidConstructorsNoteTest();
	validConstructorsNoteTest();
	invalidSettersNoteTest();
	validSettersNoteTest();
	invalidOtherNoteTest();
	validOtherNoteTest();
	validGetNotesByPositionsTest();
}
