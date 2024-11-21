#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BOARD_SIZE 3

#define EMPTY_SYMBOL ' '
#define COMPUTER_SYMBOL 'X'
#define PLAYER_SYMBOL 'O'
#define TIED_SYMBOL 'T'

#define VERTICAL 0
#define HORIZONTAL 1
#define DIAGONAL_N 2 // negative slope
#define DIAGONAL_P 3 // positive slope

static char *board = NULL;

int initBoard()
{
    board = (char *)malloc(BOARD_SIZE * BOARD_SIZE * sizeof(char));
    if (NULL == board)
    {
        return -1;
    }
    memset(board, EMPTY_SYMBOL, BOARD_SIZE * BOARD_SIZE * sizeof(char));
    return 0;
}

void deinitBoard()
{
    free(board);
    board = NULL;
}

char checkWinner(int direction)
{
    int i, j, k;
    char first_symbol;

    for (i = 0; i < (DIAGONAL_N == direction || DIAGONAL_P == direction ? 1 : BOARD_SIZE); i++)
    {
        if (VERTICAL == direction)
        {
            k = i;
        }
        else if (HORIZONTAL == direction)
        {
            k = i * BOARD_SIZE;
        }
        else if (DIAGONAL_N == direction)
        {
            k = 0;
        }
        else if (DIAGONAL_P == direction)
        {
            k = BOARD_SIZE - 1;
        }
        if (EMPTY_SYMBOL == (first_symbol = board[k]))
        {
            continue;
        }
        for (j = 1; j < BOARD_SIZE; j++)
        {
            if (VERTICAL == direction)
            {
                k = j * BOARD_SIZE + i;
            }
            else if (HORIZONTAL == direction)
            {
                k = i * BOARD_SIZE + j;
            }
            else if (DIAGONAL_N == direction)
            {
                k = j * BOARD_SIZE + j;
            }
            else if (DIAGONAL_P == direction)
            {
                k = j * BOARD_SIZE + (BOARD_SIZE - 1) - j;
            }
            if (first_symbol != board[k])
            {
                break;
            }
        }
        if (BOARD_SIZE == j)
        {
            return first_symbol;
        }
    }
    return TIED_SYMBOL;
}

char getWinner()
{
    char winner;

    if (TIED_SYMBOL != (winner = checkWinner(VERTICAL)))
    {
        return winner;
    }
    if (TIED_SYMBOL != (winner = checkWinner(HORIZONTAL)))
    {
        return winner;
    }
    if (TIED_SYMBOL != (winner = checkWinner(DIAGONAL_N)))
    {
        return winner;
    }
    if (TIED_SYMBOL != (winner = checkWinner(DIAGONAL_P)))
    {
        return winner;
    }
    return TIED_SYMBOL;
}

void printBoard()
{
    int i;
    int j;

    for (i = 0; i < BOARD_SIZE; i++)
    {
        for (j = 0; j < BOARD_SIZE; j++)
        {
            printf("%c", board[i * BOARD_SIZE + j]);
            if (BOARD_SIZE - 1 != j)
            {
                printf("|");
            }
            else
            {
                printf("\n");
            }
        }
        if (BOARD_SIZE - 1 != i)
        {
            for (j = 0; j < BOARD_SIZE; j++)
            {
                printf("-");
                if (BOARD_SIZE - 1 != j)
                {
                    printf("+");
                }
            }
        }
        printf("\n");
    }
}

#if 1//CS
#define	BOX_ONE		0
#define	BOX_TWO		1
#define	BOX_THREE	2
#define	BOX_FOUR	3
#define	BOX_FIVE	4
#define	BOX_SIX		5
#define	BOX_SEVEN	6
#define	BOX_EIGHT	7
#define	BOX_NINE	8

