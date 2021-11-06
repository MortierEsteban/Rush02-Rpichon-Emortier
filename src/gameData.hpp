#ifndef GAMEFIELD_HPP
# define GAMEFIELD_HPP
#include <iostream>
#include <vector>

class gameData {
public:
        gameData();
        ~gameData();
        gameData(const int nb);
        gameData(const float nb);
        gameData (gameData const & src);
        gameData & operator=(gameData const & rhs);
				int height;
				int gain;
				int time;
				int width;
				int winLen;
				int player_start;
				int lastPlay;
				void	initGameTab();
				void	dispGameTab();
				void	updateField(int i, char whoPlay);
private:
		std::vector<std::vector<char > > gameTab;
};
#endif
