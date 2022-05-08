// FeasabilityDemo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <fstream> 
#include <time.h>
#include <iostream>
#include <string>
using namespace std;

struct coordinate {//struct used for fitness function
	int x;
	int y;
	bool checked = false;
};

int fitness(int map[20][20]) {
	//std::cout << "fitness test " << std::endl;

	int directions[4][2]{ -1, 0,
							  1, 0,
							  0, -1,
							  0, 1 }; //directions for moving 




	int distance = 1;
	int distancelooped = 0;
	bool foundtarget = false;
	bool nextsteppossible = true;

	int ends = 0;
	int rooms = 0;

	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			if (map[i][j] == -3)
				ends++;
		}
	}
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			if (map[i][j] == -5)
				rooms++;
		}
	}
	if (ends > 1) {
	//	std::cout << "fail, too many ends " << ends << std::endl;
		return 0;
	}
	if (rooms < 2) {
		//std::cout << "fail, not enough rooms" << std::endl;

		return 0;
	}

	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {

			if (map[i][j] == -2) {
				map[i][j] = distance; // find and mark start point
			}
		}
	}
	while (foundtarget == false) { //until target found
		for (int i = 0; i < 20; i++) {
			for (int j = 0; j < 20; j++) {//check every coordinate

				if (map[i][j] == distance) { //find where the path has reached
					for (int h = 0; h < 4; h++) {  //check coords around newest point
						if (map[i + directions[h][0]][j + directions[h][1]] == -3) { //if target found stop
							foundtarget = true;
							return distance;

						}
						else if (map[i + directions[h][0]][j + directions[h][1]] == -1) {//if the coord is in a tuneel mark it for the next loop
							map[i + directions[h][0]][j + directions[h][1]] = distance + 1;

						}

						else if (map[i + directions[h][0]][j + directions[h][1]] == -4) {//if the coord is in a tuneel mark it for the next loop
							map[i + directions[h][0]][j + directions[h][1]] = distance + 1;

						}
						else if (map[i + directions[h][0]][j + directions[h][1]] == -5) {//if the coord is in a tuneel mark it for the next loop
							map[i + directions[h][0]][j + directions[h][1]] = distance + 1;

						}


					}
				}

			}



		}

		
		distance++;//increase distance to check next section of the path
		nextsteppossible = false;
		for (int i = 0; i < 20; i++) {
			for (int j = 0; j < 20; j++) {
				if (map[i][j] == distance) {
					nextsteppossible = true;
				}

			}
		}
		if (nextsteppossible == false) {
			/*std::cout << " new map " << std::endl;
			for (int i = 0; i < 20; i++) {
				for (int j = 0; j < 20; j++) {
					std::cout << " " << map[i][j];
				}
				std::cout << std::endl;
			}*/
			return 0;
		}
	}
	//std::cout << " new map " << std::endl;
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			std::cout << " " << map[i][j];
		}
		std::cout << std::endl;
	}
	return distance;

}

