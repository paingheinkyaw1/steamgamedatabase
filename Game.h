// Specification file for the Game class
// Written By: Aye Thwe Tun, Paing Hein Kyaw

#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <iomanip>
#include <string>
#include <string>

using std::string;
using std::ostream;

using namespace std;

class Game {
	private:
		string name;
		string genre;
		string developer;
		string date;
		double price;
    int noCol;
	public:
		Game(){
			name = "";
			genre = "";
			developer = "";
			date = "";
			price = 0.00;
      noCol = 0;
		}

		Game(string n, string g, string dev, string d, double p){
			name = n;
			genre = g;
			developer = dev;
			date = d;
			price = p;
      noCol = 0;
		}

		void setName(string input){
			name = input;
		};

		void setGenre(string input){
			genre = input;
		}

		void setDev(string input){
			developer = input;
		}

		void setDate(string input){
			date = input;
		}

		void setPrice(double input){
			price = input;
		}

    void setCol(int c){
      noCol = c;
    }

		string getName() const{
			return name;
		}

		string getGenre() const{
			return genre;
		}

		string getDev() const{
			return developer;
		}

		string getDate() const{
			return date;
		}

		double getPrice() const{
			return price;
		}

    int getCol() const{
      return noCol;
    }

    // Overloaded operators
    bool operator == (const Game &right)
    {
      bool status = false;

      if (name == right.getName())
          status = true;

      return status;
    }

    bool operator < (const Game &right)
    {
      bool status = false;

      if (genre < right.getGenre())
        status = true;

      return status;
    }

    bool operator > (const Game &right)
    {
      bool status = false;

      if (genre > right.getGenre())
        status = true;

      return status;
    }

    bool operator >= (const Game &right)
    {
      bool status = false;

      if (genre >= right.getGenre())
        status = true;

      return status;
    }

    friend ostream& operator<<(ostream& strm, const Game &game)
    {
      strm << game.name << "; "
           << game.genre << "; "
           << game.developer << "; "
           << game.date << "; "
           << game.price;

      return strm;
    }
};

#endif
