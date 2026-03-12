/**
 * Funções principais do programa.
 * Cada Lote tem um numero de identificação, nome da vacina e data de validade.
 * @file: principais.h
 * @author: ist1113868 (Guilherme Marques)
 */



/**< inclui as restantes funções, estruturas e constantes*/
#include "auxiliares.h"



/** Função que cria o lote e armazena-o no sistema.
 *  @param sys estrutura do sistema.
 *  @param in input do utilizador.
 */
void cria_lote(Sys *sys, char *in);



/** Função que lista os lotes de vacinas.
 *  @param sys estrutura do sistema.
 *  @param in input do utilizador.
 */
void lista_lote(Sys *sys, char *in);



/** Função que lista os lotes de vacinas.
 *  @param sys estrutura do sistema.
 *  @param in input do utilizador.
 */
void muda_tempo(Sys *sys, char *in);



/** Função que aplica a vacina ao paciente.
 *  @param sys estrutura do sistema.
 *  @param in input do utilizador.
 */
void aplica_vacina(Sys *sys, char *in);



/** Função que remove um lote do sistema, ou as vacinas de um lote.
 *  @param sys estrutura do sistema.
 *  @param in input do utilizador.
 */
void remove_lote(Sys *sys, char *in);



/** Função que lista as inoculações.
 *  @param sys estrutura do sistema.
 *  @param in input do utilizador.
 */
void lista_inoculacoes(Sys *sys, char *in);



/** Função que remove uma inoculação do sistema.
 *  @param sys estrutura do sistema.
 *  @param in input do utilizador.
 */
void remove_inoculacao(Sys *sys, char *in);