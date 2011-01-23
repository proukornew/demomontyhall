#include <iostream>
#include <cstring>
#include <gsl/gsl_rng.h>
#include <ctime>
#include "mix_bj.h"

using namespace std;

gsl_rng * r;

class Door {
	public:
		bool prize;
		Door ();
};
Door::Door () : prize(false) {}
class setOfDoor {
	public:
		Door set[3];
		setOfDoor ();
};
setOfDoor::setOfDoor () {
	set[(gsl_rng_get(r) % 3)].prize = true;
}
class Game {
	public:
		setOfDoor start;
		short ourChoose;
		short enemyChoose;
		Game ();
		bool getResult (bool);
};
Game::Game () {
	ourChoose = gsl_rng_get(r) % 3;
	if (start.set[ourChoose].prize) {
		enemyChoose = (ourChoose + (gsl_rng_get(r) % 2) + 1) % 3; 
	}
	else {
		enemyChoose = (start.set[(ourChoose+1) % 3].prize) ? (ourChoose+2) % 3 : (ourChoose+1) % 3;
	}
}
bool Game::getResult (bool a) {
	if(a) {
		return start.set[3-(ourChoose+enemyChoose)].prize;
	}
	else {
		return start.set[ourChoose].prize;
	}
}
int main(int argc, char **argv)
{	
	gsl_rng_default_seed = mix_1ed(time(NULL), clock(), getpid());
	r = gsl_rng_alloc(gsl_rng_default);
	Game* test[100000];
	unsigned goods = 0;
	for(register unsigned i = 0; i < 100000; i++) {
		test[i] = new Game;
		if(argc > 1 && strcmp(argv[1], "strategy") == 0) {
			goods += (unsigned) test[i]->getResult(true);
		}
		else {
			goods += (unsigned) test[i]->getResult(false);
		}
		if(argc > 2 && strcmp(argv[2], "debug") == 0) {
			cout << test[i]->enemyChoose << '|' << test[i]->ourChoose << '|' << test[i]->start.set[0].prize << '|' << test[i]->start.set[1].prize << '|' << test[i]->start.set[2].prize << '\n';
		}
	}
	cout << goods << endl;
	gsl_rng_free(r);
	return 0;
}
