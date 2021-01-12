#include<iostream>
#include<fstream>
#include<string>

int main()
{
	//register file 
	int rf[8];
	//register alias table, rat populations with a 10s place are used to indicate
	//reserve station. ex. 4 in the rat means rf4 is stored and the rat
	//may be used while 14 means that the stations is RS4
	int rat[8];
	for (int i = 0; i < 8; i++) {
		rat[i] = -1;
	}
	//reservation stations
	int rs[5][7];
	int input[50];


	//instruction queue
	int ops[10][4];

	std::fstream myfile("input.txt",std::ios_base::in);
	int a;

	//j is the master count of total lines in the input.txt
	int j = 0;

	while (myfile >> a) {
		input[j] = a;
		j = j + 1;
	}
	
	int c = 0;
	while (c < j) {
		c = c + 1;
	}

	int num_ops = input[0];

	printf("Number of opperations: %d\n", num_ops);

	int start = 0;
	//start at input index 2 for beginning of first op code
	//create arrays for the ops
	for (int q = 0; q < num_ops; q++) {
		start = q*4 + 2;

		for (int w = 0; w < 4; w++) {
			ops[q][w] = input[start];
			start = start + 1;
		}

	}

	int k = 7;
	int j2 = j-1;
	//populate the RFs
	for (int i = 0; i < 8; i++) {
		rf[k] = input[j2];
		k = k - 1;
		j2 = j2 - 1;
	}

	
	//intsruction queue and checking ops
	printf("Instruction Queue\n");
	for (int i = 0; i < num_ops; i++) {

		//check type of operation
		//o:add; 1:sub; 2:mult; 3:divide
		for (int p = 0; p < 4; p++) {
			
			if (p == 0) {
				if (ops[i][p] == 0) {
					printf("add ");
				}
				 if (ops[i][p] == 1) {
					printf("sub  ");
				}
				 if (ops[i][p] == 2) {
					printf("mul ");
				}
				 if (ops[i][p] == 3) {
					printf("div ");
				}
			}
			else {
				printf(" R%d ", ops[i][p]);
			}
		}
		printf("\n");
	}

	//set all rs busies to 0 and dispatches to 0
	//trouble with other spots being 0 they become null
	for (int y = 0; y < 5; y++) {
		for (int z = 0; z < 7; z++) {
			rs[y][0] = 0;
			rs[y][6] = 0;
			rs[y][2] = 0;
			rs[y][3] = 0;
			rs[y][4] = 0;
			rs[y][5] = 0;
			rs[y][1] = -1;

		}
	}

	//initalize counting variables
	int iq = 0; //keeps track of placement in instruction queue

	//will keep track of when dispatch takes place
	//add and sub 2CCs, mul 10 CCs, div 40 CCs
	int rs1 , rs2, rs3, rs4, rs5;
	rs1 = -1; rs2 = -1; rs3 = -1; rs4 = -1; rs5 = -1;
	//store which RAT position the op is holding up so that
	//the rat can be freed when the CCs are done
	int crs1, crs2, crs3, crs4, crs5;
	crs1 = -1; crs2 = -1; crs3 = -1; crs4 = -1; crs5 = -1;

	//counts how many things have been dispatched
	int zx = 0;

	//for manipulation in the RAT comparison
	int ratm;

	/*
	//code for comparing the RAT to the 2 inputs for the operators
	for (int i = 0; i < 2; i++) {
		for (int u = 0; u < 8; u++) {
			ratm = i + 2;
			if (rat[u] == ops[zx][ratm]) {

			}
		}
	}
	*/

	//The big code bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb
	for (int b = 0; b < input[1]; b++) {

		//for things in the queue not active
		if (zx < num_ops) {
			//checks the opcode add and sub
			if (ops[zx][0] == 0 || ops[zx][0] == 1) {
				//check for busy stations
				if (rs[0][0] == 0) {
					if (rat[ops[zx][1]] < 10) {
						crs1 = ops[zx][1];
						rat[ops[zx][2]] = 10;
					}
					
				}
				else if (rs[1][0] == 0) {
					if (rat[ops[zx][1]] < 10) {
						crs2 = ops[zx][1];
						rat[ops[zx][2]] = 11;
					}
				}
				else if (rs[2][0] == 0) {
					if (rat[ops[zx][1]] < 10) {
						crs3 = ops[zx][1];
						rat[ops[zx][1]] = 12;
					}
				}
			}
			//for mul and div
			else {
				if (rs[3][0] == 0) {
					if (rat[ops[zx][1]] < 10) {
						crs4 = ops[zx][1];
						rat[ops[zx][1]] = 13;
					}

				}
				if (rs[4][0] == 0) {
					if (rat[ops[zx][1]] < 10) {
						crs5 = ops[zx][1];
						rat[ops[zx][1]] = 14;
					}

				}

			}
		}


		//check active rs stations for the next dispatch
		//increment iq on each  commit to rat
		if (iq < num_ops) {
			for (int i = 0; i < 5; i++) {
			
				//----------------------need for loop break

				if (ops[zx][0] == 0 || ops[zx][0] == 1) {
					if (rs[0][0] == 1) {
						//checks for dispatch and if no dispatch checks to see if the RAT
						//positions are taken up
						if (rs[i][6] != 1) {
							for (int i = 0; i < 8; i++) {
								if ((rat[ops[i][3]]<10)&&(rat[ops[i][2]] < 10)&&(rs1<0)) {
									rs[i][6] = 1;
									//set that the clock needs to start counting for 
									//CCs since the RAT positions must have just been filled out
									rs1 = b + 2;
									break;
								}
							}
						}
						
					}
					else if (rs[1][0] == 1) {
						if (rs[i][6] != 1) {
							for (int i = 0; i < 8; i++) {
								if ((rat[ops[i][3]] < 10) && (rat[ops[i][2]] < 10)&&(rs2 < 0)) {
									rs[i][6] = 1;
									//set that the clock needs to start counting for 
									//CCs 
									rs2 = b + 2;
									break;
								}
							}
						}
					}
					else if (rs[2][0] == 1) {
						if (rs[i][6] != 1) {
							for (int i = 0; i < 8; i++) {
								if ((rat[ops[i][3]] < 10) && (rat[ops[i][2]] < 10) && (rs3 < 0)) {
									rs[i][6] = 1;
									//set that the clock needs to start counting for 
									//CCs 
									rs3 = b + 2;
									break;
								}
							}
						}
					}
					else { zx = zx - 1; }
				}
				if (ops[zx][0] == 2 || ops[zx][0] == 3) {
					if (rs[3][0] == 1) {
						if (rs[i][6] != 1) {
							for (int i = 0; i < 8; i++) {
								if ((rat[ops[i][3]] < 10) && (rat[ops[i][2]] < 10) && (rs4 < 0)) {
									rs[i][6] = 1;
									//set that the clock needs to start counting for 
									//CCs 
									if (ops[i][0] == 2) {
										rs4 = b + 10;
									}
									else {
										rs4 = b + 40;
									}
									break;
								}
							}
						}
					}
					else if (rs[4][0] == 1) {
						if (rs[i][6] != 1) {
							for (int i = 0; i < 8; i++) {
								if ((rat[ops[i][3]] < 10) && (rat[ops[i][2]] < 10) && (rs5 < 0)) {
									rs[i][6] = 1;
									//set that the clock needs to start counting for 
									//CCs 
									if (ops[i][0] == 2) {
										rs5 = b + 10;
									}
									else {
										rs5 = b + 40;
									}
									break;
								}
							}
						}
					}
					else { zx = zx - 1; }
				}
				

				//check to see if the reservation stations are done with 
				//the CCs and the RAT can be opened and busy set to 0
				//need to track who is taking up which rat
				rs1 = rs1 - 1;
				if (rs1 == 0) {
					rs[0][0] = 0;
					if (rs[0][1] == 0) {
						rf[crs1] = rs[0][2] + rs[0][3] + rs[0][4] + rs[0][5];
					}
					if (rs[0][1] == 1) {
						rf[crs1] = rs[0][2] - rs[0][3] + rs[0][4] - rs[0][5];
					}

				}
				rs2 = rs2 - 1;
				if (rs2 == 0) {
					rs[1][0] = 0;
					if (rs[1][1] == 0) {
						rf[crs2] = rs[1][2] + rs[1][3] + rs[1][4] + rs[1][5];
					}
					if (rs[1][1] == 1) {
						rf[crs2] = rs[1][2] - rs[1][3] + rs[1][4] - rs[1][5];
					}
				}
				rs3 = rs3 - 1;
				if (rs3 == 0) {
					rs[2][0] = 0;
					if (rs[2][1] == 0) {
						rf[crs3] = rs[2][2] + rs[2][3] + rs[2][4] + rs[2][5];
					}
					if (rs[2][1] == 1) {
						rf[crs3] = rs[2][2] - rs[2][3] + rs[2][4] - rs[2][5];
					}
				}
				rs4 = rs4 - 1;
				if (rs4 == 0) {
					rs[3][0] = 0;
					if (rs[3][1] == 2) {
						rf[crs4] = rs[3][2] * rs[3][3] * rs[3][4] * rs[3][5];
					}
					if (rs[3][1] == 1) {
						rf[crs4] = (rs[3][2] + rs[3][4]) / (rs[3][3] + rs[3][5]);
					}
				}
				rs5 = rs5 - 1;
				if (rs5 == 0) {
					rs[4][0] = 0;
					if (rs[4][1] == 2) {
						rf[crs5] = rs[4][2] * rs[4][3] * rs[4][4] * rs[4][5];
					}
					if (rs[3][1] == 1) {
						rf[crs5] = (rs[4][2] + rs[4][4]) / (rs[4][3] + rs[4][5]);
					}
				}
				
			}
		}
		//------------------for loop checking current stations

		

		
	}

	/*
	//intsruction queue checking
	for (int i = 0; i < num_ops; i++) {

		//check type of operation
		//o:add; 1:sub; 2:mult; 3:divide
		for (int p = 0; p < 4; p++) {
			if (ops[i][p] == 0) {
				
			}
			if (ops[i][p] == 1) {

			}
			if (ops[i][p] == 2) {

			}
			if (ops[i][p] == 3) {

			}
		}
	}
	*/

	//int i = 11;
	//int b = 0;
	//while (i >> b) {
	//	if (b == 0) {
	//
	//	}
	//	printf("%d", a);
	//	b = b + 1;
	//}
	
	printf("      Busy  Op  Vj  Vk  Qj  Qk  Disp\n");
	printf("RS1    %d    %d  %d  %d  %d %d    %d\n", rs[0][0], rs[0][1], rs[0][2], rs[0][3], rs[0][4], rs[0][5], rs[0][6]);
	printf("RS2    %d    %d  %d  %d  %d %d    %d\n", rs[1][0], rs[1][1], rs[1][2], rs[1][3], rs[1][4], rs[1][5], rs[1][6]);
	printf("RS3    %d    %d  %d  %d  %d %d    %d\n", rs[2][0], rs[2][1], rs[2][2], rs[2][3], rs[2][4], rs[2][5], rs[2][6]);
	printf("RS4    %d    %d  %d  %d  %d %d    %d\n", rs[3][0], rs[3][1], rs[3][2], rs[3][3], rs[3][4], rs[3][5], rs[3][6]);
	printf("RS5    %d    %d  %d  %d  %d %d    %d\n", rs[4][0], rs[4][1], rs[4][2], rs[4][3], rs[4][4], rs[4][5], rs[4][6]);

	printf("   RF   RAT\n");
	printf("0: %d   %d\n", rf[0], rat[0]);
	printf("1: %d   %d\n", rf[1], rat[1]);
	printf("2: %d   %d\n", rf[2], rat[2]);
	printf("3: %d   %d\n", rf[3], rat[3]);
	printf("4: %d   %d\n", rf[4], rat[4]);
	printf("5: %d   %d\n", rf[5], rat[5]);
	printf("6: %d   %d\n", rf[6], rat[6]);
	printf("7: %d   %d\n", rf[7], rat[7]);

	std::cout << "Type anything to exit" << std::endl;getchar();
	std::cin.get();
}