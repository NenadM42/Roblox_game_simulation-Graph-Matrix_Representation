#include <stdio.h>
#include <string.h>


int matrix[10][5] = { {0,1,0,0,1},
{1,0,1,1,1},
{0,1,0,0,1},
{0,1,1,0,1},
{1,1,0,1,0} };


int **mapa;
int matr[4][100][100];
char **map_string;

int number_of_elements;
int rows = 0;
int cols = 0;
int cnt = 0;


typedef struct bufer
{
	int value, state;
}Bufer;

typedef struct stek
{
	Bufer bufer[3000];
	int kraj;
}Stek;

Stek s;
Stek put;

int stack_empty()
{
	if (s.kraj == 0)
		return 1;
	else
		return 0;
}

Bufer pop()
{
	int x = s.kraj;
	Bufer a = s.bufer[x];
	s.kraj--;
	return a;
}

Bufer get()
{
	int x = s.kraj;
	Bufer a = s.bufer[x];
	return a;
}

void push(int value, int state)
{
	s.kraj++;
	Bufer b;
	b.value = value;
	b.state = state;
	s.bufer[s.kraj] = b;
}

void push2(int value, int state)
{
	put.kraj++;
	Bufer b;
	b.value = value;
	b.state = state;
	put.bufer[put.kraj] = b;
}

Bufer pop2()
{
	int x = put.kraj;
	Bufer a = put.bufer[x];
	put.kraj--;
	return a;
}


void addNode()
{
	number_of_elements++;


	for (int j = 1; j <= 3; j++)
	{
		for (int i = 0; i < number_of_elements - 1; i++)
		{
			matr[j][i][number_of_elements - 1] = 0;
		}

		for (int i = 0; i < number_of_elements; i++)
		{
			matr[j][number_of_elements - 1][i] = 0;
		}
	}
}

void addEdge(int a, int b, int level, int leveln)
{
	matr[level][a][b] = leveln;
	matr[leveln][b][a] = level;
	//matr[a][b] = 1;
	//matr[b][a] = 1;
}

void addEdgeROWnCOL(int row, int col)
{
	map_string[row][col] = 'o';
	mapa[row][col] = number_of_elements - 1;


	int i = row, j = col;

	int level, leveln;
	//odradimo prvo za 1. state tj kad je usparvno
	//gore
	if (i - 2 >= 0 && mapa[i - 2][j] != -1 && mapa[i - 1][j] != -1)
	{
		level = 1;
		leveln = 2;

		addEdge(mapa[i][j], mapa[i - 2][j], level, leveln);
	}
	// dole
	if (i + 2 < rows && mapa[i + 2][j] != -1 && mapa[i + 1][j] != -1)
	{
		level = 1;
		leveln = 2;
		addEdge(mapa[i][j], mapa[i + 1][j], level, leveln);
	}
	//desno
	if (j + 2 < cols && mapa[i][j + 2] != -1 && mapa[i][j + 1] != -1)
	{
		level = 1;
		leveln = 3;
		addEdge(mapa[i][j], mapa[i][j + 2], level, leveln);
	}
	//levo
	if (j - 2 >= 0 && mapa[i][j - 2] != -1 && mapa[i][j - 1] != -1)
	{
		level = 1;
		leveln = 3;
		addEdge(mapa[i][j], mapa[i][j - 1], level, leveln);
	}

	//sad kad je state 2 |
	//gore
	if (i - 1 >= 0 && mapa[i - 1][j] != -1)
	{
		level = 2;
		leveln = 1;
		addEdge(mapa[i][j], mapa[i - 1][j], level, leveln);
	}

	//dole

	if (i - 2 >= 0 && mapa[i - 2][j] != -1)
	{
		level = 2;
		leveln = 1;
		addEdge(mapa[i][j], mapa[i - 1][j], level, leveln);
	}

	//desno
	if (j + 1 < cols && mapa[i][j + 1] != -1 && mapa[i + 1][j + 1] != -1)
	{
		level = 2;
		leveln = 2;
		addEdge(mapa[i][j], mapa[i][j + 1], level, leveln);
	}
	//levo
	if (j - 1 >= 0 && mapa[i][j - 1] != -1 && mapa[i + 1][j - 1] != -1)
	{
		level = 2;
		leveln = 2;
		addEdge(mapa[i][j], mapa[i][j - 1], level, leveln);
	}


	//sad state 3 --
	//gore
	if (i - 1 >= 0 && mapa[i - 1][j] != -1 && mapa[i - 1][j - 1] != -1)
	{
		level = 3;
		leveln = 3;
		addEdge(mapa[i][j], mapa[i - 1][j], level, leveln);
	}
	//dole
	if (i + 1 < rows && mapa[i + 1][j] != -1 && mapa[i + 1][j - 1] != -1)
	{
		level = 3;
		leveln = 3;
		addEdge(mapa[i][j], mapa[i + 1][j], level, leveln);
	}
	//desno
	if (j + 1 < cols && mapa[i][j + 1] != -1)
	{
		level = 3;
		leveln = 1;
		addEdge(mapa[i][j], mapa[i][j + 1], level, leveln);
	}
	//levo
	if (j - 1 >= 0 && mapa[i][j - 1] != -1)
	{
		level = 3;
		leveln = 1;
		addEdge(mapa[i][j], mapa[i][j - 2], level, leveln);
	}
}

