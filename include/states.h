/* @name STATES
* @author @walger-lucas
* @date 30/04/2024
* @paragraph Interface com a state_machine
*/

#pragma once
#include <Arduino.h>
#include <movements.h>

/* baseState
* @brief função que chama as funcionalidades de um estado do micromouse, como a de leitura de entradas e execução de tarefas
* @return void
* @date alterações:
*   - 01/05/2024: criado comentário, começado a documentar. - @walger-lucas
*/
extern void (*baseState) ();

/* executionAlgorithm
* @brief Função chamada a todo fim de operação de movimento, deve chamar uma nova operação internamente. Utilizada quando o modo de operação é o de execução
* @return True se não há novos movimentos, execução terminada
* @date alterações:
*   - 01/05/2024: criado comentário, começado a documentar. - @walger-lucas
*/
bool executionAlgorithm();

/* floodfillAlgorithm
* @brief Função chamada a todo fim de operação de movimento, deve chamar uma nova operação internamente. Utilizada na busca de competição.
* @return True se não há novos movimentos, execução terminada
* @date alterações:
*   - 01/05/2024: criado comentário, começado a documentar. - @walger-lucas
*/
bool floodfillSearch();
/* dfsAlgorithm
* @brief Função chamada a todo fim de operação de movimento, deve chamar uma nova operação internamente. Utilizada na busca de dfs.
* @return True se não há novos movimentos, execução terminada
* @date alterações:
*   - 01/05/2024: criado comentário, começado a documentar. - @walger-lucas
*/
bool dfsSearch();
/* bfsAlgorithm
* @brief Função chamada a todo fim de operação de movimento, deve chamar uma nova operação internamente. Utilizada na busca de bfs.
* @return True se não há novos movimentos, execução terminada
* @date alterações:
*   - 01/05/2024: criado comentário, começado a documentar. - @walger-lucas
*/
bool bfsSearch();