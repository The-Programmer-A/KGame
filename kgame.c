/**
 * NWEN 241 Programming Assignment 3
 * kgame.c C Source File
 *
 * Name:
 * Student ID:
 * 
 * IMPORTANT: Implement the functions specified in kgame.h here. 
 * You are free to implement additional functions that are not specified in kgame.h here.
 */

#include <stdlib.h>
#include "kgame.h"
#include <stdio.h>


void kgame_init(kgame_t *game)
{
    if(!game) return;
    
    for(int i=0; i<KGAME_SIDES; i++) 
        for(int j=0; j<KGAME_SIDES; j++)
            game->board[i][j] = ' ';
    game->score = 0;
}

void kgame_add_random_tile(kgame_t *game)
{
	int row, col; //field
	
	if(!game) return;

	// find random, but empty tile
	// FIXME: will go to infinite loop if no empty tile
    
    //go thorugh the 2D array adding a count if the count = gridsize*gridsize then exit program 
    int count = 0;
    
    for(int i = 0; i < KGAME_SIDES; i++){
        for(int j = 0; j < KGAME_SIDES; j++){
            if(game->board[i][j] != ' '){
                count++;
            }
        }
    }
    
    if(count == (KGAME_SIDES*KGAME_SIDES)){
        return;
    }
    
	do {
		row = rand() % 4; // randomly choose a row from the grid
		col = rand() % 4; // randomly choose a col from the grid
	} while(game->board[row][col] != ' '); //if that pos was occupied re select randoms

	// place to the random position 'A' or 'B' tile
	game->board[row][col] = 'A' + (rand() % 2); //populate the game board with a A or B
}


void kgame_render(char *output_buffer, const kgame_t *game)
{
    // FIXME: Implement correctly (task 1)
    //use sprintf() to output to the output buffer rather than the screan
    //*game allows use to get the board and the score of the game state
    
    output_buffer += sprintf(output_buffer, "Score:%d", game->score); // trying to print out the score
    output_buffer += sprintf(output_buffer, "\n"); //formatting
        
    kgame_add_random_tile((kgame_t *) game);
    
    for(int i = 0; i < KGAME_SIDES; i++){
    output_buffer += sprintf(output_buffer, "+---"); //creating the top
	}
	output_buffer += sprintf(output_buffer, "+"); //formattin
	output_buffer += sprintf(output_buffer, "\n"); //formatting
	
	for(int i = 0; i < KGAME_SIDES; i++){ //creating the middle
		for(int j = 0; j < KGAME_SIDES; j++){
            char c = game ->board[i][j]; //allowing to enter a tile
			output_buffer += sprintf(output_buffer, "|  ");
            output_buffer += sprintf(output_buffer, "%c", c);
		}
		output_buffer += sprintf(output_buffer, "|");
		output_buffer += sprintf(output_buffer, "\n");
		
		for(int b = 0; b < KGAME_SIDES; b++){
            output_buffer += sprintf(output_buffer, "+---");
        }
        output_buffer += sprintf(output_buffer, "+"); //formattin
        output_buffer += sprintf(output_buffer, "\n"); //formatting
	}
	
	
}


bool kgame_is_won(const kgame_t *game)
{
    // FIXME: Implement correctly (task 2)
    //return false;
    
    for(int i = 0; i < KGAME_SIDES; i++){
        for(int j = 0; j < KGAME_SIDES; j++){
            if(game->board[i][j] == 'K'){
                return true;
            }
        }
    }
    return false;
}


bool kgame_is_move_possible(const kgame_t *game)
{
    // FIXME: Implement correctly (task 3)
    //return true;
     
    for(int i = 0; i < KGAME_SIDES-1; i++){ //-1 to stop a null pointer
        for(int j = 0; j < KGAME_SIDES-1; j++){
            if(game->board[i][j] == ' '){
                return true;
            }
        }
    }
    
    
    for(int i = 0; i < KGAME_SIDES-1; i++){ //-1 to stop a null pointer
        for(int j = 0; j < KGAME_SIDES-1; j++){
            if(game->board[i][j] == game->board[i][j+1]){//merge horizontal right
                return true;
            }else if(game->board[i][j] == game->board[i+1][j]){ //merge vertical down
                return true;
            }else if(game->board[i][j+1] == game->board[i][j]){  // merge horizontal left
                return true;
            }else if(game->board[i+1][j] == game->board[i][j]){// merge vertical up
                return true;
            }else if(game->board[i][j+1] == ' '){ //available right
                return true;
            }else if(game->board[i+1][j] == ' '){ //available down
                return true;
            }
        }
    }
        
        for(int i = 1; i < KGAME_SIDES; i++){ // start at 1 to stop a null pointer
            for(int j = 1; j < KGAME_SIDES; j++){
               if(game->board[i][j-1] == ' '){ //available left
                    return true;
                }else{
                    if(game->board[i-1][j] == ' '){ //available up
                        return true;
                    }
                }
            }
    }

return false;
    
}