void geneicAlgorithm(int map[20][20][20]) {
	std::cout << "genetic  algorithm" << std::endl;
	string filename = "maps";
	

	int fitnessscores[20]; // array for fitness score
	bool converged = false; //bool for tracking convergence
	int parents[2]; //parent values
	int parentval;
	int weakest;
	int weakestpos; //weakest values
	int mutatonresult;
	int parentval2;
	int offspring[20][20]; //array for tracking offspring maps
	int x;
	int y;
	bool mutation = false; //bool to control mutation
	int mutationchance = 0;
	int randnum = 0;

	while (converged == false) { //until population congerges keep evolving
		//std::cout << "still looping genetic" << std::endl;

		for (int i = 0; i < 20; i++) {
			fitnessscores[i] = fitness(map[i]);//get fitness sores of starting maps

		}

		for (int h = 0; h < 20; h++) {

			filename = "test genetic map" + std::to_string(h) + ".ppm";//set up for exporting maps to image
			ofstream img(filename);
			img << "P3" << endl;
			img << 20 << " " << 20 << endl;
			img << "255" << endl;

			for (int i = 0; i < 20; i++) {

				for (int j = 0; j < 20; j++) {
					//std::cout << map[i][j];
					if (map[h][i][j] == -1) { //output an image marking the start, end and tunnels with appropriate colours

						img << 0 << " " << 250 << " " << 5 << endl;

					}
					else  if (map[h][i][j] == 0) {
						img << 200 << " " << 5 << " " << 50 << endl;


					}
					else  if (map[h][i][j] == -2) {
						img << 100 << " " << 5 << " " << 200 << endl;


					}
					else  if (map[h][i][j] == -3) {
						img << 120 << " " << 5 << " " << 125 << endl;


					}
				}

			}
		}
		parentval = fitnessscores[0];
		parentval2 = fitnessscores[0];
		weakest = fitnessscores[0];
		weakestpos = 0;
		parents[0] = 0;
		parents[1] = 0;
		if (map[0] == map[1] && map[0] == map[2] && map[0] == map[3] && map[0] == map[4] && map[0] == map[5] && map[0] == map[6] && map[0] == map[7] && map[0] == map[8] && map[0] == map[9] && map[0] == map[10] && map[0] == map[11] && map[0] == map[12] && map[0] == map[13] && map[0] == map[14] && map[0] == map[15] && map[0] == map[16] && map[0] == map[17] && map[0] == map[18] && map[0] == map[19]) { //check convergence
			converged = true;
		}
		for (int i = 0; i < 20; i++) {
			if (fitnessscores[i] > parentval) {
				parentval = fitnessscores[i]; //find best fitness value
				parents[0] = i;

			}
		}
		//cout << "best val " << fitnessscores[parents[0]] << endl;
		for (int i = 0; i < 20; i++) {
			if (fitnessscores[i] >= parentval2 && i != parents[0]) {
				parentval2 = fitnessscores[i];
				parents[1] = i; // find second best fitness value
			}
		}
		//cout << "breeding " << parents[0] << " with " << parents[1] << endl;
		for (int i = 0; i < 20; i++) {
			for (int j = 0; j < 20; j++) {
				offspring[i][j] = map[parents[0]][i][j]; //put best parent value into offspring array
			}
		}
		//for (int i = 0; i < 5; i++) {
			x = rand() % 19;
			y = rand() %19;
			offspring[x][y] = map[parents[1]][x][y]; //select random pointd from second parent and combine with the first parent


		//}
		for (int i = 0; i < 20; i++) {
			if (fitnessscores[i] < weakest) {
				weakest = fitnessscores[i]; //find the weakest fitness score
				weakestpos = i;
			}
		}
	//cout << "weakest value was " << weakestpos << "With a value of " << weakest << endl;

		for (int i = 0; i < 20; i++) {
			for (int j = 0; j < 20; j++) {
				map[weakestpos][i][j] = offspring[i][j];//replace weakest map with offspring of both parents 
			}
		}


		randnum = x = rand() % 5 + 1;  //if the random number is smaller than the mutation chance then mutate the data
		if (randnum <= mutationchance) {
			//std::cout << "mutation " << std::endl;
			mutationchance = 0; //reset mutation chance
			for (int i = 0; i < 5; i++) {

				randnum = x = rand() % 19;
				mutatonresult = rand() % 4;
				if (mutatonresult == 0) {
					map[randnum][rand() % 19 + 1][rand() % 19 + 1] = -1; //randomly change data
				}
				if (mutatonresult == 1) {
					for (int i = 0; i < 20; i++) {
						for (int j = 0; j < 20; j++) {
							if (map[randnum][i][j] == -2) {
								map[randnum][i][j] = -1;
							}
						}
					}
					map[randnum][rand() % 19 + 1][rand() % 19 + 1] = -2; //randomly change data

				}
				if (mutatonresult == 2) {
					for (int i = 0; i < 20; i++) {
						for (int j = 0; j < 20; j++) {
							if (map[randnum][i][j] == -3) {
								map[randnum][i][j] = -1;
							}
						}
					}
					map[randnum][rand() % 19 + 1][rand() % 19 + 1] = -3; //randomly change data
				}
				if (mutatonresult == 3) {
					map[randnum][rand() % 19 + 1][rand() % 19 + 1] = 0; //randomly change data

				}

			}



			

		}
		mutationchance++; //increase mutation chance over time
		

	}
	 filename = "Genetic map.pmm";

	ofstream img(filename);
	img << "P3" << endl;
	img << 20 << " " << 20 << endl;
	img << "255" << endl;


	// writing pixel data
	
		for (int i = 0; i < 20; i++) {

			for (int j = 0; j < 20; j++) {
				//std::cout << map[i][j];
				if (map[0][i][j] == -1) { //output an image marking the start, end and tunnels with appropriate colours

					img << 0 << " " << 250 << " " << 5 << endl;

				}
				else  if (map[0][i][j] == 0) {
					img << 200 << " " << 5 << " " << 50 << endl;


				}
				else  if (map[0][i][j] == -2) {
					img << 100 << " " << 5 << " " << 200 << endl;


				}
				else  if (map[0][i][j] == -3) {
					img << 120 << " " << 5 << " " << 125 << endl;


				}
			}
		
	}
	
	
	std::cout << "genetic  algorithm finished" << std::endl;

}

