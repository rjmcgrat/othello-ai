#ifndef MYOTHELLOAI_HPP
#define MYOTHELLOAI_HPP

#include "OthelloAI.hpp"

namespace rjmcgrat {


	class MyOthelloAI: public OthelloAI {

	public:
		virtual std::pair<int, int> chooseMove (const OthelloGameState& state);
	private:
		int search (OthelloGameState& state, int depth, bool isBlack);

	};


}

#endif
