/* tictactoe with 3-step AI
 * written by Kamil Piekutowski
 * TODO:
 * -fix the memory leaks
 * -expand to more than 3x3 matrix
 * -fix input, to not allw human to overwirte
 */














#include <stdio.h>
#include <stdlib.h>

struct board{
	struct board* next;
	struct board* prev;
	char cell[9];
	int mvsleft; //moves left
};

int
init_brd(struct board* b) //initialize the board
{
	int i = 0;
	for(i = 0; i < 9; ++i){
		b->cell[i] = ' ';
	}
	b->mvsleft = 9;
  b->next = NULL;
	b->prev = NULL;
}

int
cpy_brd(struct board* dst,struct board* b)
{
	int i;
	for(i = 0;i < 9;++i){
		dst->cell[i] = b->cell[i];
	}
	dst->mvsleft = b->mvsleft;
}

int
make_move(struct board* b,char p,int c)
{
	if(c == -999)
		return -999;
	b->cell[c] = p;
	return 1;
}
int
remove_move(struct board* b,int c)
{
	b->cell[c] = ' ';
	return 1;
}

struct board*
new_brd()
{
	return malloc(sizeof(struct board));
}

//AI starts here
//
int
check3_layers(struct board* b){
	int i,j,k,l;
	struct board* start = b;
	struct board* curr = b;
  struct board* tmp = new_brd();

	cpy_brd(tmp,curr);
	//append_brd(curr,tmp);
	int may_loose = 0;
	int good_strategy = 0;
  for(i = 0;i < 9; ++i){
		if(tmp->cell[i] == ' '){
			may_loose = 0;
			good_strategy = 0;
			make_move(tmp,'o',i);
			if(check_if_loose(tmp)){
				goto win;
			}
			else{
				for(j = 0;j < 9; ++j){
					if(tmp->cell[j] == ' '){
						make_move(tmp,'x',j);
						//display_brd(tmp);
						if(check_if_loose(tmp)){
							//printf("*** you may loose ***\n");
							//display_brd(tmp);
							may_loose = 1;
						}
						else{ //checking 3rd move
							for(k = 0; k < 9; ++k){
								if(tmp->cell[k] == ' '){
									make_move(tmp,'o',k);
									if(check_if_loose(tmp)){
										good_strategy = 1;
										remove_move(tmp,k);
									}
									else{
										remove_move(tmp,k);
									}
								}		
							}
						}
						remove_move(tmp,j);
					}
				}
				if(!may_loose && good_strategy){
					goto win;
				}
				else if(!may_loose){
					goto win;
				}
				else{
					remove_move(tmp,i);
				}	
		}
	}
	//display_brd(tmp);
	}

	

  	

	i = rand()%10;
	if(tmp->cell[i] == ' '){
		make_move(tmp,'o',i);
		remove_move(tmp,i);
	}
	else{
		++i;
		if(i > 9)
			i = 0;
		while(tmp->cell[i] != ' '){
			++i;
			if(i > 9)
				i = 0;
		}
		make_move(tmp,'o',i);
	}
  win:
	//printf("EXITING AI\n");
	b->next = NULL;
	if(may_loose)
		return -999;
	return i;

}

//AI ends here

int 
check_if_loose(struct board* b)
{
	int i;
	//check columns
	for(i = 0;i < 3;++i){
		if(b->cell[i] == b->cell[i+3] && b->cell[i+3] == b->cell[i+6] &&
				b->cell[i] != ' ' && b->cell[i+3] != ' ' &&  b->cell[i+6] != ' ')
			return 1;
	}
	//check rows
	for(i = 0;i < 9;i += 3){
		if(b->cell[i] == b->cell[i+1] && b->cell[i+1] == b->cell[i+2] &&
				b->cell[i] != ' ' && b->cell[i+1] != ' ' && b->cell[i+2] != ' ')
			return 1;
	}
	//check diognals
	if(b->cell[0] == b->cell[4] && b->cell[4] == b->cell[8] &&
			b->cell[0] != ' ' && b->cell[4] != ' ' &&  b->cell[8] != ' ')
		return 1;
	if(b->cell[2] == b->cell[4] && b->cell[4] == b->cell[6] &&
			b->cell[2] != ' ' && b->cell[4] != ' ' && b->cell[6] != ' ')
		return 1;

	return 0;
}

int 
display_brd(struct board* b)
{
	printf("\n %c|%c|%c\n",b->cell[0],b->cell[1],b->cell[2]);
	printf("-------\n");
	printf(" %c|%c|%c\n",b->cell[3],b->cell[4],b->cell[5]);
	printf("-------\n");
	printf(" %c|%c|%c\n\n",b->cell[6],b->cell[7],b->cell[8]);
}





int
append_brd(struct board* b,struct board* tail)
{
	b->next = tail;
	tail->prev = b;
}

int
list_brd_back(struct board* b)//lists all moves backwards
{
	struct board* probe = b;
	while(probe->prev != NULL){
		printf("\n");
		display_brd(probe);
		probe = probe->prev;
	}
}
int
list_brd_forw(struct board* b)//lists all moves backwards
{
	struct board* probe = b;
	while(probe->next != NULL){
		printf("\n");
		display_brd(probe);
		probe = probe->next;
	}
}

int
get_human_move(struct board* b){
	int move = 0; //to  skip first test;
	int tryagain = 0;
	while(move < 1 || move > 9 || b->cell[move-1] != ' '){
		if(tryagain)
			printf("\nTry again: ");
		scanf("%d",&move);
		tryagain = 1;
	}
	return move-1;
}

int
get_cpu_move(struct board* b)
{
	
}


int main()
{
	char P1 = 'x';
	char P2 = 'o';

	struct board brd;
	struct board* curr = &brd; //need to remember the current move
	init_brd(&brd);
  display_brd(&brd);

	srand(time(NULL)); //seeding 
  
  while(curr->mvsleft){
		//player1
		printf("Player1 Enter move: ");
		struct board *tmp1 = new_brd();
		cpy_brd(tmp1,curr);
		if(curr->mvsleft){
			if(make_move(tmp1,'x',check3_layers(tmp1)) == -999){ //placing move on board
				printf("No more winning moves Player2 loses.\n");
				return -999;
			}
		}
		else
			goto tie;
		//make_move(tmp1,'x',get_human_move(tmp1)); //placing move on board
		append_brd(curr,tmp1);
		curr = tmp1;
		printf("\n");
		//printf("addr of tmp1 %x\n",tmp1);
		//player2
		display_brd(curr);
		if(check_if_loose(curr)){
			printf("Player1 won. Game Over\n");
			//list_brd_forw(&brd);
			return 1;
		}


		curr->mvsleft--;

		printf("Player2 Enter move: ");
		struct board *tmp2 = new_brd();
		cpy_brd(tmp2,curr);
		if(curr->mvsleft){
			make_move(tmp2,'o',get_human_move(tmp2)); //placing move on board
		}
		else
			goto tie;
		//make_move(tmp2,'o',get_human_move()); //placing move on board
		append_brd(curr,tmp2);
		curr = tmp2;
		printf("\n");
		//printf("addr of tmp2 %x\n",tmp2);
		display_brd(curr);
		if(check_if_loose(curr)){
			printf("Player2 won. Game Over\n");
			//list_brd_forw(&brd);
			return 1;
		}
		curr->mvsleft--;
		printf("moves left %d\n",curr->mvsleft);
	}
	tie:
	printf("\nThere was a tie.\n");
	return 0;
}
