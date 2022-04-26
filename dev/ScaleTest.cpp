#include "ScaleTest.h"
#include <iostream>
#include "Note.h"
#include "Scale.h"
using namespace std;

void invalidConstructorsScaleTest(){
	//titulo
	cout << endl << endl << "- CONSTRUCTOR CON ENTRADAS INVALIDAS" << endl << endl;
	//test
	Note fundamental;
	Scale scale;	
	
	fundamental.setNote("do", "", 4);
	cout << scale.setScale(fundamental, "mayor") << endl;
	fundamental.setNote("do", "bb", 3);
	cout << scale.setScale(fundamental, "mayor") << endl;
	
	fundamental.setNote("do", "", 3);
	cout << scale.setScale(fundamental, "mayorrr") << endl;
	
	fundamental.setNote("sol", "#", 3);
	cout << scale.setScale(fundamental, "mayor") << endl;
	
	cout << scale << endl;
}


void validConstructorsScaleTest(){
	//titulo
	cout << endl << endl << "- CONSTRUCTOR CON ENTRADAS VALIDAS" << endl << endl;
	//test
	Note fundamental;
	Scale scale;
	
	fundamental.setNote("do", "", 3);
	cout << scale.setScale(fundamental,"mayor") << endl;
	cout << scale << endl;
	scale.setScale(fundamental, "menor natural");
	cout << scale << endl;
	
	fundamental.setNote("fa", "#", 3);
	scale.setScale(fundamental,"mayor");
	cout << scale << endl;
	scale.setScale(fundamental, "menor natural");
	cout << scale << endl;
	
	fundamental.setNote("si", "b", 3);
	scale.setScale(fundamental,"mayor");
	cout << scale << endl;
	scale.setScale(fundamental, "menor natural");
	cout << scale << endl;
	
}

void generatorTest(){
	for(int i=0;i<10;i++) {
		vector<Note> fundamentalExclusions;
		vector<string> typeExclusions;
		
		Scale scale;
		scale.setScale(randomScale(fundamentalExclusions, typeExclusions));
		
		cout << scale << endl;
	}
}

void scaleTest(){
//	invalidConstructorsScaleTest();
//	validConstructorsScaleTest();
	generatorTest();
}
