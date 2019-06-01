/*
 * main.c
 */
#include "main.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
	openFile(argv[1]);
}

void openFile(char *nf) {
	FILE *file = fopen(nf, "r");
	if (!file) {
		printf("Erro abrir ficheiro\n");
		return;
	}
	ushort **sudoku = calloc(9, sizeof(ushort *));
	for (ushort i = 0; i < 9; i++) {
		sudoku[i] = calloc(9, sizeof(ushort));
	}
	char buf[256];
	while (!feof(file)) {
		fgets(buf, 256, file);
		for (ushort i = 0, row = 0, col = 0; i < strlen(buf) && row < 9 && col < 9; i++) {
			sudoku[row][col++] = buf[i] - '0';
			if (col == 9) {
				row++;
				col = 0;
			}
		}

		for (ushort row = 0; row < 9; row++) {
			if (row % 3 == 0) {
				printf("+-----+-----+-----+\n");
			}
			for (ushort col = 0; col < 9; col++) {
				printf("|%hu", sudoku[row][col]);
			}
			printf("|\n");
		}
		printf("+-----+-----+-----+\n");

		if (resolveSudoku(sudoku, 0, 0)) {
			for (ushort row = 0; row < 9; row++) {
				if (row % 3 == 0) {
					printf("+-----+-----+-----+\n");
				}
				for (ushort col = 0; col < 9; col++) {
					printf("|%hu", sudoku[row][col]);
				}
				printf("|\n");
			}
			printf("+-----+-----+-----+\n");
		} else {
			printf("Sudoku impossivel\n");
		}

	}

	for (ushort i = 0; i < 9; i++) {
		free(sudoku[i]);
	}
	free(sudoku);
	fclose(file);
}

ushort numeroDisponivel(ushort **sudoku, ushort row, ushort col, ushort numero) {
	ushort rowStart, colStart;
	// Definir os limites da linha para a regra do quadrado
	if (row >= 0 && row <= 2) {
		rowStart = 0;
	} else if (row >= 3 && row <= 5) {
		rowStart = 3;
	} else {
		rowStart = 6;
	}
	// Definir os limites da coluna para a regra do quadrado
	if (col >= 0 && col <= 2) {
		colStart = 0;
	} else if (col >= 3 && col <= 5) {
		colStart = 3;
	} else {
		colStart = 6;
	}
	for (ushort i = 0; i < 9; i++) {
		// Aplicar regra linha
		if (sudoku[row][i] == numero) {
			return 0;
		}
		// Aplicar regra da coluna
		if (sudoku[i][col] == numero) {
			return 0;
		}
		// Aplicar regra do quadrado
		if (sudoku[rowStart + (i % 3)][colStart + (i / 3)] == numero) {
			return 0;
		}
	}
	return 1;
}

ushort resolveSudoku(ushort **sudoku, ushort row, ushort col) {
	if (sudoku[row][col] == 0) {
		// Estamos perante elemento vazio
		for (ushort numero = 1; numero < 10; numero++) {
			if (numeroDisponivel(sudoku, row, col, numero)) {
				sudoku[row][col] = numero;
				// Procuro em profundidade todas as hipoteses com este numero
				printf("[%hu][%hu]%hu\n", row, col, numero);
				if (resolveSudoku(sudoku, row, col)) {
					// Encontrei uma solução com este valor
					return 1;
				}
				// Não encontrei solução
				sudoku[row][col] = 0;
			}
		}
		// Sudoku impossivel
		return 0;
	} else {
		// Estamos perante um elemento já preenchido
		if (col < 8) {
			// Procuramos primeiro todas as colunas
			return resolveSudoku(sudoku, row, col + 1);
		} else if (row < 8) {
			// Avançamos a linha quando chegarmos ao fim da coluna
			return resolveSudoku(sudoku, row + 1, 0);
		}
	}
	return 1;
}


