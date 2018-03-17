#pragma once
#include "Generations\First\open.h"
#include "Generations\First\save.h"
#include "Generations\First\points.h"
#include "Generations\First\history.h"
#include "Generations\First\settings.h"
using namespace Tools;

int main(){
	int indexer;
	bool success = true;
	option** options = new option*[Menu::Max];
	options[Menu::One] = new open(Menu::One);
	options[Menu::Two] = new save(Menu::Two);
	options[Menu::Four] = new points(Menu::Three);
	options[Menu::Three] = new history(Menu::Four);
	options[Menu::Five] = new settings(Menu::Five);
	do {
		option::removeKeysPressed();
		option::clearConsoleScreen(); std::cout << "WELCOME!" << std::endl;
		std::cout << "Please select one of the following functions:\n\n";
		for (indexer = 0; indexer < Menu::Max; indexer++)
			options[indexer]->output(false);
		if (!success) std::cout << "X) Exit\n\n" << "You have entered an invalid"
			<< " option.\nTry again or press x to exit...\n\n" << "Enter Option: ";
		else std::cout << "X) Exit\n\n" << "Enter Option: ";
		option::processKeysPressed();
		for (indexer = 0; indexer < Menu::Max; indexer++)
			if (option::keyPressed(indexer)) {
			options[indexer]->outputIntroductions();
			if (options[indexer]->update())
				options[indexer]->output();
			option::removeKeysPressed();
			option::processKeysPressed();
			if (option::keyPressed(indexer))
				indexer--;
			else break;
			}
		success = indexer < Menu::Max;
	} while (!option::keyPressed('X', 'x'));
	return 0;
}