void printGraph()
{

	printf("Mapa:\n\n");
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			printf("%d ", mapa[i][j]);
		}
		printf("\n");
	}
	printf("\n\n");

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			printf("%c ", map_string[i][j]);
		}
		printf("\n");
	}


	for (int k = 1; k <= 3; k++)
	{
		for (int i = 0; i < number_of_elements; i++)
		{
			for (int j = 0; j < number_of_elements; j++)
			{
				printf("%d ", matr[k][i][j]);
			}
			printf("\n");
		}
		printf("\n\n\n");
	}
}


int visited[4][100];

Bufer stigao[4][100];

void solve(int begRow, int begCol, int endRow, int endCol)
{
	int startNode = mapa[begRow][begCol];
	int endNode = mapa[endRow][endCol];

	int state = 1;

	put.kraj = 0;

	push(startNode, state);

	Bufer t;
	t.state = -1;
	t.value = -1;
	stigao[state][startNode] = t;

	char odg[1000];
	int cn = 0;

	while (!stack_empty())
	{
		Bufer node = pop();
		state = node.state;
		int value = node.value;

		if (state == 1 && endNode == value)
		{
			printf("NADJEN PUT!\n");
			int cnt = 0;


			/*  for (int j = 1; j <= 3; j++)
				{
					printf("State %d:\n", j);
					for (int i = 0; i < number_of_elements; i++)
					{
						printf("%d -> %d s: %d || ", i,stigao[j][i].value,stigao[j][i].state);
					}
					printf("\n");
				}
				*/
			state = 1;
			value = 29;
			//printf("%d", value);

			int prState, prValue = -1;
			while (1)
			{
				if (prValue != -1)
				{

					if (prState == 1 && state == 3)
					{
						if (prValue > value)
							odg[cn] = 'D';//    printf("D");
						else
							odg[cn] = 'L';  //printf("L");
					}
					else if (prState == 1 && state == 2)
					{
						if (prValue > value)
						{
							odg[cn] = 'S';  //printf("S");
						}
						else
							odg[cn] = 'W';  //printf("W");
					}
					else if (prState == 2 && state == 2)
					{
						if (prValue > value)
							odg[cn] = 'D';  //printf("D");
						else
							odg[cn] = 'L';  //printf("L");
					}
					else if (prState == 3 && state == 3)
					{
						if (prValue > value)
							odg[cn] = 'S';  //printf("S");
						else
							odg[cn] = 'W';  //printf("W");
					}
					else if (prState == 2 && state == 1)
					{
						if (prValue > value)
							odg[cn] = 'S';  //printf("S");
						else
							odg[cn] = 'W';  //printf("W");
					}
					else if (prState == 3 && state == 1)
					{
						if (prValue > value)
							odg[cn] = 'D';  //printf("D");
						else
							odg[cn] = 'L';  //printf("L");
					}
					cn++;
				}

				if (stigao[state][value].value == -1)
				{
					for (int i = cn - 1; i >= 0; i--)
						printf("%c", odg[i]);
					return;
				}


				//printf("%d %d\n", state, value);
				int pom = state;

				prState = state;
				prValue = value;

				state = stigao[state][value].state;
				value = stigao[pom][value].value;
				cnt++;
			}

			return;
		}

		//printf("%d\n", startNode);

		visited[state][value] = 1;


		for (int i = 0; i < number_of_elements; i++)
		{
			int go_state = matr[state][value][i];
			if (go_state != 0 && visited[go_state][i] == 0)
			{
				push(i, go_state);
				Bufer a;
				a.state = state;
				a.value = value;
				stigao[go_state][i] = a;
			}
		}

	}

}


