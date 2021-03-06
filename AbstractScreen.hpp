/*================================================================================================*/
/*
 * ScreenInterface.hpp
 *
 *  Created on: 28.10.2016
 *      Author: grzegorz
 */

/*================================================================================================*/
#ifndef ABSTRACTSCREEN_HPP_
#define ABSTRACTSCREEN_HPP_
/*================================================================================================*/
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#include <fstream>
#include "AbstractGameField.hpp"
/*================================================================================================*/
class AbstractScreen {
public:
	AbstractScreen(int fieldWidth) :
			fieldWidth(fieldWidth) {
	}
	void draw(AbstractGameField *field, int gameScore, bool isGameOver) {
		prepareWindowContext();
		getWindowContext() << makeStatusLine(gameScore, isGameOver) << std::endl << std::endl;

		int size = field->getSize();
		for (int i = 0; i < size; i++) {
			getWindowContext() << makeDivisionLine(size) << std::endl;
			getWindowContext() << makeOneLine(field->getRow(i)) << std::endl;
		}
		getWindowContext() << makeDivisionLine(size) << std::endl;
		releaseWindowContext();
	}
	virtual ~AbstractScreen() {

	}
private:
	virtual std::ostream& getWindowContext() = 0;
	virtual void prepareWindowContext() = 0;
	virtual void releaseWindowContext() = 0;
	std::string getNumberString(int number) {
		std::string fixTable[] = {
		      "",
		      "k",
		      "M",
		      "G",
		      "T," "P" };
		std::string postfix = fixTable[0];

		for (unsigned int i = 0, divisor = 1; i < (sizeof(fixTable) / sizeof(std::string)); i++) {
			if (number / divisor) {
				postfix = fixTable[i];
				number /= divisor;
				divisor *= 1024;
			} else {
				break;
			}
		}
		std::stringstream ss;
		ss << number << postfix;
		return ss.str();
	}
	std::string makeOneLine(GameFieldVector row) {
		std::stringstream ss;
		ss << "|";
		for (int i = 0; i < row.getSize(); i++) {
			int n = row.getNext();
			if (n == 0) {
				ss << std::setw(fieldWidth) << " ";
			} else {
				ss << std::setw(fieldWidth) << getNumberString(n);
			}
			ss << "|";
		}
		return ss.str();
	}
	std::string makeDivisionLine(int numberOfFields) {
		std::stringstream line;
		line << "+";

		for (int i = 0; i < numberOfFields; i++) {
			line << std::setw(fieldWidth) << std::setfill('-') << "-";
			line << "+";
		}
		return line.str();
	}
	std::string makeStatusLine(int score, bool gameOver) {
		std::stringstream status;
		status << "Score:\t" << score;
		if (gameOver)
			status << "\tGAME OVER!";
		return status.str();
	}
	int fieldWidth;
};
/*================================================================================================*/
#endif /* ABSTRACTSCREEN_HPP_ */
/*================================================================================================*/
/*                                              EOF                                               */
/*================================================================================================*/