int check_human_winning_possibility_in_all_direction(int direction)
{
	int raw, column;
	int index;
	int safe_index = -1;
	int found_similar_symbol = 0;

	for (column = 0; column < (DIAGONAL_N == direction || DIAGONAL_P == direction ? 1 : BOARD_SIZE); column++)
	{
		for (raw = 0; raw < BOARD_SIZE; raw++)
		{
			if (VERTICAL == direction)
			{
				index = (raw * BOARD_SIZE) + column;
			}
			else if (HORIZONTAL == direction)
			{
				index = (column * BOARD_SIZE) + raw;
			}
			else if (DIAGONAL_N == direction)
			{
				index = (raw * BOARD_SIZE) + raw;
			}
			else if (DIAGONAL_P == direction)
			{
				index = (raw * BOARD_SIZE) + (BOARD_SIZE - 1) - raw;
			}
			
			if (board[index] == COMPUTER_SYMBOL)
			{
				found_similar_symbol = 0;
				break;
			}
			else if (board[index] == PLAYER_SYMBOL)
			{
				found_similar_symbol++;	
			}
			else if (board[index] == EMPTY_SYMBOL)
			{
				safe_index = index;
			}
		}
		if (found_similar_symbol == 2)
		{
			printf("Found loosing possibility in %d direction :: Safe index is: %d\r\n", direction, safe_index);
			return safe_index; 
		}
		else
		{
			found_similar_symbol = 0;
			safe_index = -1;
		}
	}
	return -1;
}

int check_human_winning_possibility(void)
{
	int status;

	status = check_human_winning_possibility_in_all_direction(VERTICAL);
	if (status != -1)
	{
		printf("Found loosing possibility in VERTICAL direction :: Safe index is: %d\r\n", status);
		return status;
	}
	
	status = check_human_winning_possibility_in_all_direction(HORIZONTAL);
	if (status != -1)
	{
		printf("Found loosing possibility in HORIZONTAL direction :: Safe index is: %d\r\n", status);
		return status;
	}
	
	status = check_human_winning_possibility_in_all_direction(DIAGONAL_N);
	if (status != -1)
	{
		printf("Found loosing possibility in DIAGONAL_N direction :: Safe index is: %d\r\n", status);
		return status;
	}
	
	status = check_human_winning_possibility_in_all_direction(DIAGONAL_P);
	if (status != -1)
	{
		printf("Found loosing possibility in DIAGONAL_P direction :: Safe index is: %d\r\n", status);
		return status;
	}
	
	return status;
}

int find_computer_winning_possibility_in_all_direction(int direction)
{
	int raw, column;
	int index;
	int winning_index = -1;
	int found_similar_symbol = 0;

	for (column = 0; column < (DIAGONAL_N == direction || DIAGONAL_P == direction ? 1 : BOARD_SIZE); column++)
	{
		for (raw = 0; raw < BOARD_SIZE; raw++)
		{
			if (VERTICAL == direction)
			{
				index = (raw * BOARD_SIZE) + column;
			}
			else if (HORIZONTAL == direction)
			{
				index = (column * BOARD_SIZE) + raw;
			}
			else if (DIAGONAL_N == direction)
			{
				index = (raw * BOARD_SIZE) + raw;
			}
			else if (DIAGONAL_P == direction)
			{
				index = (raw * BOARD_SIZE) + (BOARD_SIZE - 1) - raw;
			}
			
			if (board[index] == PLAYER_SYMBOL)
			{
				found_similar_symbol = 0;
				break;
			}
			else if (board[index] == COMPUTER_SYMBOL)
			{
				found_similar_symbol++;	
			}
			else if (board[index] == EMPTY_SYMBOL)
			{
				winning_index = index;
			}
		}
		if (found_similar_symbol == 2)
		{
			printf("Found winning possibility in %d direction :: Possible winning index is: %d\r\n", direction, winning_index);
			return winning_index; 
		}
		else
		{
			found_similar_symbol = 0;
			winning_index = -1;
		}
	}
	return -1;
}

int find_computer_winning_possibility(void)
{
	int status;

	status = find_computer_winning_possibility_in_all_direction(VERTICAL);
	if (status != -1)
	{
		printf("Found winning possibility in VERTICAL direction :: Possible winning index is: %d\r\n", status);
		return status;
	}
	
	status = find_computer_winning_possibility_in_all_direction(HORIZONTAL);
	if (status != -1)
	{
		printf("Found winning possibility in HORIZONTAL direction :: Possible winning index is: %d\r\n", status);
		return status;
	}
	
	status = find_computer_winning_possibility_in_all_direction(DIAGONAL_N);
	if (status != -1)
	{
		printf("Found winning possibility in DIAGONAL_N direction :: Possible winning index is: %d\r\n", status);
		return status;
	}
	
	status = find_computer_winning_possibility_in_all_direction(DIAGONAL_P);
	if (status != -1)
	{
		printf("Found winning possibility in DIAGONAL_P direction :: Possible winning index is: %d\r\n", status);
		return status;
	}
	
	return status;
}