void printMap()
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			printf("%c", map_string[i][j]);
		}
		printf("\n");
	}
}


void replaceX()
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (map_string[i][j] == 'x')
				map_string[i][j] = 'o';
		}
	}
}

void play(int begRow, int begCol, int endRow, int endCol)
{
	int currNode = mapa[begRow][begCol];
	int currState = 1;

	int row = begRow;
	int col = begCol;

	printMap();
	getchar();

	while (1)
	{
		char c;
		scanf("%c", &c);
		int ima = 0;
		getchar();

		int b = 0;
		if (currState == 1)
		{
			if (c == 'S')
			{
				//znaci mora da bude na vecoj poziciji od curr noda
				for (int i = 0; i < number_of_elements; i++)
				{
					if (matr[currState][currNode][i] == 2 && i > currNode)
					{
						currState = 2;
						currNode = i;
						row++;
						b = 1;
						break;
					}
				}
			}
			else if (c == 'W')
			{
				for (int i = 0; i < number_of_elements; i++)
				{
					if (matr[currState][currNode][i] == 2 && i < currNode)
					{
						currState = 2;
						currNode = i;
						row -= 2;
						b = 1;
						break;
					}
				}
			}
			else if (c == 'D')
			{
				for (int i = 0; i < number_of_elements; i++)
				{
					if (matr[currState][currNode][i] == 3 && i > currNode)
					{
						currState = 3;
						currNode = i;
						col += 2;
						b = 1;
						break;
					}
				}
			}
			else if (c == 'A')
			{
				for (int i = 0; i < number_of_elements; i++)
				{
					if (matr[currState][currNode][i] == 3 && i < currNode)
					{
						currState = 3;
						currNode = i;
						col--;
						b = 1;
						break;
					}
				}
			}
		}
		else if (currState == 2)
		{
			if (c == 'S')
			{
				//znaci mora da bude na vecoj poziciji od curr noda
				for (int i = 0; i < number_of_elements; i++)
				{
					if (matr[currState][currNode][i] == 1 && i > currNode)
					{
						currState = 1;
						currNode = i;
						row += 2;
						b = 1;
						break;
					}
				}
			}
			else if (c == 'W')
			{
				for (int i = 0; i < number_of_elements; i++)
				{
					if (matr[currState][currNode][i] == 1 && i < currNode)
					{
						currState = 1;
						currNode = i;
						row--;
						b = 1;
						break;
					}
				}
			}
			else if (c == 'D')
			{
				for (int i = 0; i < number_of_elements; i++)
				{
					if (matr[currState][currNode][i] == 2 && i > currNode)
					{
						currState = 2;
						currNode = i;
						col++;
						b = 1;
						break;
					}
				}
			}
			else if (c == 'A')
			{
				for (int i = 0; i < number_of_elements; i++)
				{
					if (matr[currState][currNode][i] == 2 && i < currNode)
					{
						currState = 2;
						currNode = i;
						col--;
						b = 1;
						break;
					}
				}
			}
		}
		else if (currState == 3)
		{
			if (c == 'S')
			{
				//znaci mora da bude na vecoj poziciji od curr noda
				for (int i = 0; i < number_of_elements; i++)
				{
					if (matr[currState][currNode][i] == 3 && i > currNode)
					{
						currState = 3;
						currNode = i;
						row++;
						b = 1;
						break;
					}
				}
			}
			else if (c == 'W')
			{
				for (int i = 0; i < number_of_elements; i++)
				{
					if (matr[currState][currNode][i] == 3 && i < currNode)
					{
						currState = 3;
						currNode = i;
						row--;
						b = 1;
						break;
					}
				}
			}
			else if (c == 'D')
			{
				for (int i = 0; i < number_of_elements; i++)
				{
					if (matr[currState][currNode][i] == 1 && i > currNode)
					{
						currState = 1;
						currNode = i;
						col++;
						b = 1;
						break;
					}
				}
			}
			else if (c == 'A')
			{
				for (int i = 0; i < number_of_elements; i++)
				{
					if (matr[currState][currNode][i] == 1 && i < currNode)
					{

						currState = 1;
						currNode = i;
						col -= 2;
						b = 1;
						break;
					}
				}
			}
		}

		if (b == 0)
		{
			printf(":(\n");
			return;
		}

		replaceX();

		if (currState == 1)
		{
			map_string[row][col] = 'x';
		}
		else if (currState == 2)
		{

			map_string[row][col] = 'x';
			map_string[row + 1][col] = 'x';
		}
		else if (currState == 3)
		{
			map_string[row][col] = 'x';
			map_string[row][col - 1] = 'x';
		}

		if (row == endRow && col == endCol && currState == 1)
		{
			printf("Pobeda!\n\n");
			return;
		}


		printf("Cvor je: %d\n", currNode);
		printf("State je: %d\n", currState);
		printMap();

	}
}


