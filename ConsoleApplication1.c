#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <ctype.h>




//maximum word length will be 100;

char    player_guess;                  //the character the player will guess
int     guessed_letters[26] = { 0 };     //array of characters 0-25 (a-z) the player has guessed. 0 if not guessed, 1 if guessed.
int      lives = 6;
bool    seen[26] = { false };
int      letters_left = 0;
bool    game_over = false;
char    ans = 'y';
char    random_word[100];

const char* get_word();              //gets random word from a file. use rand(time(null));
void    draw_game(const char* word);   // the pole, and the dashes depending on size of the word ( calculates the size here).        
void    reset_game(const char* word);
bool keep_reading = true;


int main(void)
{
    
    srand(time(NULL));

    int random_line = rand() % 12;
    printf("Random number: %d\n", random_line);
    int current_line = 1;
    
    FILE* pF = fopen("words.txt", "r");

    if (pF == NULL)
    {
        printf("Unable to open file.");
    }

    do
    {
        fgets(random_word, 100, pF);
       // printf("%s\n", random_word);

        if (feof(pF))
        {
            keep_reading = false;
            printf("File had %d lines.\n", current_line - 1);
            printf("Couldnt find  line %d\n", random_line);
        }
        else if (current_line == random_line)
        {
            keep_reading = false;
        }
        current_line++;
    } while (keep_reading);

    fclose(pF);
   
    
    for (int i = 0; i < strlen(random_word); i++)
    {
        if (isalpha(random_word[i]) && !seen[tolower(random_word[i]) - 'a'])
        {
            letters_left++;
            seen[tolower(random_word[i]) - 'a'] = true;
        }
    }

    int     num = 0;
  

    while (ans == 'y') {
        
        printf("number of unique letters left: %d\n", letters_left);
 
        draw_game(random_word);

        printf("type letter here: ");
        do {


            player_guess = getchar();


            while (getchar() != '\n' && getchar() != EOF); //consume the newline character from user pressing enterer

            if (!isalpha(player_guess))
            {
                printf("thats not a valid letter.");
            }

            num = tolower(player_guess) - 'a'; //converts player_guess to its coressponding place in the alphabet. e.g. a -> 0
            //printf("Letter to num: %d\n", num);

            if (guessed_letters[num] > 0)
            {
                printf("You already guessed that letter. \n");
            }
            else
            {
               guessed_letters[num] += 1;
               if (strchr(random_word, player_guess) == NULL)
               {
                   lives -= 1;
                   printf("----------------------------------\n\n");
                   printf("Wrong guess! Lives left: %d\n", lives);
               }
               else
               {
                   letters_left--;
               }
            }
            
          

        } while (!isalpha(player_guess) && guessed_letters[num] > 0);

        
        
        
        

        printf("Guessed letters: ");
        for (int i = 0; i < 26; i++)
        {
            if (guessed_letters[i] > 0)
            {
                printf("%c ", i + 'a');
            }
        }
        printf("\n\n");

       
        

        printf("------------------------------\n");

    }
    
   

    return 0;
}

void draw_game(const char* word)

{
    printf    (" |---|\n");
    printf    (" |   |\n");

    
    //head
    if (lives == 6) {
        printf(" |    \n");
    } 
    else 
    {
        printf(" |   O \n");
    }

    //body
    if (lives == 4)
    {
        printf(" |   | \n");
    }
    else if (lives == 3)
    {
        printf(" |  /|   \n");
    }
    else if (lives <= 2)
    {
        printf(" |  /|\\   \n");
    }
    else
    {
        printf(" |     \n");
    }

    //legs

    if (lives == 1)
    {
        printf(" |  /  \n");
    }
    else if (lives == 0)
    {
        printf(" |  / \\  \n");
    }
    else
    {
        printf(" |    \n");
    }
   
    printf      (" |   \n");
    printf      ("_|_   \n");
    //printf("%s\n", word);
    for (int i = 0; i < strlen(word); i++)
    {
            if (guessed_letters[(tolower(word[i]) - 'a')] > 0)
            {
                printf("%c ", word[i]);
                
            }
            else if (word[i] == ' ')
            {
                printf("   ");
            }
            else
            {
                printf("_ ");
            }
        }
        printf("\n");

        if (lives <= 0)
        {
            printf("You ran out of lives. Try again? \n");
            ans = getchar();
            while (getchar() != '\n' && getchar() != EOF);
            if (tolower(ans) == 'n')
            {
                printf("good bye!");
                return 0;
            }
            else
            {
                reset_game(random_word);
            }
        }
        if (letters_left <= 0)
        {
            printf("@@@@@@@@@@@@@@@@@@@@@@@@\n\n");
            printf("You WIN!!!!\n\n");
            printf("@@@@@@@@@@@@@@@@@@@@@@@@\n\n");
            printf("Play again? ");
            ans = getchar();
            while (getchar() != '\n' && getchar() != EOF);
            if (tolower(ans) == 'n')
            {
                printf("good bye!");
                return 0;
            }
            else
            {
                reset_game(random_word);
            }

        }
        
    }


void reset_game(const char* word)
{
    memset(guessed_letters, 0, sizeof(guessed_letters));
    memset(seen, 0, sizeof(seen));
    lives = 6;
    letters_left = 0;

    for (int i = 0; i < strlen(word); i++)
    {
        if (isalpha(word[i]) && !seen[tolower(word[i]) - 'a'])
        {
            letters_left++;
            seen[tolower(word[i]) - 'a'] = true;
        }
    }
    
    printf("@@@@@@Game reset@@@@@@\n");

}