/*
 * main.h
 */

#ifndef MAIN_H_
#define MAIN_H_

typedef unsigned short ushort;

/**
 * Lê o ficheiro que contém o sudoku
 * @param *nf contém o ponteiro para o nome do fichero (passado por argumento)
 */
void openFile(char *nf);

/**
 * Aplica as regras da linha, coluna e quadrado respetivamente dado um número
 * @param **sudoku contém a matriz correspondente ao array
 * @param row contém a linha em que a tentativa de número se encontra
 * @param col contém a coluna em que a tentativa de número se encontra
 * @param numero contém o número que queremos avaliar a disponibilidade
 * @return 0 caso o número não possa ser usado para o sudoku, 1 caso contrário
 */
ushort numeroDisponivel(ushort **sudoku, ushort row, ushort col, ushort numero);

/**
 * Pesquisa recursivamente e em profundidade as possibilidades de resolução do sudoku
 * @param **sudoku contém a matriz correspondente ao array
 * @param row contém a linha em que nos encontramos atualmente
 * @param col contém a coluna em que nos encontramos atualmente
 * @return 0 caso a solução não seja possível, 1 caso assim que encontrar uma solução
 */
ushort resolveSudoku(ushort **sudoku, ushort row, ushort col);

#endif /* MAIN_H_ */
