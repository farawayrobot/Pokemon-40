#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <sstream>
using namespace std;

vector<string> types = {"Normal", "Fighting", "Flying", "Poison", "Ground", "Rock", "Bug", "Ghost", "Steel", "Fire", "Water", "Grass", "Electric", "Psychic", "Ice", "Dragon", "Dark", "Fairy"};

void die(string s = "INVALID INPUT!") {
	cout << s << endl;
	exit(EXIT_FAILURE);
}

//void load_type {
//	ifstream ins
//}

//Holds a record for a single species of Pokemon, such as Pikachu
class Pokemon {
  public:
	//YOU: Add member variable ints for each of the following:
	//index - what index it is in the pokedex
	//name (this is a string not an int)
	//hp - how much damage it takes before dying fainting
	//attack - this number gets multiplied by the move's power to determine damage
	//defense - incoming damage gets divided by this number
	//speed - whichever pokemon has the highest speed attacks first, flip a coin on a tie
	//special - like attack and defense both, but for special moves
	//Note: this is also the order the data is ordered in the file
	//YOU: Add member variables of type string for type1 and type2
	int index = 0;
	string name = "MisingNo";
	int hp = 1;
	int attack = 1;
	int defense = 1;
	int speed = 1;
	int special = 1;
	string type1 = "poop", type2 = "poop2"; //string filled incase database doesn't load
};
vector<Pokemon> pokemon_db; //Holds all pokemon known to mankind

//This function reads from the "pokemon.txt" file in the directory and loads the data into the pokemon_db global vector
//Each row has: pokemon number, name, hp, etc.
void load_pokemon_db(string filename = "pokemon.txt", string filename2 = "types.txt") {
	ifstream ins(filename);
	if (!ins) die("Couldn't load file "s + filename);
	ifstream ins2(filename2);
	if (!ins2) die("Couldn't load file"s + filename2);
//YOU: Read from the files the data into a temporary Pokemon, getting the stats from pokemon.txt and its types from types.txt
//YOU: After vetting it (make sure you handle Mr. Mime 122  properly) push it back into pokemon_db
	Pokemon temp;
	Pokemon temp2;//this stores unwanted variables
//main loop bringing data into the vector
	while (ins) {
//this resets type2 to not push older value incase pokemon only has one type
		temp.type2 = " ";
		string nametest;
		string inpoke;
		stringstream outpoke;
		getline(ins, inpoke, '\n');
		outpoke << inpoke;
		outpoke >> temp.index >> temp.name >> nametest;

//check is pokemon name is longer than one word.
		if (isdigit(nametest[0])) {
			temp.hp = stoi(nametest);
		} else {
			temp.name += " " + nametest;
			outpoke >> temp.hp;
		}


		outpoke >> temp.attack >> temp.defense >> temp.speed >> temp.special;
		if (!ins) break;
		string inbuffer;
		stringstream outbuffer;
		getline(ins2, inbuffer, '\n');
		outbuffer << inbuffer;
		outbuffer >> temp2.index >> temp2.name;
		bool istype = false;
//checks to see if pokemon name is greater than one word
		while (!istype) {
			outbuffer >> nametest;
			for (int i = 0; i < types.size(); i++) {
				if (types.at(i) == nametest) {
					temp.type1 = nametest;
					istype = true;
				}
			}
			temp2.name += " " + nametest;

		}


//		if (temp2.name == "Mr.") {
//			string mime;
//			outbuffer >> mime;
//			temp2.name += " " + mime;
//		}
		outbuffer >> temp.type2;
		pokemon_db.push_back(temp);
	}
}

//This class holds a record for each move in the game
class Move {
  public:
//YOU: Add member variable for each of these:
//int index, string name, string type, string category, int PP, int power, int accuracy
	int index = 0;
	string name, type, category;
	int PP = 0;
	int power = 0;
	int accuracy = 0;


};

vector<Move> move_db;