int chose_opposite_corner(void)
{
	return 0;
}

int chose_corner_on_first_move(void)
{
	return 0;
}

void next_simple_move(void)
{
	int i, j;
	for (i = 0; i < BOARD_SIZE; i++)
	{
		for (j = 0; j < BOARD_SIZE; j++)
		{
			if (EMPTY_SYMBOL == board[i * BOARD_SIZE + j])
			{
				board[i * BOARD_SIZE + j] = COMPUTER_SYMBOL;
				return;
			}
		}
	}
}
#endif//CS

void makeComputerMove()
{
    printf("My move:\n");

    // TODO: This function to be implemented by the applicant.
    // Do not modify any existing function or macro (except for the value of BOARD_SIZE).
    // The implementation must work for BOARD_SIZE >= 2.
    // It is ok to add helper functions only to be used by this function.
    // It is ok to add global variables only to be used by this function.

#if	1//CS
	static unsigned int current_move = 0;
	int safe_index;
	int winning_index;

	//For first move
	if (current_move == 0)
	{
		//Condition - 1: Check all corners are blank or not
		if (board[BOX_ONE] == EMPTY_SYMBOL && board[BOX_THREE] == EMPTY_SYMBOL && board[BOX_SEVEN] == EMPTY_SYMBOL && board[BOX_NINE] == EMPTY_SYMBOL)
		{
			//All corners are blank - find appropriate corner to fill first X
			//chose_corner_on_first_move();
			board[0] = COMPUTER_SYMBOL;
		}
		else
			board[4] = COMPUTER_SYMBOL;
		current_move++;
	}
	else
	{
		//safe_index = check_human_winning_possibility();
		//if (safe_index != -1)
		if (-1 != (safe_index = check_human_winning_possibility()))
		{
			printf("Saving my self from loss\r\n");//CS	
			board[safe_index] = COMPUTER_SYMBOL;
		}
		else if (-1 != (winning_index = find_computer_winning_possibility()))
		{
			printf("Found winning position at: %d\r\n", winning_index);
			board[winning_index] = COMPUTER_SYMBOL;
		}
		else
			next_simple_move();
	}
#endif//CS
}

void flushStdin()
{
    int c;

    while ('\n' != (c = getchar()) && EOF != c);
}

void makePlayerMove()
{
    int player_move;

    while (1)
    {
        player_move = -1;
        printf("Your move (enter a space 1-%d)?\n", BOARD_SIZE * BOARD_SIZE);
        if (1 != scanf("%d", &player_move))
        {
            flushStdin();
            printf("Invalid move. You must select a space between 1 and %d.\n\n", BOARD_SIZE * BOARD_SIZE);
            continue;
        }

        player_move--;
        if (0 > player_move || BOARD_SIZE * BOARD_SIZE - 1 < player_move)
        {
            printf("Invalid move. You must select a space between 1 and %d.\n\n", BOARD_SIZE * BOARD_SIZE);
            continue;
        }

        if (EMPTY_SYMBOL != board[player_move])
        {
            printf("Invalid move. You must select an empty space.\n\n");
            continue;
        }

        board[player_move] = PLAYER_SYMBOL;
        break;
    }
}

int main(void)
{
    int round_count = 0;
    char winner;

    if (0 != initBoard())
    {
        printf("Error initializing game, exiting.\n");
        return EXIT_FAILURE;
    }
    printBoard();

    while (TIED_SYMBOL == (winner = getWinner()) && round_count < BOARD_SIZE * BOARD_SIZE)
    {
		printf("winner: %c\r\n", winner);//CS - remove
        if (0 == round_count++ % 2)
        {
            makePlayerMove();
        }
        else
        {
            makeComputerMove();
        }
        printBoard();
    }

    if (COMPUTER_SYMBOL == winner)
    {
        printf("I win! Computers are the best!\n");
    }
    else if (PLAYER_SYMBOL == winner)
    {
        printf("You win! Darn humans!\n");
    }
    else
    {
        printf("We tied!\n");
    }

    deinitBoard();
    return EXIT_SUCCESS;
}
