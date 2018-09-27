#include <ics46/factory/DynamicFactory.hpp>
#include "MyOthelloAI.hpp"

#include <iostream>

ICS46_DYNAMIC_FACTORY_REGISTER(OthelloAI, rjmcgrat::MyOthelloAI, "Rodney's AI (Required)");

std::pair<int, int> rjmcgrat::MyOthelloAI::chooseMove(const OthelloGameState& state) {

	int highestX = 0;
	int highestY = 0;
	int highestEval;

	if (state.isBlackTurn()) {
		highestEval = (state.blackScore() - state.whiteScore());
	} else {
		highestEval = (state.whiteScore() - state.blackScore());
	}

	for (int x = 0; x < 8; x++) {
		for (int y = 0; y < 8; y++)
		{
			
			if (state.isValidMove(x, y)) {
				std::unique_ptr<OthelloGameState> possibility = state.clone();
				//possibility->makeMove(x, y);
				int possibilityValue = search(*possibility, 3, state.isBlackTurn());

				if (possibilityValue >= highestEval) {
					highestEval = possibilityValue;
					highestX = x;
					highestY = y;
				}

			}

		}
	}

	return std::pair(highestX, highestY);

}

int rjmcgrat::MyOthelloAI::search (OthelloGameState& state, int depth, bool isBlack) {

	if (depth == 0) {
		if (isBlack) {
			return (state.blackScore() - state.whiteScore());
		} else if (!isBlack){
			return (state.whiteScore() - state.blackScore());
		}
	} else {



		int possibilityValue;

		if ((isBlack && state.isBlackTurn()) || (!isBlack && state.isWhiteTurn())) { //ai's turn

			int highestEval;

			if (state.isBlackTurn()) {
				highestEval = (state.blackScore() - state.whiteScore());
			} else {
				highestEval = (state.whiteScore() - state.blackScore());
			}

			for (int x = 0; x < 8; x++) {
				for (int y = 0; y < 8; y++)
				{
					
					if (state.isValidMove(x, y)) {
						std::unique_ptr<OthelloGameState> possibility = state.clone();
						possibility->makeMove(x, y);
						possibilityValue = search(*possibility, depth - 1, isBlack);
					}

					if (possibilityValue >= highestEval) {
						highestEval = possibilityValue;
					}

				}
			}

			return highestEval;

		} else { //other player's turn

			int lowestEval;

			if (state.isBlackTurn()) {
				lowestEval = (state.blackScore() - state.whiteScore());
			} else {
				lowestEval = (state.whiteScore() - state.blackScore());
			}

			for (int x = 0; x < 8; x++) {
				for (int y = 0; y < 8; y++)
				{
					
					if (state.isValidMove(x, y)) {
						std::unique_ptr<OthelloGameState> possibility = state.clone();
						possibility->makeMove(x, y);
						possibilityValue = search(*possibility, depth - 1, isBlack);
					}

					if (possibilityValue <= lowestEval) {
						lowestEval = possibilityValue;
					}

				}
			}

			return lowestEval;

		}



	}

	return 1;

}
