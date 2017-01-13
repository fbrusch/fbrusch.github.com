
#include "stdafx.h"
#include "Math.h"

#define dim 9

void stampa(int mat[dim][dim])
{
	for (size_t i = 0; i < dim; i++)
	{
		if (i % (int)sqrt((double)dim) == 0)
			printf("\n\n\n");
		for (size_t j = 0; j < dim; j++)
		{
			if (j % (int)sqrt((double)dim) == 0)
				printf("\t");
			printf("%d\t", mat[i][j]);
		}
		printf("\n\n");
	}
}

int colonna_corretta(int mat[dim][dim], int k)
{
	for (size_t i = 0; i < dim; i++)
	{
		for (size_t j = 0; j < dim; j++)
		{
			if (mat[i][k] == mat[j][k] && mat[i][k]>0 && j != i)
				return 0;
		}
	}
	return 1;
}

int riga_corretta(int mat[dim][dim], int k)
{
	for (size_t i = 0; i < dim; i++)
	{
		for (size_t j = 0; j < dim; j++)
		{
			if (mat[k][i] == mat[k][j] && mat[k][i]>0 && j != i){ return 0; }
		}
	}
	return 1;
}

int individua_quadrotto(int x, int y)
{
	int n = x / (int)sqrt((double)dim) + ((int)y / (int)sqrt((double)dim))*(int)sqrt((double)dim);
	return n;
}

int quadrotto_corretto(int mat[dim][dim], int k)
{
	int array[dim], l = 0;
	for (size_t i = 0; i < dim; i++)
	{
		for (size_t j = 0; j < dim; j++)
		{
			if (individua_quadrotto(j, i) == k)
			{
				array[l] = mat[i][j]; l++;
			}
		}
	}

	for (size_t i = 0; i < dim; i++)
	{
		for (size_t j = 0; j < dim; j++)
		{
			if (array[i] == array[j] && j != i && array[i] != 0) return 0;
		}
	}
	return 1;
}


int risolto(int mat[dim][dim]){
	for (size_t i = 0; i < dim; i++)
	{
		for (size_t j = 0; j < dim; j++)
		{
			if (mat[i][j] == 0)
				return 0;
		}
	}
	return 1;
}

int concesso(int mat[dim][dim], int n, int x, int y)
{
	int c = mat[y][x];
	mat[y][x] = n;
	if ((riga_corretta(mat, y) == 1) && (colonna_corretta(mat, x) == 1) && quadrotto_corretto(mat, individua_quadrotto(x, y)))
		return 1;
	mat[y][x] = c;
	return 0;
}

void matCopy(const int m1[dim][dim], int m2[dim][dim]){
	for (size_t i = 0; i < dim; i++)
	{
		for (size_t j = 0; j < dim; j++)
		{
			m2[i][j] = m1[i][j];
		}
	}
}

void risolvi(int mat[dim][dim], int x, int y){

	int itemMat[dim][dim];

	matCopy(mat, itemMat);

	if (x >= dim){ x = 0; y++; }

	if (mat[y][x] != 0)return risolvi(mat, x + 1, y);

	else{
		for (int i = 1; i <= dim && y<dim; i++)
		{
			if (risolto(mat) != 1)
			{
				matCopy(itemMat, mat);
				if (concesso(mat, i, x, y) == 1)
					risolvi(mat, x + 1, y);
			}
		}
	}
}


int _tmain(int argc, _TCHAR* argv[])
{
	/*int mat[dim][dim] = {
	{ 3, 4, 1, 0 },
	{ 0, 2, 0, 0 },
	{ 0, 0, 2, 0 },
	{ 0, 1, 4, 3 } };*/

	int mat[dim][dim] = {
		{ 0, 0, 7, 9, 6, 2, 4, 0, 0 },
		{ 9, 0, 0, 0, 1, 0, 0, 0, 2 },
		{ 0, 1, 0, 8, 5, 3, 0, 6, 0 },
		{ 5, 0, 0, 4, 7, 9, 0, 0, 1 },
		{ 0, 0, 0, 0, 8, 0, 0, 0, 0 },
		{ 4, 0, 0, 3, 2, 1, 0, 0, 7 },
		{ 0, 9, 0, 2, 4, 8, 0, 5, 0 },
		{ 6, 0, 0, 0, 3, 0, 0, 0, 8 },
		{ 0, 0, 8, 6, 9, 5, 1, 0, 0 } };


	risolvi(mat, 0, 0);
	stampa(mat);

	return 0;
}
