#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <random>
#include <sstream>

using namespace std;

//Strategy - Allows Players to choose from different strategies to win
class Strategy{
    public:
    bool win = true;
    bool validate_win(vector<int> numbers){
        return false;
    }
    Strategy () {}

};

class Five_Evens : public Strategy{
    public:
    bool validate_win(vector<int> numbers){
        for (auto i : numbers){
            if (i%2 != 0){
                win = false;
                break;
            }
        }
        return win;
    }
};

class Five_Uneven : public Strategy{
    public:
    bool validate_win(vector<int> numbers){
        for (auto i : numbers){
            if (i%2 == 0){
                win = false;
                break;
            }
        }
        return win;
    }
};

class One_Prime : public Strategy{
    public:
    
    bool validate_win(vector<int> numbers){
        vector<int> prime_numbers = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};
        for (auto i : numbers){
            for (int j = 0; j <= prime_numbers.size(); j++){
                if (i == j){
                    win = false;
                    break;
                }
            }
        }
        return win;
    }
}; 

class Three_10 : public Strategy{
    public:
    
    bool validate_win(vector<int> numbers){
        int cnt = 0;
        for (auto i : numbers){
            if (i%10 == 0){
                cnt++;
            }
        }
        if (cnt != 3){
            win = false;
        }
        return win;
    }
};

class Two_25 : public Strategy{
    public:
    
    bool validate_win(vector<int> numbers){
        int cnt = 0;
        for (auto i : numbers){
            if (i%25 == 0){
                cnt++;
            }
        }
        if (cnt != 2){
            win = false;
        }
        return win;
    }
};

//Observer - Class observes game and is notified when a new number is created.
class Player{
    public:
        Player () {}
        virtual bool update(){
            cout << "New number Created" << endl;
        }
};

//Singleton - Only allows one instance to be created.
class Game{
    private:
    Game(){};
    int players;
    map<Player*, Strategy> strat_map;

public:
    Game(const Game&) = delete; 

    static Game& getInstance(){ 
        static Game Instance;
        return Instance;
    }

    void registerObserver(Player *_o, Strategy _s){
        if (players > 5){
            return;
        }

        strat_map.insert(pair<Player*, Strategy>(_o,_s));
        players++;
    }

    void notifyObserver(){
        for (auto const&i : strat_map) {
            i.first->update();
        }
    } 

    int create_rng(){
        static std::default_random_engine rng;

        std::uniform_real_distribution<int> dist(1, 100); 
        notifyObserver();
        return dist(rng);
    }

    void play_round(){
        vector<int> numeros;
        for (int i = 0; i < 5; i++){
            int temp = create_rng();
            numeros.push_back(temp);
        }
        int cnt = 0;
        for (auto const&i : strat_map) {
            i.second.validate_win(numeros);
            if(i.second.win = true){
                cout << "Player " << cnt << " has won!" << endl;
                break;
            }
        }
    }
};

int main(){
    Game& game = Game::getInstance();
    Player p1;
    Player p2;
    Player p3;
    Player p4;
    Player p5;
    Player p6;

    Five_Evens evens;
    Five_Uneven unevens;
    One_Prime prime;
    Three_10 tens;
    Two_25 twofive;

    game.registerObserver(&p1,evens);
    game.registerObserver(&p2,unevens);
    game.registerObserver(&p3,prime);
    game.registerObserver(&p4,tens);
    game.registerObserver(&p5,twofive);


    game.play_round();
}
