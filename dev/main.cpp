#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>
#include "Globals.h"
#include "Note.h"
#include "Interval.h"
#include "NoteTest.h"
#include "IntervalTest.h"
#include "MainView.h"
#include "Button.h"
#include "Label.h"
#include "RadioButton.h"
#include "Piano.h"
#include "Key.h"
#include "RoundedRectangleShape.h"
#include "ScaleTest.h"



int main(){
	std::srand(std::time(0));
	globInit();
	MainView mainView;
	mainView.game();
	
	return 0;
}