bool kgame_update(kgame_t *game, dir_t direction){
    // FIXME: Implement correctly (task 4)
    //return true;  
    
    //get the direction user is trying to move
    //check if you can merge, or you can move
    //if you can move then move in that direction until you no longer can
    //if the next space in the direction you are moving is the same as the current instance then 
        //add 1 to the 'next space' and set the current to ' '
    //if the merged value is k then stop the game
            
            
            if(direction == UP){
                int moved = 0;
                for(int j = KGAME_SIDES-1; j >= 0; j--){ //cols 
                    int shifter = 0;
                    while(shifter <= 4){ //this is the shfit to bring everything as far the the direction as possible
                        for(int i = KGAME_SIDES-1; i > 0; i--){ //row
                            if(game->board[i-1][j] == ' '){
                                game->board[i-1][j] = game->board[i][j];
                                game->board[i][j] = ' ';
                                }
                            }
                            shifter++;
                            moved =1;
                    }
                    //allowing to merge
                    int shifter1 = 0;
                    while(shifter1 < 1){ 
                        for(int z = 0; z < KGAME_SIDES; z++){
                            if(game->board[z][j] == game->board[z-1][j] && game->board[z][j] != ' '){ //if the current is same as tile to the left -merge
                                game->board[z-1][j] += 1; //set the value to change by 1 character
                                game->board[z][j] = ' ';
                                game->score += updateScore(game->board[z-1][j]);
                                break;
                                }
                            }
                            shifter1++;
                            moved =1;
                    }
                    
                    //bringing everything as far as direction after a merge
                    int shifter2 = 0;
                    while(shifter2 < 1){
                        for(int i = KGAME_SIDES-1; i >= 0; i--){ //row
                            if(game->board[i-1][j] == ' '){
                                game->board[i-1][j] = game->board[i][j];
                                game->board[i][j] = ' ';
                            }
                        }
                        shifter2++;
                        moved = 1;
                    }
                }
                if(moved == 1){
                    return true;    
                }else{
                    return false;
                }
            }
            
            if(direction == DOWN){ //working
				int moved = 0;
                for(int j = 0; j < KGAME_SIDES; j++){ //cols
                    
                    int shifter = 0;
                    while(shifter <= 4){ //move
                        for(int i = 0; i < KGAME_SIDES; i++){ //row
                            if(game->board[i+1][j] == ' '){
                                game->board[i+1][j] = game->board[i][j];
                                game->board[i][j] = ' ';
                            }
                        }
                        shifter++;
                        moved = 1;
                    }   
                    
                    //merge only once
                    int shifter1 = 0;
                    while(shifter1 < 1){
                        for(int z = 0; z < KGAME_SIDES; z++){
                            if(game->board[z][j] == game->board[z+1][j] && game->board[z][j] != ' '){ 
                                game->board[z+1][j] += 1;
                                game->board[z][j] = ' ';
                                game->score += updateScore(game->board[z+1][j]);
                                break;
                            }
                        }
                        shifter1++;
                        moved = 1;
                    }
                    
                    //move
                    int shifter2 = 0;
                    while(shifter2 <= 4){
                        for(int i = 0; i < KGAME_SIDES; i++){ //row
                            if(game->board[i+1][j] == ' '){
                                game->board[i+1][j] = game->board[i][j];
                                game->board[i][j] = ' ';
                            }
                        }
                        shifter2++;
                    }    
                }
                if(moved = 1){
					return true;
				}else{
					return false;
				}
            }
            
            
            if(direction == RIGHT){ //only moving 1 step
				int moved = 0;
                for(int i = KGAME_SIDES-1; i >= 0; i--){
                    int shifter = 0;
                    while(shifter <= 4){
                        for(int j = KGAME_SIDES-2; j >= 0; j--){ 
                            if(game->board[i][j+1] == ' '){
                                game->board[i][j+1] = game->board[i][j];
                                game->board[i][j] = ' ';
                            }
                        }
                        shifter++;
                        moved = 1;
                    }
                    
                    int shifter1 = 0;
                    while(shifter1 < 1){
                        for(int z = 0; z < KGAME_SIDES; z++){
                            if(game->board[i][z] == game->board[i][z+1] && game->board[i][z] != ' '){
                                game->board[i][z+1] += 1;
                                game->board[i][z] = ' ';
                                game->score += updateScore(game->board[i][z+1]);
                                break;
                            }
                        }
                        shifter1++;
                        moved = 1;
                    }
                    
                    int shifter2 = 0;
                    while(shifter2 <= 4){
                        for(int j = KGAME_SIDES-2; j >= 0; j--){ 
                            if(game->board[i][j+1] == ' '){
                                game->board[i][j+1] = game->board[i][j];
                                game->board[i][j] = ' ';
                            }
                        }
                        shifter2++;
                    } 
                }
                if(moved = 1){
					return true;
				}else{
					return false;
				}
            }

            if(direction == LEFT){
				int moved = 0;
                for(int i = 0; i < KGAME_SIDES; i++){
                    int shifter = 0;
                    while(shifter <= 4){ //makes the move
                        for(int j = 1; j < KGAME_SIDES; j++){
                            if(game->board[i][j-1] == ' '){ //first check if its avilable first
                                game->board[i][j-1] = game->board[i][j]; //update to move the current left
                                game->board[i][j] = ' '; //update it to be empty as it have now moved
                                moved = 1;
                                }  
                            }
                            shifter++;
                        }
                        //merge 
                        
                        int shifter1 = 0;
                        while(shifter1 < 1 ){
                            for(int z = 0; z < KGAME_SIDES; z++){
                                if(game->board[i][z] == game->board[i][z-1] && game->board[i][z] != ' '){ //if the current is same as tile to the left -merge
                                    game->board[i][z-1] += 1; //set the value to change by 1 character
                                    game->board[i][z] = ' ';
                                    game->score += updateScore(game->board[i][z-1]);
                                    moved = 1;
                                    break;
                                }
                            }
                            shifter1++;
                            
                        }
                        
                        int shifter2 = 0;
                        while(shifter2 <= 4){
                            for(int j = 1; j < KGAME_SIDES; j++){
                                if(game->board[i][j-1] == ' '){ //first check if its avilable first
                                    game->board[i][j-1] = game->board[i][j]; //update to move the current left
                                    game->board[i][j] = ' '; //update it to be empty as it have now moved
                                }
                            }
                            shifter2++;
                        }
                    }
                    if(moved = 1){
						return true;
					}else{
						return false;
					}
                }
			}
        
