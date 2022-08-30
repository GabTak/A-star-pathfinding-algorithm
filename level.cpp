//======================================================================================
//Source code for cLevel class
//======================================================================================
#include "level.h"
#include "bots.h"
#include <stdio.h>

//======================================================================================
//Globals
//======================================================================================
cLevel gLevel;

//======================================================================================
//Valid if in range and position is traversable
//======================================================================================

bool cLevel::isValid(int x, int y) const
{ 
	if ((x < 0) || (x > 39)) return false; 
	if ((y < 0) || (y > 39)) return false;
	int m = map[x][y];
	if(m != 0) return false;
	return true;
}

//======================================================================================
//Constructor
//======================================================================================
cLevel::cLevel()
{
	for (int i = 0; i < GRIDHEIGHT; i++)
	{
		for (int j = 0; j < GRIDWIDTH; j++)
		{
			map[i][j] = 0;
		}
	}
}

//======================================================================================
//Load map from ascii text file
//======================================================================================
void cLevel::Load(const char* fname)
{
	for (int i = 0; i < GRIDHEIGHT; i++)
	{
		for (int j = 0; j < GRIDWIDTH; j++)
		{
			map[i][j] = 0;
		}
	}
	FILE *file = fopen(fname,"rt");
	for (int j = 0; j < GRIDHEIGHT; j++)
	{
		char line[128];
		fread(line, 1, 41, file);
		for (int i = 0; i < GRIDWIDTH; i++)
		{
			if(line[i]=='#') map[i][j] = 1;
			else map[i][j] = 0;
		}
	}
	fclose(file);
}

//======================================================================================
//Draw grid
//======================================================================================
void cLevel::Draw(void)
{
	SDL_Rect position;
	position.h = position.w = 16;

	for (int i = 0; i < GRIDHEIGHT; i++)
	{
		for (int j = 0; j < GRIDWIDTH; j++)
		{
			position.x = i * 16;
			position.y = j * 16;


			if (map[i][j] == 0)
			{
				SDL_RenderCopy(gMainRenderer, tileTexture, NULL, &position);

				//Manhattan
				if (gAStar.completed)
				{
					SDL_RenderCopy(gMainRenderer, tileTexture, NULL, &position);
					if (gAStar.inPath[i][j] == true)
					{
						SDL_RenderCopy(gMainRenderer, tileRouteTexture, NULL, &position);
					}
					else if ((gAStar.completed) && (gAStar.closed[i][j] == true))
					{
						SDL_RenderCopy(gMainRenderer, tileClosedTexture, NULL, &position);
					}
					else SDL_RenderCopy(gMainRenderer, tileTexture, NULL, &position);
				}

				//Euclidean

				if (gAStar_euclidean.completed)
				{
					SDL_RenderCopy(gMainRenderer, tileTexture, NULL, &position);
					if (gAStar_euclidean.inPath[i][j] == true)
					{
						SDL_RenderCopy(gMainRenderer, tileRouteTexture, NULL, &position);
					}
					else if ((gAStar_euclidean.completed) && (gAStar_euclidean.closed[i][j] == true))
					{
						SDL_RenderCopy(gMainRenderer, tileClosedTexture, NULL, &position);
					}
					else SDL_RenderCopy(gMainRenderer, tileTexture, NULL, &position);
				}


				//Diagonal

				if (gAStar_diagonal.completed)
				{
					SDL_RenderCopy(gMainRenderer, tileTexture, NULL, &position);
					if (gAStar_diagonal.inPath[i][j] == true)
					{
						SDL_RenderCopy(gMainRenderer, tileRouteTexture, NULL, &position);
					}
					else if ((gAStar_diagonal.completed) && (gAStar_diagonal.closed[i][j] == true))
					{
						SDL_RenderCopy(gMainRenderer, tileClosedTexture, NULL, &position);
					}
					else SDL_RenderCopy(gMainRenderer, tileTexture, NULL, &position);
				}

				
			}
			else SDL_RenderCopy(gMainRenderer, tileBlockedTexture, NULL, &position);
		}
	}
}