int branchrooms(int map[10][20][20]) {

	int currentdir[2];
	currentdir[0] = 0;
	currentdir[1] = 0;

	int roompos[2];
	roompos[0] = 0;
	roompos[0] = 0;

	bool spacecheck = true;

	for (int h = 0; h < 10; h++) {
		//check each map

		for (int i = 0; i < 20; i++) {
			for (int j = 0; j < 20; j++) {
				//find rooms
				if (map[h][i][j] == -5 || map[h][i][j] == -2) {

					//check all directios
					if (map[h][i + 4][j] == 0) {

						currentdir[0] = 1;
						currentdir[1] = 0;
						roompos[0] = i + currentdir[0] * 5;
						roompos[1] = j + currentdir[1] * 5;
						if (roompos[0] - 2 >= 0 && roompos[0] - 2 <= 19 && roompos[1] - 2 >= 0 && roompos[1] + 2 <= 19) {//check room wont go over edge

							for (int k = 1; k < 4; k++) {
								for (int l = 1; l < 4; l++) {
									if (map[h][roompos[0] + k][roompos[1] + l] == -4) {
										spacecheck = false;
									}
									if (map[h][roompos[0] + k][roompos[1] - l] == -4) {
										spacecheck = false;

									}
									if (map[h][roompos[0] + k][roompos[1]] == -4) {
										spacecheck = false;

									}
									if (map[h][roompos[0] - k][roompos[1] + l] == -4) {
										spacecheck = false;

									}
									if (map[h][roompos[0] - k][roompos[1] - l] == -4) {
										spacecheck = false;

									}
									if (map[h][roompos[0] - k][roompos[1]] == -4) {
										spacecheck = false;

									}
									if (map[h][roompos[0]][roompos[1] + k] == -4) {
										spacecheck = false;

									}
									if (map[h][roompos[0]][roompos[1] - k] == -4) {
										spacecheck = false;

									}

								}

							

							}
							if (spacecheck == true) {
								map[h][roompos[0] - currentdir[0] * 3][roompos[1] - currentdir[0] * 4] = -1;

							}



						}if (map[h][i - 4][j] == 0) {
							currentdir[0] = -1;
							currentdir[1] = 0;


						}if (map[h][i][j + 4] == 0) {
							currentdir[0] = 0;
							currentdir[1] = 1;


						}if (map[h][i][j - 4] == 0) {
							currentdir[0] = 0;
							currentdir[1] = -1;

						}

						//check for space


				// Add room


					}



				}
			}
		}
		return 0;
	}
}





