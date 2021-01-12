#include<iostream>
#include<fstream>
#include<string>

int MyCrayon(int flames) {
	int returnVal;
	if (flames == -1) {
		returnVal = 0;
	}

	else {

		returnVal = flames;
	}
	return returnVal;
}

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

	//storing rs outputs
	int output[5][2];


	//instruction queue
	int ops[10][4];

	std::fstream myfile("input.txt", std::ios_base::in);
	int a;

	//j is the master count of total lines in the input.txt
	int j = 0;

	while (myfile >> a) {
		input[j] = a;
		j = j + 1;
	}



	int num_ops = input[0];

	//printf("Number of opperations: %d\n", num_ops);

	int start = 0;
	//start at input index 2 for beginning of first op code
	//create arrays for the ops
	for (int q = 0; q < num_ops; q++) {
		start = q * 4 + 2;

		for (int w = 0; w < 4; w++) {
			ops[q][w] = input[start];
			start = start + 1;
		}

	}

	int k = 7;
	int j2 = j - 1;
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
			rs[y][2] = -1;
			rs[y][3] = -1;
			rs[y][4] = -1;
			rs[y][5] = -1;
			rs[y][1] = -1;

		}
	}

	//number of things used in the instriction queue
	int inst = 0;

	//for op check
	int check;



	int clock[5];
	for (int i = 0; i < 5; i++) {
		clock[i] = -1;
	}

	for (int j = 0; j < input[1]; j++) {



		//check that there is more in the instruction queue and handle new instructions
		//new instructions into queue
		if (inst < num_ops) {

			//set while loop to check for busy stations and intitially populate
			//vk/vj/qk/qj
			if (ops[inst][0] == 0 || ops[inst][0 == 1]) {
				if (rs[0][0] == 0) {
					rs[0][1] = ops[inst][0];
					output[0][0] = ops[inst][1];
					rs[0][0] = 1;

					//fill out vj vk qj qk values as needed
					if (rat[ops[inst][2]] > 0) {
						rs[0][4] = rat[ops[inst][2]];
					}
					else {
						rs[0][2] = rf[ops[inst][2]];
					}
					if (rat[ops[inst][3]] > 0) {
						rs[0][5] = rat[ops[inst][3]];
					}
					else {
						rs[0][3] = rf[ops[inst][3]];
					}
					//fill out vj vk qj qk
					inst++;
					goto loop;

				}
				else if (rs[1][0] == 0) {
					rs[1][1] = ops[inst][0];
					output[1][0] = ops[inst][1];
					rs[1][0] = 1;

					//fill out vj vk qj qk values as needed
					if (rat[ops[inst][2]] > 0) {
						rs[1][4] = rat[ops[inst][2]];
					}
					else {
						rs[1][2] = rf[ops[inst][2]];
					}
					if (rat[ops[inst][3]] > 0) {
						rs[1][5] = rat[ops[inst][3]];
					}
					else {
						rs[1][3] = rf[ops[inst][3]];
					}
					//fill out vj vk qj qk
					inst++;
					goto loop;
				}
				else if (rs[2][0] == 0) {
					rs[2][1] = ops[inst][0];
					output[2][0] = ops[inst][1];
					rs[2][0] = 1;

					//fill out vj vk qj qk values as needed
					if (rat[ops[inst][2]] > 0) {
						rs[2][4] = rat[ops[inst][2]];
					}
					else {
						rs[2][2] = rf[ops[inst][2]];
					}
					if (rat[ops[inst][3]] > 0) {
						rs[2][5] = rat[ops[inst][3]];
					}
					else {
						rs[2][3] = rf[ops[inst][3]];
					}
					//fill out vj vk qj qk

					inst++;
					goto loop;

				}
			}
			if (ops[inst][0] == 2 || ops[inst][0] == 3) {
				if (rs[3][0] == 0) {
					rs[3][1] = ops[inst][0];
					output[3][0] = ops[inst][1];
					rs[3][0] = 1;

					//fill out vj vk qj qk values as needed
					if (rat[ops[inst][2]] > 0) {
						rs[3][4] = rat[ops[inst][2]];
					}
					else {
						rs[3][2] = rf[ops[inst][2]];
					}
					if (rat[ops[inst][3]] > 0) {
						rs[3][5] = rat[ops[inst][3]];
					}
					else {
						rs[3][3] = rf[ops[inst][3]];
					}
					//fill out vj vk qj qk
					inst++;
					goto loop;

				}
				else if (rs[4][0] == 0) {
					rs[4][1] = ops[inst][0];
					output[4][0] = ops[inst][1];
					rs[4][0] = 1;

					//fill out vj vk qj qk values as needed
					if (rat[ops[inst][2]] > 0) {
						rs[4][4] = rat[ops[inst][2]];
					}
					else {
						rs[4][2] = rf[ops[inst][2]];
					}
					if (rat[ops[inst][3]] > 0) {
						rs[4][5] = rat[ops[inst][3]];
					}
					else {
						rs[4][3] = rf[ops[inst][3]];
					}
					//fill out vj vk qj qk
					inst++;
					goto loop;


				}
			}

		}
		//new instructions into queue
		//for handling new instructions


		//check for dispatch
		//if rat is open for the input then use it
		//if rat is open for the output good to go

	loop:
		int qj = 0;
		int qk = 0;
		//check for dispatch


		for (int i = 0; i < 5; i++) {
			int inputholder[2][2];
			//Rat value
			//Rat value
			if ((rs[i][0] == 1) && (rs[i][6] != 1)) {
				//qj
				if (rs[i][4] != -1) {
					inputholder[0][0] = 1;
					inputholder[0][1] = rs[i][4];
				}
				//qk
				if (rs[i][5] != -1) {
					inputholder[1][0] = 1;
					inputholder[1][1] = rs[i][5];
				}
				//vj
				if (rs[i][2] != -1) {
					inputholder[0][0] = 0;
					inputholder[0][1] = rs[i][2];
				}
				//vk
				if (rs[i][3] != -1) {
					inputholder[1][0] = 0;
					inputholder[1][1] = rs[i][3];
				}

				if (((inputholder[0][0] == 0) || (rat[inputholder[0][1]] != -1)) && ((inputholder[1][0] == 0) || (rat[inputholder[1][1]] != -1))) {
					rs[i][6] = 1;
					//taking up rat space for output
					rat[output[i][0]] = i;

					int j = 0;
					int k = 0;
					if (inputholder[0][0] == 0) {
						j = inputholder[0][1];
					}
					else {
						j = rf[inputholder[0][1]];
					}
					if (inputholder[1][0] == 0) {
						k = inputholder[1][1];
					}
					else {
						k = rf[inputholder[1][1]];
					}

					//opcode checking for maths
					if (rs[i][1] == 0) {
						output[i][1] = j + k;
						clock[i] = 2;
					}
					else if (rs[i][1] == 1) {
						output[i][1] = j - k;
						clock[i] = 2;
					}
					else if (rs[i][1] == 2) {
						output[i][1] = j * k;
						clock[i] = 10;
					}
					else if (rs[i][1] == 3) {
						output[i][1] = j / k;
						clock[i] = 40;
					}


				}

			}



		}

		//check for dispatch


		for (int i = 0; i < 5; i++) {
			if (clock[i] == 0) {
				rs[i][0] = 00;
				//rs[i][6] = 1;
				rf[output[i][0]] = output[i][1];
				rat[output[i][0]] = -1;
			}
			clock[i] = clock[i] - 1;
			//	printf("clock %d is %d\n", i, clock[i]);
		}





	}






	//rs[i][2] >-1 or rat[rs[i][4]] !=0


	int display[4][7];
	for (int pineapple = 0; pineapple < 5; pineapple++) {

		display[pineapple][0] = rs[pineapple][0];
		display[pineapple][1] = rs[pineapple][1];
		display[pineapple][2] = rs[pineapple][2];
		display[pineapple][3] = rs[pineapple][3];
		display[pineapple][4] = rs[pineapple][4];
		display[pineapple][5] = rs[pineapple][5];
		display[pineapple][6] = rs[pineapple][6];

		for (int tires = 0; tires < 1; tires++) {
			if (display[pineapple][tires] == -1) {
				display[pineapple][tires] = 0;
			}
		}
		for (int tires = 2; tires < 8; tires++) {
			if (display[pineapple][tires] == -1) {
				display[pineapple][tires] = 0;
			}
		}
	}




	printf("      Busy   Op       Vj   Vk   Qj     Qk     Disp\n");

	printf("RS1  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d\n", display[0][0], display[0][1], display[0][2], display[0][3], display[0][4], display[0][5], display[0][6]);
	printf("RS2  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d\n", display[1][0], display[1][1], display[1][2], display[1][3], display[1][4], display[1][5], display[1][6]);
	printf("RS3  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d\n", display[2][0], display[2][1], display[2][2], display[2][3], display[2][4], display[2][5], display[2][6]);
	printf("RS4  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d\n", display[3][0], display[3][1], display[3][2], display[3][3], display[3][4], display[3][5], display[3][6]);
	printf("RS5  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d  |  %d\n", display[4][0], display[4][1], display[4][2], display[4][3], display[4][4], display[4][5], display[4][6]);
	printf("\n");


	printf("   RF   RAT\n");

	for (int matthew = 0; matthew < 8; matthew++) {
		if (MyCrayon(rat[matthew]) == 0) {
			printf("%d: %d   %d\n", matthew, rf[matthew], MyCrayon(rat[matthew]));
		}
		else {
			printf("%d: %d   RS%d\n", matthew, rf[matthew], MyCrayon(rat[matthew]));
		}
	}
	/*
	printf("0: %d   %d\n", rf[0], MyCrayon(rat[0]));
	printf("1: %d   %d\n", rf[1], MyCrayon(rat[1]));
	printf("2: %d   %d\n", rf[2], MyCrayon(rat[2]));
	printf("3: %d   %d\n", rf[3], MyCrayon(rat[3]));
	printf("4: %d   %d\n", rf[4], MyCrayon(rat[4]));
	printf("5: %d   %d\n", rf[5], MyCrayon(rat[5]));
	printf("6: %d   %d\n", rf[6], MyCrayon(rat[6]));
	printf("7: %d   %d\n", rf[7], MyCrayon(rat[7]));
	*/


	std::cout << "Type anything to exit" << std::endl; getchar();
	std::cin.get();
}


