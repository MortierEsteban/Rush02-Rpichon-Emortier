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
				char myChar;
				char ennemiChar;
				void	initGameTab();
				void	dispGameTab();
				void	updateField(int i, char whoPlay);
				bool	checkWin(char verif, int posx, int posy);
				int		recursive_find(int x, int y,char teamletter,std::vector<std::vector<char > >Tmptab, int depth);
				std::vector<std::vector<char > > getGameTab(void) {return gameTab;}
private:
		std::vector<std::vector<char > > gameTab;
};
#endif
