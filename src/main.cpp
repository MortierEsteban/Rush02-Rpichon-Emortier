#include "AI.hpp"
#include <unistd.h>
#include <fstream>
#include <sys/types.h>
#include <string>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
using namespace std;
#include "gameData.hpp"
int main()
{
    int i = 0;
    gameData data;

    std::ofstream outfile ("rep.txt");
    std::string line;
    outfile << data.width << " " << data.height << " " << data.winLen << " " << data.player_start << " " << data.time << " " << data.gain << " " << data.lastPlay << " " << std::endl;
    while (1){
        if (data.player_start == 1) {
            // CALCUL DU COUP A JOUER
            // std::cout << COUP A JOUER;
            std::cout << data.width / 2 << std::endl;
            outfile << data.width/2 << std::endl;
            data.updateField(data.width/2, data.myChar);
        }
        std::getline(std::cin, line);
        i++;
        outfile << line << std::endl;
        data.updateField(atoi(line.c_str()),data.ennemiChar);
        data.player_start = 1;
    }
}
