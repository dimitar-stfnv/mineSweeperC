#include <stdio.h>
#include <stdlib.h>

struct Board
{
    int n;
    void*** fields;
};
enum FieldType
{
    MINE,
    EMPTY
};
struct Mine
{
    enum FieldType fieldtype;
    short discovered;
};

struct Empty
{
    enum FieldType fieldtype;
    short discovered;   
    void** neighbors;
};

struct Mine* newMine()
{
    struct Mine* mine = malloc(sizeof(struct Mine));
    mine->discovered = 0;
    mine->fieldtype = MINE;
    return mine;
}

struct Empty* newEmpty(short neighborsCount)
{
    struct Empty* empty = malloc(sizeof(struct Empty));
    empty->discovered = 0;
    empty->fieldtype = EMPTY;
    empty->neighbors = malloc(neighborsCount * sizeof(void*));
    return empty;
}

enum FieldType fieldTypeOf(void* field)
{
    if(field == MINE)
    {
        return MINE;
    }
    else
    {
        return EMPTY;
    }
}

int getNeighborsCount(int i, int j, int n)
{
    if(i == 0 && j == 0 || i == 0 && j == n-1 || i == n-1 && j == 0 || i == n-1 && j == n-1)
    {return 3;}
    else if(i == 0 || i == n-1 || j == 0 || j == n-1)
    {return 5;}
    else 
    {return 8;}

}

struct Board* newBoard(short n)
{
    struct Board* board = malloc(sizeof(struct Board));
    board->n = n;
    board->fields = malloc(n * sizeof(void**));
    
    for(int i = 0; i < n; i++)
    {
        board->fields[i] = malloc(n * sizeof(void*));
        for(int j = 0; j < n; j++)
        {
            int randNum = rand();
            if(randNum % 5 == 0)
            {
                board->fields[i][j] = newMine();              
            }
            else
            {
                int neighborsCount = getNeighborsCount(i, j, n);
                board->fields[i][j] = newEmpty(neighborsCount);
            }
        }
    }
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(fieldTypeOf(board->fields[i][j]) == EMPTY)
            {
                struct Empty* currentField = (struct Empty*) board->fields[i][j];
                int br = 0;
                for(int k = 0; k < 3; k++)
                {
                    for(int p = 0; p < 3; p++)
                    {
                        if(i-1+k < 0 || i-1+k > n-1 || j-1+p < 0 || j-1+p > n-1)
                        {
                            continue;
                        }
                        currentField->neighbors[br] = board->fields[i-1+k][j-1+p];
                        br++;
                    }
                }
            }
        }
    }     
    return board;
}

short mineCount(struct Empty* field, int neighborsCount)
{
    int count = 0;
    for (int i = 0; i < neighborsCount; i++)
    {
        if (fieldTypeOf(field->neighbors[i]) == MINE)
        {
            count++;
        }
    }
    return count;
}

void printBoard(struct Board* board)
{
    for(int i = 0; i < board->n; i++)
    {
        for(int j = 0; j < board->n; j++)
        {
            if(fieldTypeOf(board->fields[i][j]) == EMPTY)
            {
                struct Empty* currentField = (struct Empty*) board->fields[i][j];
                if(currentField->discovered == 0)
                {
                    printf(" ");
                }
                else
                {
                    printf("%d", mineCount(currentField, getNeighborsCount(i, j, board->n)));
                }
            }
            else
            {
                struct Mine* currentField = (struct Mine*) board->fields[i][j];
                if(currentField->discovered == 0)
                {
                    printf("O");
                }
                else
                {
                    printf(" ");
                }
            }
        }
    }
}

void saveBoard(struct Board *board)
{
    FILE *file = fopen("board.txt", "w");
    if (file == NULL)
    {
        printf("Error opening file!\n");
        return;
    }
    short n = board->n;
    fprintf(file, "%d\n", n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            void *field = board->fields[i][j];
            enum FieldType type = ((struct Mine *)field)->fieldtype;
            if (type == MINE)
            {
                struct Mine *mine = (struct Mine *)field;
                fputc(mine->discovered ? 'm' : 'M', file);
            }
            else
            {
                struct Empty *empty = (struct Empty *)field;
                fputc(empty->discovered ? 'e' : 'E', file);
            }
        }
        fputc('\n', file);
    }
    fclose(file);
}

struct Board *parseBoard(const char *filename)
{
    FILE* file = fopen(filename, "r");
    int n;
    fscanf(file, "%d", &n);

    struct Board *board = malloc(sizeof(struct Board));
    board->fields = malloc(n * sizeof(*board->fields));
    for (int i = 0; i < n; i++)
    {
        board->fields[i] = malloc(n * sizeof(*board->fields));
        for (int j = 0; j < n; j++)
        {
            char *line = malloc(n * sizeof(char));
            scanf("%s", line);
        }
    }

    fclose(file);
}

void discover(struct Board* board, struct Empty* field)
{
    
}

int main() {
    putc('a', stdout);
    putc('b', stdout);
    putc('c', stdout);
    putc('\n', stdout);
    printf("abc\n");
    puts("abc");
    const char *asd = "asdasdasd";
}