//Reads all moves from moves.txt into move_db
//Be sure to discardasd all status moves
void load_move_db(string filename = "moves.txt") {
	ifstream ins(filename);
	if (!ins) die("Couldn't load "s + filename);
	Move temp;
	string test;
	int testnum = 0;
	while (ins) {
		bool istype = false;
		string inbuffer;
		stringstream outbuffer;
		getline(ins, inbuffer, '\n');
//		cout << inbuffer << endl;

		outbuffer << inbuffer;
		outbuffer >> temp.index >> temp.name;
		outbuffer >> test;

		while (!istype) {
//			cout << "test" << endl;
			for (int i = 0; i < types.size(); i++) {
//				cout << types.at(i) << test << endl;
				if (types.at(i) == test) {
					temp.type = test;
					istype = true;
				}
			}
			if (!istype) {
				temp.name += " " + test;
				outbuffer >> test;
			} else {
				temp.type = test;
			}
		}

		outbuffer >> temp.category >> temp.PP;
//these deal with moves with - in them.
		outbuffer >> testnum;
		if (!testnum) temp.power = 0;
		else temp.power = testnum;

		outbuffer >> testnum;
		if (!testnum) temp.accuracy = 0;
		else {
//			testnum.pop_back();
			temp.accuracy = testnum;
		}
		if (!ins) break;



//		ins >> temp.index >> temp.name >> temp.type >> temp.category >> temp.PP >> temp.power >> temp.accuracy;
		move_db.push_back(temp);
		//YOU: Read from the file, make a temp Move with all the data read in
		//YOU: Push it back into the move_db
	}
}

//PART 2
//This conducts a one versus one battle between two pokemon of your choice

class Team {
  public:

	string name;
	Pokemon starter;
	vector <Move> teamMoves;

};


//FIXME need to change the data input to support more than one word names for pokemon and moves