void menu()
{
	printf("-------------\n\n");
	printf("1 - Ispisi graf\n");
	printf("2 - Dodaj cvor\n");
	printf("3 - Nadji put\n");
	printf("4 - Igraj igru\n");
	printf("5 - Obrisi graf\n");
	printf("---------------\n");
}

void deleteGraph()
{
	for (int k = 1; k <= 3; k++)
	{
		for (int i = 0; i < number_of_elements; i++)
		{
			for (int j = 0; j < number_of_elements; j++)

				matr[k][i][j] = 0;
		}
	}

	number_of_elements = 0;

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			map_string[i][j] = '-';
		}
	}

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			mapa[i][j] = -1;
		}
	}

}

int main()
{
	s.kraj = 0;
	put.kraj = 0;
	memset(visited, 0, sizeof(visited));

	for (int i = 0; i < 3000; i++)
	{
		s.bufer[i].value = 0;
		s.bufer[i].state = 0;
	}
	memset(visited, 0, sizeof(visited));

	FILE *f = fopen("mapa.txt", "r");

	char c[100];


	int begrow, begcol;
	int endrow, endcol;
	mapa = calloc(1, sizeof(int*));
	while (1)
	{
		if (fscanf(f, "%s", c) == EOF)
			break;
		//printf("%s\n", c);
		int len = strlen(c);
		cols = len;
		mapa[rows] = calloc(len, sizeof(int));

		for (int i = 0; i < len; i++)
		{
			if (c[i] == 'S')
			{
				mapa[rows][i] = cnt++;
				begrow = rows;
				begcol = i;
			}
			else if (c[i] == 'T')
			{
				mapa[rows][i] = cnt++;
				endrow = rows;
				endcol = i;
			}
			else if (c[i] == 'o')
			{
				mapa[rows][i] = cnt++;
			}
			else
			{
				mapa[rows][i] = -1;
			}
		}

		rows++;
		mapa = realloc(mapa, (rows + 1) * sizeof(int*));
	}


	number_of_elements = 0;
	//pravimo matricu susednosti
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (mapa[i][j] != -1)
			{
				addNode();
			}
		}
	}

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (mapa[i][j] != -1)
			{

				int level, leveln;
				//odradimo prvo za 1. state tj kad je usparvno
				//gore
				if (i - 2 >= 0 && mapa[i - 2][j] != -1 && mapa[i - 1][j] != -1)
				{
					level = 1;
					leveln = 2;

					addEdge(mapa[i][j], mapa[i - 2][j], level, leveln);
				}
				// dole
				if (i + 2 < rows && mapa[i + 2][j] != -1 && mapa[i + 1][j] != -1)
				{
					level = 1;
					leveln = 2;
					addEdge(mapa[i][j], mapa[i + 1][j], level, leveln);
				}
				//desno
				if (j + 2 < cols && mapa[i][j + 2] != -1 && mapa[i][j + 1] != -1)
				{
					level = 1;
					leveln = 3;
					addEdge(mapa[i][j], mapa[i][j + 2], level, leveln);
				}
				//levo
				if (j - 2 >= 0 && mapa[i][j - 2] != -1 && mapa[i][j - 1] != -1)
				{
					level = 1;
					leveln = 3;
					addEdge(mapa[i][j], mapa[i][j - 1], level, leveln);
				}

				//sad kad je state 2 |
				//gore
				if (i - 1 >= 0 && mapa[i - 1][j] != -1)
				{
					level = 2;
					leveln = 1;
					addEdge(mapa[i][j], mapa[i - 1][j], level, leveln);
				}

				//dole

				if (i - 2 >= 0 && mapa[i - 2][j] != -1)
				{
					level = 2;
					leveln = 1;
					addEdge(mapa[i][j], mapa[i - 1][j], level, leveln);
				}

				//desno
				if (j + 1 < cols && mapa[i][j + 1] != -1 && mapa[i + 1][j + 1] != -1)
				{
					level = 2;
					leveln = 2;
					addEdge(mapa[i][j], mapa[i][j + 1], level, leveln);
				}
				//levo
				if (j - 1 >= 0 && mapa[i][j - 1] != -1 && mapa[i + 1][j - 1] != -1)
				{
					level = 2;
					leveln = 2;
					addEdge(mapa[i][j], mapa[i][j - 1], level, leveln);
				}


				//sad state 3 --
				//gore
				if (i - 1 >= 0 && mapa[i - 1][j] != -1 && mapa[i - 1][j - 1] != -1)
				{
					level = 3;
					leveln = 3;
					addEdge(mapa[i][j], mapa[i - 1][j], level, leveln);
				}
				//dole
				if (i + 1 < rows && mapa[i + 1][j] != -1 && mapa[i + 1][j - 1] != -1)
				{
					level = 3;
					leveln = 3;
					addEdge(mapa[i][j], mapa[i + 1][j], level, leveln);
				}
				//desno
				if (j + 1 < cols && mapa[i][j + 1] != -1)
				{
					level = 3;
					leveln = 1;
					addEdge(mapa[i][j], mapa[i][j + 1], level, leveln);
				}
				//levo
				if (j - 1 >= 0 && mapa[i][j - 1] != -1)
				{
					level = 3;
					leveln = 1;
					addEdge(mapa[i][j], mapa[i][j - 2], level, leveln);
				}
			}
		}
	}

	int rw = begrow;
	int cl = begcol;

	map_string = calloc(number_of_elements + 1, sizeof(char*));
	for (int i = 0; i < number_of_elements; i++)
	{
		map_string[i] = calloc(number_of_elements + 1, sizeof(char));
	}

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (mapa[i][j] != -1)
			{
				if (rw == i && cl == j)
					map_string[i][j] = 'x';
				else if (i == endrow && j == endcol)
					map_string[i][j] = 'T';
				else
					map_string[i][j] = 'o';
			}
			else
			{
				map_string[i][j] = '-';
			}
		}
	}


	//play(begrow, begcol, endrow, endcol);

	while (1)
	{

		menu();

		int m;
		scanf("%d", &m);



		if (m == 1)
		{
			printGraph();
		}
		else if (m == 2)
		{
			printf("Unesite red i kolonu\n");
			int rr, cc;
			scanf("%d%d", &rr, &cc);
			addNode();
			addEdgeROWnCOL(rr, cc);
		}
		else if (m == 3)
		{
			solve(begrow, begcol, endrow, endcol);
		}
		else if (m == 4)
		{
			play(begrow, begcol, endrow, endcol);
		}
		else if (m == 5)
		{
			deleteGraph();
		}
		else
		{
			printf("Pogresna vrednost\n");
		}

	}
	return 0;
}