int updateScore(int letter){
    return(1<<(letter - 65))*2;
}


void kgame_save(const kgame_t *game)
{
    // FIXME: Implement correctly (task 5)
    
    FILE *fp;
    
    fp = fopen("KGAME_SAVE_FILE", "w"); //open the file to be writeable
    
    for(int i = 0; i < KGAME_SIDES; i++){
     for(int j = 0; j < KGAME_SIDES; j++){
         if(game->board[i][j] == ' '){
             putc('-', fp);
         }else{
             putc(game->board[i][j], fp);
         }
     }
    }
    
    fprintf(fp, "%d", game->score);
    
    fclose(fp); //close the file
}


bool kgame_load(kgame_t *game)
{
    // FIXME: Implement correctly (task 6)
    FILE *fp;
    char c;
    int score;
    
    fp = fopen("KGAME_SAVE_FILE", "r");
    
    if(fp == NULL){
        return false;
    }

     for(int i = 0; i < KGAME_SIDES; i++){
        for(int j = 0; j < KGAME_SIDES; j++){
            c = getc(fp);
            if(c == '-'){
                game->board[i][j] = ' ';
            }else{
                game->board[i][j] = c;
            }
        }
     }
     
         
    fscanf(fp, "%d", &score);
    game->score = score;

    
    fclose(fp);
    
    return true;
}