void battle_mode() {
	bool choicesMade1 = false;
	bool choicesMade2 = false;
	Team one;
	Team two;
//Intro to pokemon for the funsys
	cout << "Hello there! and Welcome to the world of POKEMON!\nThis world is inhabited by creatures called POKEMON.\nFor some people POKEMON are pets. Today we use them to fight!\n\n\n First, what is your name?\n";

	cin >> one.name;

	cout << "Right! so your name is " << one.name << "!\nThis is my grandson. He's been your rival since you were a baby.\n...Erm, what is his name again?\n";

//have to clear the c buffer ugh
	cin >> two.name;
	cin.clear();
	cin.ignore(100, '\n');

	cout << "That's right! I remember now! His name is " << two.name << "!\n\n\nYour very own POKEMON legend is about to unfold!\nA world of dreams and adventures with POKEMON awaits! Lets go!\n\n";



	while (!choicesMade1) {
		cout << one.name << endl;
		cout << "Please enter the pokemon name or index number\n\n";
//		bool inputcheck = false;
		string inputTemp;
		string pokeinput;


		getline(cin, pokeinput, '\n');

		//this checks if the input is an int and then will set search parameters to poke.index
		int pokeindex;
		if (isdigit(pokeinput[0])) {
			pokeindex = stoi(pokeinput);
		}

//put in a check for lowercase letter in teh first spot then to upper

		char firstletter;
		firstletter = (toupper(pokeinput[0]));
		pokeinput[0] = firstletter;

		for (int i = 0 ; i < pokeinput.size(); i++) {
			int j = i + 1;
			char temp;
			temp = tolower(pokeinput[j]);
			pokeinput[j] = temp;
		}

//scans across pokemon database and sets a variable to the vector location if input matches.
		int pokeMatch = -1;
		for (int i = 0; i < pokemon_db.size(); i++) {
			if (pokeindex == pokemon_db[i].index) {
				pokeMatch = pokemon_db[i].index - 1;
				break;
			}
			//		cout << pokemon_db[i].name << " " << pokeinput;
			if (pokeinput == pokemon_db[i].name) {
				pokeMatch = pokemon_db[i].index - 1;
				break;
			}
		}
		if (pokeMatch == -1) die();

		//confirm choice FIXME
		cout << "You picked " << pokemon_db[pokeMatch].name << endl << endl;
//sets team one starter pokemon stats
		one.starter.index = pokemon_db[pokeMatch].index;
		one.starter.name = pokemon_db[pokeMatch].name;
		one.starter.hp = pokemon_db[pokeMatch].hp;
		one.starter.attack = pokemon_db[pokeMatch].attack;
		one.starter.defense = pokemon_db[pokeMatch].defense;
		one.starter.speed = pokemon_db[pokeMatch].speed;
		one.starter.special = pokemon_db[pokeMatch].special;
		one.starter.type1 = pokemon_db[pokeMatch].type1;
		one.starter.type2 = pokemon_db[pokeMatch].type2;


		//Pick four moves
		cout << "Pick four moves for your " << one.starter.name << " to learn!\n";

		for (int i = 0 ; i < 4; i++) {
			string moveName;
			int moveMatch = -1;
			int moveIndex;

			//counts move
			string moveCountOut;
			if (i == 0) moveCountOut = "first";
			else if (i == 1) moveCountOut = "second";
			else if (i == 2) moveCountOut = "third";
			else moveCountOut = "fourth";

			cout << "Please enter the name or index of the " << moveCountOut << " move you want to teach to your pokemon.\n";

			getline(cin, moveName, '\n');

			//		cout << moveName;

			//sets struggle as move if user puts empty string
//			if (moveName == " ") moveMatch = 165;


			if (isdigit(moveName[0])) {
				moveIndex = stoi(moveName);
			}

			char firstletter;
			firstletter = (toupper(moveName[0]));
			moveName[0] = firstletter;

			for (int i = 0 ; i < moveName.size(); i++) {
				int j = i + 1;
				char temp;
				temp = tolower(moveName[j]);
				moveName[j] = temp;
			}

			for (int i = 0; i < move_db.size(); i++) {
				if (moveIndex == move_db[i].index) {
					moveMatch = i;
					break;
				}
				//			cout << move_db[i].name << " " << moveName << endl;
				if (moveName == move_db[i].name) {
					moveMatch = i;
					break;
				}

			}

			if (moveMatch == -1) die();

			if (move_db[moveMatch].category == "Status") {
				moveMatch = 156;
				cout << "Move Replaced\n";
			}


			cout << "you picked " <<  move_db[moveMatch].name << endl;

//adds move from database to team move vector
			Move temp;
			temp.index = move_db[moveMatch].index;
			temp.name = move_db[moveMatch].name;
			temp.type = move_db[moveMatch].type;
			temp.category = move_db[moveMatch].category;
			temp.PP = move_db[moveMatch].PP;
			temp.power = move_db[moveMatch].power;
			temp.accuracy = move_db[moveMatch].accuracy;

			one.teamMoves.push_back(temp);
		}
		/*
				cout << one.teamMoves[0].name << endl;
				cout << one.teamMoves[1].name << endl;
				cout << one.teamMoves[2].name << endl;
				cout << one.teamMoves[3].name << endl;
		*/

		choicesMade1 = true;
	}

//pokemon and moves selection
//Pick a Pokemon and a move for team two
	while (!choicesMade2) {
		//Pick a Pokemon and a move for team one
		cout << two.name << endl;
		cout << "Please enter the pokemon name or index number\n\n";
//FIXME need to add more than one word input
		string pokeinput;
		int pokeindex;

		getline(cin, pokeinput, '\n');

		//this checks if the input is an int and then will set search parameters to poke.name
		if (isdigit(pokeinput[0])) {
			pokeindex = stoi(pokeinput);
		}

		char firstletter;
		firstletter = (toupper(pokeinput[0]));
		pokeinput[0] = firstletter;

		for (int i = 0 ; i < pokeinput.size(); i++) {
			int j = i + 1;
			char temp;
			temp = tolower(pokeinput[j]);
			pokeinput[j] = temp;
		}

		//scans across pokemon database and sets a variable to the vector location if input matches.
		int pokeMatch = -1;
		for (int i = 0; i < pokemon_db.size(); i++) {
			if (pokeindex == pokemon_db[i].index) {
				pokeMatch = pokemon_db[i].index - 1;
				break;
			}
			if (pokeinput == pokemon_db[i].name) {
				pokeMatch = pokemon_db[i].index - 1;
				break;
			}
		}

		if (pokeMatch == -1) return;

		cout << "You picked " << pokemon_db[pokeMatch].name << endl << endl;
//sets team two pokemon stats
		two.starter.index = pokemon_db[pokeMatch].index;
		two.starter.name = pokemon_db[pokeMatch].name;
		two.starter.hp = pokemon_db[pokeMatch].hp;
		two.starter.attack = pokemon_db[pokeMatch].attack;
		two.starter.defense = pokemon_db[pokeMatch].defense;
		two.starter.speed = pokemon_db[pokeMatch].speed;
		two.starter.special = pokemon_db[pokeMatch].special;
		two.starter.type1 = pokemon_db[pokeMatch].type1;
		two.starter.type2 = pokemon_db[pokeMatch].type2;


		//Pick four moves
		cout << "Pick four moves for your " << two.starter.name << " to learn!\n";

		for (int i = 0 ; i < 4; i++) {
			string moveName;
			int moveMatch = -1;
			int moveIndex;

			//counts move
			string moveCountOut;
			if (i == 0) moveCountOut = "first";
			else if (i == 1) moveCountOut = "second";
			else if (i == 2) moveCountOut = "third";
			else moveCountOut = "fourth";

			cout << "Please enter the name or index of the " << moveCountOut << " move you want to teach to your pokemon.\n";
//FIXME cin needs to have more than one word input
			getline(cin, moveName, '\n');


			//sets struggle as move if user puts empty string
			//	if (moveName == " ") moveMatch = 165;

			if (isdigit(moveName[0])) {
				moveIndex = stoi(moveName);
			}

			char firstletter;
			firstletter = (toupper(moveName[0]));
			moveName[0] = firstletter;


			for (int i = 0 ; i < moveName.size(); i++) {
				int j = i + 1;
				char temp;
				temp = tolower(moveName[j]);
				moveName[j] = temp;
			}

			for (int i = 0; i < move_db.size(); i++) {
				if (moveIndex == move_db[i].index) {
					moveMatch = i;
					break;
				}
				if (moveName == move_db[i].name) {
					moveMatch = i;
					break;
				}
			}
			if (moveMatch == -1) break;

			cout << "you picked " <<  move_db[moveMatch].name << endl;

			Move temp;
			temp.index = move_db[moveMatch].index;
			temp.name = move_db[moveMatch].name;
			temp.type = move_db[moveMatch].type;
			temp.category = move_db[moveMatch].category;
			temp.PP = move_db[moveMatch].PP;
			temp.power = move_db[moveMatch].power;
			temp.accuracy = move_db[moveMatch].accuracy;

			two.teamMoves.push_back(temp);
		}
		/*
				cout << two.teamMoves[0].name << endl;
				cout << two.teamMoves[1].name << endl;
				cout << two.teamMoves[2].name << endl;
				cout << two.teamMoves[3].name << endl;
		*/
		choicesMade2 = true;
	}

//Whichever Pokemon has the higher speed goes first

//Have them do damage to each other based on their move * power * type modifier

//Target Pokémon reduces damage based on its defense or special defense


}