int main()
{
	srand(time(NULL));//set up for random numbers
	int map[20][20][20] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,//initialised map grid
					0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	};
	int maxtunnels =5 ;//variables for controlling map generation
	int maxlength = 7;
	int tunnellength;
	int randlength;
	int directions[4][2]{ -1, 0,// 2d array used to move through grid
							  1, 0,
							  0, -1,
							  0, 1 };

	directions[3][1] = 0;

	int stuckdirections;
	int currentx;
	int currenty;//variables for current position in map
	int lastDirection[2]{ 0,0 };// tracks last direction traveled
	int randomDirection[2];// used to select new direction 
	int firstdirection;
	bool spacecheck = false;
	string filename;

	int stuckcount = 0;
	bool badtunnel = false;

	int newmap[20][20];
	
	int goodmaps = 0;

	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			newmap[i][j] = 0;
		}
	}

	int fitnessmap[20][20];
	stuckdirections = 0;
	

   while (goodmaps < 10){

	//for (int h = 0; h < 20; h++) {

		for (int i = 0; i < 20; i++) {
			for (int j = 0; j < 20; j++) {
				newmap[i][j] = 0;
			}
		}

		maxtunnels = 5;//reset max tunnels 
		stuckcount = 0;

		 currentx = rand() % 13 + 3;//choose random start position
		 currenty = rand() % 13 + 3;
		 //cout << "start x " << currentx << endl;
		 //cout << "start y " << currenty << endl;

		 newmap[currentx][currenty] = -2;// mark start position

		for (int i = 1; i < 3; i++) {
			for (int j = 1; j < 3; j++) {
				newmap[currentx + i][currenty + j] = -4;
				newmap[currentx + i][currenty - j] = -4;
				newmap[currentx + i][currenty] = -4;
				newmap[currentx - i][currenty + j] = -4;
				newmap[currentx - i][currenty - j] = -4;
				newmap[currentx - i][currenty] = -4;
				newmap[currentx][currenty + i] = -4;
				newmap[currentx][currenty - i] = -4;


			}
		}

		 firstdirection = rand() % 3 + 0; //choose a random diresction
		randomDirection[0] = directions[firstdirection][0];
		randomDirection[1] = directions[firstdirection][1];
		currentx += randomDirection[0] * 4;
		currenty += randomDirection[1] * 4;
		newmap[currentx - randomDirection[0]][currenty - randomDirection[1]] = -1;
		newmap[currentx ][currenty] = -1;


		while (maxtunnels > 0) { // wander until max amount of tunnels has been generated 
			
			spacecheck = true;
			for (int i = 1; i < 4; i++) {
				for (int j = 1; j < 4; j++) {
					if (newmap[currentx + i][currenty + j] == -4) {
						spacecheck = false;
					}
					if (newmap[currentx + i][currenty - j] == -4) {
						spacecheck = false;

					}
					if (newmap[currentx + i][currenty] == -4) {
						spacecheck = false;

					}
					if (newmap[currentx - i][currenty + j] == -4) {
						spacecheck = false;

					}
					if (newmap[currentx - i][currenty - j] == -4) {
						spacecheck = false;

					}
					if (newmap[currentx - i][currenty] == -4) {
						spacecheck = false;

					}
					if (newmap[currentx][currenty + i] == -4) {
						spacecheck = false;

					}
					if (newmap[currentx][currenty - i] == -4) {
						spacecheck = false;

					}
					if (currentx > 17 || currentx < 4 || currenty > 17 || currenty < 4) {
						spacecheck = false;


					}


				}
			}
			if (spacecheck == true) {
				newmap[currentx][currenty] = -5;
				for (int i = 1; i < 3; i++) {
					for (int j = 1; j < 3; j++) {
						newmap[currentx + i][currenty + j] = -4;
						newmap[currentx + i][currenty - j] = -4;
						newmap[currentx + i][currenty] = -4;
						newmap[currentx - i][currenty + j] = -4;
						newmap[currentx - i][currenty - j] = -4;
						newmap[currentx - i][currenty] = -4;
						newmap[currentx][currenty + i] = -4;
						newmap[currentx][currenty - i] = -4;


					}
				}
			}




			if (newmap[currentx][currenty] == -5) {
				while ((randomDirection[0] == -lastDirection[0] && randomDirection[1] == -lastDirection[1]) || (randomDirection[0] == lastDirection[0] && randomDirection[1] == lastDirection[1])) { //loop until i new direction that isnt backwards is chosen

					firstdirection = rand() % 3 + 0; //pick random direction
					randomDirection[0] = directions[firstdirection][0];
					randomDirection[1] = directions[firstdirection][1];

					if (currentx >= 16 && randomDirection == directions[1]) { //if near the right side and going that way try again
						randomDirection[0] = lastDirection[0];
						randomDirection[1] = lastDirection[1];

					}	if (currentx <= 3 && randomDirection == directions[0]) { //if near the left side and going that way try again
						randomDirection[0] = lastDirection[0];
						randomDirection[1] = lastDirection[1];

					}
					if (currenty <= 3 && randomDirection == directions[3]) { //if near the left side and going that way try again
						randomDirection[0] = lastDirection[0];
						randomDirection[1] = lastDirection[1];

					}
					if (currenty >= 16 && randomDirection == directions[2]) { //if near the left side and going that way try again
						randomDirection[0] = lastDirection[0];
						randomDirection[1] = lastDirection[1];

					}
					//cout << "room direction" << endl;
				}
			}
			else {
				while ((randomDirection[0] == -lastDirection[0] && randomDirection[1] == -lastDirection[1]) || (randomDirection[0] == lastDirection[0] && randomDirection[1] == lastDirection[1])) { //loop until i new direction that isnt backwards is chosen
					//cout << "hall direction" << endl;

					if (currentx == 1 && currenty == 1 && lastDirection[0] == 0 && lastDirection[1] == -1) { //if in top left corner and going up go right

						randomDirection[0] = directions[1][0];
						randomDirection[1] = directions[1][1];
						break;
					}
					else if (currentx == 1 && currenty == 1 && lastDirection[0] == -1 && lastDirection[1] == 0) { //if in top left and going left go down

						randomDirection[0] = directions[3][0];
						randomDirection[1] = directions[3][1];
						break;
					}
					if (currentx == 1 && currenty == 18 && lastDirection[0] == 0 && lastDirection[1] == 1) { //if in bottom left and going down go right

						randomDirection[0] = directions[1][0];
						randomDirection[1] = directions[1][1];
						break;
					}
					else if (currentx == 1 && currenty == 18 && lastDirection[0] == -1 && lastDirection[1] == 0) {//if in bottom left and going left go up

						randomDirection[0] = directions[2][0];
						randomDirection[1] = directions[2][1];
						break;
					}if (currentx == 18 && currenty == 1 && lastDirection[0] == 1 && lastDirection[1] == 0) { //if in top right  and going right go down

						randomDirection[0] = directions[3][0];
						randomDirection[1] = directions[3][1];
						break;
					}
					else if (currentx == 18 && currenty == 1 && lastDirection[0] == 0 && lastDirection[1] == -1) { // if in top right and going up go left

						randomDirection[0] = directions[0][0];
						randomDirection[1] = directions[0][1];
						break;
					}if (currentx == 18 && currenty == 18 && lastDirection[0] == 1 && lastDirection[1] == 0) {//if in bottom right  and going down turn left

						randomDirection[0] = directions[2][0];
						randomDirection[1] = directions[2][1];
						break;
					}
					else if (currentx == 18 && currenty == 18 && lastDirection[0] == 0 && lastDirection[1] == 1) { // if in bottom right and going rght turn up

						randomDirection[0] = directions[1][0];
						randomDirection[1] = directions[1][1];
						break;
					}
					if (currentx == 1 && (lastDirection[0] == 0 && lastDirection[1] == -1 || lastDirection[0] == 0 && lastDirection[1] == 1)) { //if at left side and going up or down then turn right

						randomDirection[0] = directions[1][0];
						randomDirection[1] = directions[1][1];
						break;
					}
					if (currenty == 1 && (lastDirection[0] == -1 && lastDirection[1] == 0 || lastDirection[0] == 1 && lastDirection[1] == 0)) { //if at top side and going left or right then turn down

						randomDirection[0] = directions[3][0];
						randomDirection[1] = directions[3][1];
						break;
					}
					if (currentx == 18 && (lastDirection[0] == 0 && lastDirection[1] == -1 || lastDirection[0] == 0 && lastDirection[1] == 1)) { //if at right side and going up or down then turn left

						randomDirection[0] = directions[2][0];
						randomDirection[1] = directions[2][1];
						break;
					}
					if (currenty == 18 && (lastDirection[0] == -1 && lastDirection[1] == 0 || lastDirection[0] == 1 && lastDirection[1] == 0)) { //if at bottom side and going left or right then turn up

						randomDirection[0] = directions[1][0];
						randomDirection[1] = directions[1][1];
						break;
					}

					firstdirection = rand() % 3 + 0; //pick random direction
					randomDirection[0] = directions[firstdirection][0];
					randomDirection[1] = directions[firstdirection][1];
					stuckdirections++;

					if (stuckdirections < 10) {
						stuckdirections = 0;
						stuckcount = 20;
						break;
					}
				}
			}
			if (newmap[currentx][currenty] == -5) {

				currentx += randomDirection[0] * 3;
				currenty += randomDirection[1] * 3;

			}
			maxlength = 7;

			randlength = rand() % maxlength + 1; //pick a random length for current tunnel
			tunnellength = 0;

			badtunnel = false;

			for (int i = 1; i <= randlength + 2; i++) {

				if (newmap[currentx + i * randomDirection[0]] [currenty + i * randomDirection[1]] == -4 || newmap[currentx + i * randomDirection[0]][currenty + i * randomDirection[1]]  == -1) {
					//0 1 x 2 3 y
					

					badtunnel = true;
				}if (randomDirection == directions[0] || randomDirection == directions[1]) {
					if (newmap[currentx + i * randomDirection[0]][currenty + i * randomDirection[1] + 1] == -4 || newmap[currentx + i * randomDirection[0]][currenty + i * randomDirection[1] + 1] == -1 || newmap[currentx + i * randomDirection[0]][currenty + i * randomDirection[1] - 1] == -4 || newmap[currentx + i * randomDirection[0]][currenty + i * randomDirection[1] - 1] == -1) {
						badtunnel = true;
					}
				}
				if (randomDirection == directions[2] || randomDirection == directions[3]) {
					if (newmap[currentx + i * randomDirection[0] + 1][currenty + i * randomDirection[1]] == -4 || newmap[currentx + i * randomDirection[0] + 1][currenty + i * randomDirection[1]] == -1 || newmap[currentx + i * randomDirection[0] - 1][currenty + i * randomDirection[1]] == -4 || newmap[currentx + i * randomDirection[0] - 1][currenty + i * randomDirection[1]] == -1) {
						badtunnel = true;
					}
				}
			}
				
			

			if (badtunnel == true) {
				lastDirection[0] = randomDirection[0];
				lastDirection[1] = randomDirection[1];
				stuckcount++;
			}
			if (stuckcount >= 20) {
				maxtunnels = 0;
			}

			if (badtunnel == false) {
				while (tunnellength <= randlength) { //check ourr current tunnel has a lenght
					if (((currentx == 1) && (randomDirection[0] == -1)) ||
						((currenty == 1) && (randomDirection[1] == -1)) ||
						((currentx == 18) && (randomDirection[0] == 1)) ||
						((currenty == 18)) && (randomDirection[1] == 1))

					{
						lastDirection[0] = randomDirection[0];
						lastDirection[1] = randomDirection[1];
						break; //if  weve hit an edge break to chose a new direction
					}


					else {
						if (newmap[currentx][currenty] != -2 || newmap[currentx][currenty] != -4) {
							newmap[currentx][currenty] = -1; //mark new map location
							currentx += randomDirection[0];
							currenty += randomDirection[1];// move to next position
							tunnellength++;
							stuckcount = 0;
						}
					


					}


				}
			}
		
			
			if (tunnellength > 0) {
				lastDirection[0] = randomDirection[0];
				lastDirection[1] = randomDirection[1];


				maxtunnels--; //countdown max tunnels

			}

		}
		newmap[currentx][currenty] = -3;// mark end position

	//	std::cout << " new map " << std::endl;
	/*	for (int i = 0; i < 20; i++) {
			for (int j = 0; j < 20; j++) {
				std::cout << " " << newmap[i][j] << ",";
			}
			std::cout << std::endl;

		}*/
		for (int i = 0; i < 20; i++) {
			for (int j = 0; j < 20; j++) {
				fitnessmap[i][j] = newmap[i][j];
			}
		}

		if (fitness(fitnessmap) != 0) {

			for (int i = 0; i < 20; i++) {

				for (int j = 0; j < 20; j++) {

					map[goodmaps][i][j] = newmap[i][j];
				}
			}
			goodmaps += 1;
			cout << "goodmaps " << goodmaps << endl;
		}
		
	}
	   branchrooms(map);
   
	std::cout << "generation finished" << std::endl;

	for (int h = 1; h < 20; h++) {
		cout << "map " << h << endl;
		filename = "maps";
		filename = " map" + std::to_string(h) + ".ppm";//set up for exporting maps to image
		ofstream img(filename);
		img << "P3" << endl;
		img << 20 << " " << 20 << endl;
		img << "255" << endl;

		for (int i = 0; i < 20; i++) {

			for (int j = 0; j < 20; j++) {
				if (map[h][i][j] == -1) { //output an image marking the start, end and tunnels with appropriate colours

					img << 0 << " " << 250 << " " << 5 << endl;//hallway

				}
				else  if (map[h][i][j] == 0) {
					img << 200 << " " << 5 << " " << 50 << endl;//no go


				}
				else  if (map[h][i][j] == -2) {
					img << 100 << " " << 5 << " " << 200 << endl;//start


				}
				else  if (map[h][i][j] == -3) {
					img << 120 << " " << 5 << " " << 125 << endl;//end


				}
				else  if (map[h][i][j] == -4) {
					img << 0 << " " << 5 << " " << 0 << endl;//end


				}
				else  if (map[h][i][j] == -5) {
					img << 20 << " " << 20 << " " << 0 << endl;//end


				}
			}

		}
	}

	//geneicAlgorithm(map);
}


///spacecheck = true;

