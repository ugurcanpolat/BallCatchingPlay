   /* ***************** */
  /*    Ugurcan Polat  */
 /* polatu@itu.edu.tr */
/* ***************** */

#include <stdio.h> //printf(), scanf()
#include <stdlib.h> //rand() , srand()
#include <time.h> // time()

int main (void) {
	/* Define and initialize necessary numbers */
	int team1_score = 0; 
	int team2_score = 0;
	int number_players, prob_success_pass;
	int num_pass_round, target_score;
	int round_counter = 1, pass_counter = 0;
	int avoid_same_player = 0;
	int round_checker = 1;
	
	/* Get necessary numbers from user to start the game */	
	printf("$ Enter number of players per team (N)\n$ ");
	scanf("%d", &number_players);
	
	/* Check entered (N) to avoid bugs */
	/* Ask user to enter again if the entered number is buggy */
	for (; number_players < 2; ) {
		printf("\n*** You must enter at least '2' for number of");
		printf(" players per team (N). ***\n");
		printf("\n$ Enter number of players per team (N)\n$ ");
		scanf("%d", &number_players);
	} //for

	printf("$ Enter probability for a successful pass (P)\n$ ");
	scanf("%d", &prob_success_pass);
	
	/* Check entered (P) to avoid bugs */
	/* Ask user to enter again if the entered number is buggy */
	for (; prob_success_pass <= 0 || prob_success_pass > 100; ){
		printf("\n*** Probability for a successful pass (P)"); 
		printf(" must be greater than '0' and less than '101'. *** \n ");
		printf("\n$ Enter probability for a successful pass (P)\n$ ");
		scanf("%d", &prob_success_pass);
	} //for
	
	printf("$ Enter number of passes to win a single round (W)\n$ ");
	scanf("%d", &num_pass_round);
	
	/* Check entered (W) to avoid bugs */
	/* Ask user to enter again if the entered number is buggy */
	for (; num_pass_round <= 1; ){
		printf("\n*** Number of passes to win a single round (W)"); 
		printf(" must be greater than '1'. *** \n ");
		printf("\n$ Enter number of passes to win a single round (W)\n$ ");
		scanf("%d", &num_pass_round);
	} //for
	
	printf("$ Enter target score (S)\n$ ");
	scanf("%d", &target_score);
	
	/* Check entered (S) to avoid bugs */
	/* Ask user to enter again if the entered number is buggy */
	for (; target_score < 1; ){
		printf("\n*** Target score (S) must be greater than '0'. *** \n ");
		printf("\n$ Enter target score (S)\n$ ");
		scanf("%d", &target_score);
	} //for
	/* End get numbers from user. */
	
	srand(time(NULL)); //use time(NULL) to get time depended random nums
	
	/* Define and initialize integers depending random numbers. */
	/* All random selectors uses '+ 1' */
	/* because randomly generated numbers starts from 0 */
	/* which is not the case we want. */
	int team_select = (rand() % 2) + 1;	//randomly selects team 			
	int player_select = (rand() % number_players) + 1; //randomly selects player 
	
	/* Following two lines after comment; assign a random value to team */
	/* which has ball and to oppenent team */
	/* between 1 and the (P) value user entered. */
	int pass_succ_rate_selected = (rand() % prob_success_pass) + 1; 
	int pass_succ_rate_opponent = (rand() % (101 - prob_success_pass)) + 1;
	
	do { //do until a team reaches to target score (S)
		
		/* Following 'if' block; checks if it is a new round or not. */
		/* If it is a new round, selects a team randomly, */
		/* prints round number and selected team. */
		if (round_checker == 1){
			team_select = (rand() % 2) + 1;
			printf("\nRound-%d:\n", round_counter);
			if (team_select == 1)
				printf("\tTeam1 is selected\n");
			else 
				printf("\tTeam2 is selected\n");
				
			/* Reset round_checker to avoid starting a new round */
			/* before a team wins. */
			round_checker = 0; 
			
		} //if (round_checker)
		if (team_select == 1){ //If Team1 has ball
			
			/* Randomly select a player */
			/* and assign selected player to avoid_same_player */
			/* to avoid selecting same player to pass ball. */
			player_select = (rand() % number_players) + 1;	
			printf ("\tPlayer%d ", player_select);
			avoid_same_player = player_select;	
						
			/* Loop until number of successful passes reaches to */
			/* entered (W) value. */
			for (pass_counter=1; pass_counter < num_pass_round; ){
				
				/* Is the pass successful? */
				if (pass_succ_rate_selected >= pass_succ_rate_opponent){
					
					/* Increment number of successful passes. */
					pass_counter = pass_counter + 1;
					
					/* Initialize successful pass rates again */ 
					/* to be ready for new pass */
					pass_succ_rate_selected = (rand() % prob_success_pass) + 1;
					pass_succ_rate_opponent = (rand() % (101 - prob_success_pass)) + 1;
					printf("-> ");
					
					/* Is the selected player who will pass. */
					if (avoid_same_player == player_select) {
						
						/* Select another player. */
						do {
							player_select = (rand() % number_players) + 1;							
						} while (avoid_same_player == player_select);
						
						/* Print selected player. */
						printf ("Player%d ", player_select);
						avoid_same_player = player_select;	
					} //if (avoid_same_player)

					else {	
						printf ("Player%d ", player_select);
						player_select = (rand() % number_players) + 1;
						avoid_same_player = player_select;
					}
				} //if (pass_succ_rate_selected)
				
				/* If it is not a successful pass */
				else {
					team_select = 2;
					printf("\n\tTeam2 captured the ball!\n");				
					break;
				}
				/* If number of successful passes reaches to (W) */
				if (pass_counter == num_pass_round) {
					team1_score = team1_score + 1;
					round_counter = round_counter +1;
					
					/* Increment round_checker to start a new round. */
					round_checker = 1;
					printf("\n\tSuccess! New Score of Team1 is %d\n", team1_score);
					break; 
				} //if (pass_counter)
			} //for
			
		/* Assign random successful pass rates to be ready for */
		/* the first pass of the other team or new round */
		pass_succ_rate_selected = (rand() % prob_success_pass) + 1;
		pass_succ_rate_opponent = (rand() % (101 - prob_success_pass)) + 1;
		} // if(team_select)
		
		if (team_select == 2){
			
			/* Randomly select a player */
			/* and assign selected player to avoid_same_player */
			/* to avoid selecting same player to pass ball. */
			player_select = (rand() % number_players) + 1;	
			printf ("\tPlayer%d ", player_select);
			avoid_same_player = player_select;
			
			/* Loop until number of successful passes reaches to */
			/* entered (W) value. */		
			for (pass_counter=1; pass_counter < num_pass_round; ){
				/* Is the pass successful? */
				if (pass_succ_rate_selected >= pass_succ_rate_opponent){
					
					/* Increment number of successful passes. */
					pass_counter = pass_counter + 1;
					
					/* Initialize successful pass rates again */ 
					/* to be ready for new pass. */
					pass_succ_rate_selected = (rand() % prob_success_pass) + 1;
					pass_succ_rate_opponent = (rand() % (101 - prob_success_pass)) + 1;
					printf("-> ");
					
					/* Is the selected player who will pass */
					if (avoid_same_player == player_select) {
						
						/* Select another player. */
						do {
							player_select = (rand() % number_players) + 1;							
						} while (avoid_same_player == player_select);
						printf ("Player%d ", player_select);
						avoid_same_player = player_select;	
					} //if (avoid_same_player)
					
					else {	
						/* Print selected player. */
						printf ("Player%d ", player_select);
						player_select = (rand() % number_players) + 1;
						avoid_same_player = player_select;
					}
					
				} //if (pass_succ_rate_selected)
				
				/* If it is not a successful pass */
				else {
					team_select = 1;
					printf("\n\tTeam1 captured the ball!\n");
					break; 
				}
				/* If number of successful passes reaches to (W) */
				if (pass_counter == num_pass_round){
					team2_score = team2_score + 1;
					round_counter = round_counter +1;
					
					/* Increment round_checker to start a new round. */
					round_checker = 1;
					printf("\n\tSuccess! New Score of Team2 is %d\n", team2_score);				
					break;
				} //if (pass_counter)
			} // for 
			
		/* Assign random successful pass rates to be ready for */
		/* the first pass of the other team or new round */
		pass_succ_rate_selected = (rand() % prob_success_pass) + 1;
		pass_succ_rate_opponent = (rand() % (101 - prob_success_pass)) + 1;	
		} //if (team_select)
		
	} while ((team1_score != target_score) && (team2_score != target_score)); 
	
	/* Print winner. */
	if (team1_score == target_score){
		printf("\nGAME OVER: Team1 reached the target score (%d)", target_score); 
		printf(" and won the game.\n\n");
	}
	else if (team2_score == target_score) {
		printf("\nGAME OVER: Team2 reached the target score (%d)", target_score); 
		printf(" and won the game.\n\n");
	}
} //main