//PART 2
void explore_mode() {
	Team hero;
	Team rival;
	int nameRoll = -1;
	nameRoll = rand() % 3;

	if (nameRoll == 0) {
		rival.name = "Blue";
	} else if (nameRoll == 1) {
		rival.name = "Red";
	} else {
		rival.name = "Gary";
	}


//Intro to pokemon for the funsys
	cout << "Hello there! and Welcome to the world of POKEMON!\nThis world is inhabited by creatures called POKEMON.\nFor some people POKEMON are pets. Today we use them to fight!\n\n\n First, what is your name?\n";

	cin >> hero.name;
	cin.clear();
	cin.ignore(100, '\n');



	cout << "Right! so your name is " << hero.name << "!\nThis is my grandson. He's been your rival since you were a baby.\n";

//	cin >> rival.name;

	cout << "His name is " << hero.name << "!\n\n\nYour very own POKEMON legend is about to unfold!\nA world of dreams and adventures with POKEMON awaits! Lets go!\n\n";


	bool heroteam = false;
	while (!heroteam) {
		cout << hero.name << endl;
		cout << "Please enter the pokemon name or index number\n\n";
//		bool inputcheck = false;
		string inputTemp;
		string pokeinput;

		getline(cin, pokeinput, '\n');

		//this checks if the input is an int and then will set search parameters to poke.index
		int pokeindex;
		if (isdigit(pokeinput[0])) {
			pokeindex = stoi(pokeinput);
		}

		char firstletter;
		firstletter = (toupper(pokeinput[0]));
		pokeinput[0] = firstletter;

		//scans across pokemon database and sets a variable to the vector location if input matches.
		int pokeMatch = -1;
		for (int i = 0; i < pokemon_db.size(); i++) {
			if (pokeindex == pokemon_db[i].index) {
				pokeMatch = pokemon_db[i].index - 1;
				break;
			}
			if (pokeinput == pokemon_db[i].name) {
				pokeMatch = pokemon_db[i].index - 1;
				break;
			}
		}
		if (pokeMatch == -1) die();

		//confirm choice FIXME
		cout << "You picked " << pokemon_db[pokeMatch].name << endl << endl;
//sets team one starter pokemon stats
		hero.starter.index = pokemon_db[pokeMatch].index;
		hero.starter.name = pokemon_db[pokeMatch].name;
		hero.starter.hp = pokemon_db[pokeMatch].hp;
		hero.starter.attack = pokemon_db[pokeMatch].attack;
		hero.starter.defense = pokemon_db[pokeMatch].defense;
		hero.starter.speed = pokemon_db[pokeMatch].speed;
		hero.starter.special = pokemon_db[pokeMatch].special;
		hero.starter.type1 = pokemon_db[pokeMatch].type1;
		hero.starter.type2 = pokemon_db[pokeMatch].type2;


		//Pick four moves
		cout << "Pick four moves for your " << hero.starter.name << " to learn!\n";

		for (int i = 0 ; i < 4; i++) {
			string moveName;
			int moveMatch = -1;
			int moveIndex;

			//counts move
			string moveCountOut;
			if (i == 0) moveCountOut = "first";
			else if (i == 1) moveCountOut = "second";
			else if (i == 2) moveCountOut = "third";
			else moveCountOut = "fourth";

			cout << "Please enter the name or index of the " << moveCountOut << " move you want to teach to your pokemon.\n";

			cin >> moveName;

			//sets struggle as move if user puts empty string
//			if (moveName == " ") moveMatch = 165;


			if (isdigit(moveName[0])) {
				moveIndex = stoi(moveName);
			}

			char firstletter;
			firstletter = (toupper(moveName[0]));
			moveName[0] = firstletter;

			for (int i = 0; i < move_db.size(); i++) {
				if (moveIndex == move_db[i].index) {
					moveMatch = i;
					break;
				}
				if (moveName == move_db[i].name) {
					moveMatch = i;
					break;
				}

			}
			if (moveMatch == -1) die();

			cout << "you picked " <<  move_db[moveMatch].name << endl;

//adds move from database to team move vector
			Move temp;
			temp.index = move_db[moveMatch].index;
			temp.name = move_db[moveMatch].name;
			temp.type = move_db[moveMatch].type;
			temp.category = move_db[moveMatch].category;
			temp.PP = move_db[moveMatch].PP;
			temp.power = move_db[moveMatch].power;
			temp.accuracy = move_db[moveMatch].accuracy;

			hero.teamMoves.push_back(temp);
		}
		/*
				cout << one.teamMoves[0].name << endl;
				cout << one.teamMoves[1].name << endl;
				cout << one.teamMoves[2].name << endl;
				cout << one.teamMoves[3].name << endl;
		*/

		heroteam = true;
	}

	//this loop selects random pokemon and moves for rival
	bool rivalteammade = false;
	int test;
	while (!rivalteammade) {


		//Pick a Pokemon and a move for team one
		cout << rival.name << " picks thier pokemon!\n\n";

		int pokeindex;

		srand(time(0));

		pokeindex = rand() % 151 + 1;

		cout << rival.name << " picked " << pokemon_db[pokeindex].name << endl << endl;
//sets rival pokemon stats

		rival.starter.index = pokemon_db[pokeindex].index;
		rival.starter.name = pokemon_db[pokeindex].name;
		rival.starter.hp = pokemon_db[pokeindex].hp;
		rival.starter.attack = pokemon_db[pokeindex].attack;
		rival.starter.defense = pokemon_db[pokeindex].defense;
		rival.starter.speed = pokemon_db[pokeindex].speed;
		rival.starter.special = pokemon_db[pokeindex].special;
		rival.starter.type1 = pokemon_db[pokeindex].type1;
		rival.starter.type2 = pokemon_db[pokeindex].type2;


		//Picks four moves for rival pokemon

		for (int i = 0 ; i < 4; i++) {
			string moveName;
			int moveIndex;

			//	for (int i = 0; i < move_db.size(); i++) {
			moveIndex = rand() % 157 + 1;
			//	if (rival.starter.type1 == move_db[moveIndex].type1 ||

			if (move_db[moveIndex].category == "Status") {
				moveIndex = 156;
			}





			cout << rival.name << " picked " <<  move_db[moveIndex].name << endl;

			Move temp;
			temp.index = move_db[moveIndex].index;
			temp.name = move_db[moveIndex].name;
			temp.type = move_db[moveIndex].type;
			temp.category = move_db[moveIndex].category;
			temp.PP = move_db[moveIndex].PP;
			temp.power = move_db[moveIndex].power;
			temp.accuracy = move_db[moveIndex].accuracy;

			rival.teamMoves.push_back(temp);
		}

		cout << rival.teamMoves[0].name << endl;
		cout << rival.teamMoves[1].name << endl;
		cout << rival.teamMoves[2].name << endl;
		cout << rival.teamMoves[3].name << endl;

		cin >> test;

		rivalteammade = true;
	}
}

int main() {
	srand(0); //Fixed seed - don't change this
	system("figlet POKEMON");
	system("figlet ++ and \\#");
	cout << "Do you want to use the Gen1 Pokémon? (Type \"NO\" for no, anything else for yes.)\n";
	string answer;
	getline(cin, answer);
	for (char &c : answer) c = toupper(c); //Uppercaseify
	string filename1, filename2;
	if (answer == "NO") {
		cout << "Please enter the two files containing the Pokémon and types for the Pokémon.\n";
		cin >> filename1 >> filename2;
		load_pokemon_db();
	} else
		load_pokemon_db();

//	Debug the load - uncomment this to see everything
//	for (Pokemon p : pokemon_db) {
//		cerr << "Pokedex Entry " << p.index << ": " << p.name << " hp: " << p.hp << " attack: " << p.attack;
//		cerr << " defense: " << p.defense << " speed: " << p.speed << " special: " << p.special;
//		cerr << " type1: " << p.type1 << " type2: " << p.type2 << endl;
//	}


	string filename3;
	if (answer == "NO") {
		cout << "Please enter the file containing the moves for your Pokémon.\n";
		cin >> filename3;
		load_move_db(filename3);
	} else
		load_move_db();


//the load uncomment this to see the results
//
//	for (Move m : move_db) {
//		if (m.index == 0) continue;
//		cerr << "Move Index " << m.index << ": " << m.name << " " << " type: " << m.type << " category: " << m.category << " PP: " << m.PP << " power: " << m.power << " accuracy: " << m.accuracy << "%\n";
//	}


	cout << "Do you want to\n1) Print Pokémon Data?\n2) Print Move Data?\n3) Pokemon Battle (1v1)\n4) Explore the World?\n";
	int choice = 0;
	cin >> choice;
	if (!cin || choice < 1 || choice > 4) die();
	if (choice == 1) {
		cout << "Please enter the Pokedex number of the Pokémon whose data you want to print:\n";
		int index = 0;
		cin >> index;
		if (!cin) die();
		//	Pokemon p = pokemon_db.at(index + 1); //Pokedex starts at 1, this only works for Gen1 Pokémon
		Pokemon p;
		for (const Pokemon &poke : pokemon_db) if (index == poke.index) p = poke;
		cout << "Pokedex Entry " << p.index << ": " << p.name << " hp: " << p.hp << " attack: " << p.attack;
		cout << " defense: " << p.defense << " speed: " << p.speed << " special: " << p.special;
		cout << " type1: " << p.type1 << " type2: " << p.type2 << endl;
	} else if (choice == 2) {
		cout << "Please enter the move number of the move whose data you want to print:\n";
		int index = 0;
		cin >> index;
		if (!cin) die();
		Move m;
		for (const Move &mo : move_db) if (index == mo.index) m = mo;
		if (m.name == "Error") cout << "No move loaded with that index.\n";
		else
			cout << "Move Index " << m.index << ": " << m.name << " " << " type: " << m.type << " category: " << m.category << " PP: " << m.PP << " power: " << m.power << " accuracy: " << m.accuracy << "%\n";
	}
	if (choice == 3) battle_mode(); //PART 2
	else explore_mode(); //PART 2
}
