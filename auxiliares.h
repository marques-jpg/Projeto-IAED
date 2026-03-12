/**
 * Funções auxiliares do programa.
 * Cada Lote tem um numero de identificação, nome da vacina e data de validade.
 * @file: auxiliares.h
 * @author: ist1113868 (Guilherme Marques)
 */



/**<inclui as restantes funções, estruturas e constantes.*/
#include "structs.h"



/** Verifica se a data fornecida é válida.
 *  @return 1 se a data for válida, 0 caso contrário.
 *  @param d dia.
 *  @param m mês.
 *  @param a ano.
 *  @param ds data do sistema.
 */int verifica_data(int dia, int mes, int ano, Data_sistema data_sistema);



/** Imprime os dados do lote.
 * @param v Lote a imprimir.
 * @param c Número de aplicações.
 */void print_lote(Lote vacina, int cnt_aplicacoes);


 
/**
 * Ordena os lotes por data e nome.
 * @param lotes Array de lotes a ordenar.
 * @param n Número de lotes.
 */void ordena_lotes(Lote *lotes, int n);



 /**
 * Função auxiliar que encontra o índice de um lote válido para aplicação.
 * @param sys estrutura do sistema.
 * @param nome_vacina nome da vacina a ser aplicada.
 * @return índice do lote válido ou -1 se nenhum lote for encontrado.
 */
 int encontra_lote_valido(Sys *sys, const char *nome_vacina);


/**
 * Função auxiliar que verifica se o paciente já foi vacinado no mesmo dia.
 * @param sys estrutura do sistema.
 * @param nome_paciente nome do paciente.
 * @param nome_vacina nome da vacina.
 * @return 1 se o paciente já foi vacinado no mesmo dia, 0 caso contrário.
 */
 int verifica_vacinacao_no_dia(Sys *sys, const char *nome_paciente, 
                               const char *nome_vacina);


/**
 * Função auxiliar que realoca memória para o array de inoculações.
 * @param sys estrutura do sistema.
 * @return 1 se a realocação foi bem-sucedida, 0 caso contrário.
 */
 int realoca_inoculacoes(Sys *sys);


/**
 * Função auxiliar que aplica a vacina e armazena a inoculação no sistema.
 * @param sys estrutura do sistema.
 * @param nome_paciente nome do paciente.
 * @param nome_vacina nome da vacina.
 * @param lote_index índice do lote válido.
 */
 void aplica_inoculacao(Sys *sys, const char *nome_paciente, 
                        const char *nome_vacina, 
                        int lote_index);


/**
 * Função auxiliar que lista todas as inoculações registradas no sistema.
 * @param sys estrutura do sistema.
 */
 void lista_todas_inoculacoes(Sys *sys);


/**
 * Função auxiliar que valida o nome do lote.
 * @param nome_lote nome do lote a ser validado.
 * @param idioma_pt flag para idioma (1 para PT, 0 para EN).
 * @return 1 se o nome do lote for válido, 0 caso contrário.
 */
 int valida_nome_lote(const char *nome_lote, int idioma_pt);



/**
 * Função auxiliar que verifica e processa os dados do lote.
 * @param sys estrutura do sistema.
 * @param in input do utilizador.
 * @param nome_lote buffer para armazenar o nome do lote.
 * @param nome_vacina_lote buffer para armazenar o nome da vacina no lote.
 * @param dia ponteiro para armazenar o dia de validade do lote.
 * @param mes ponteiro para armazenar o mês de validade do lote.
 * @param ano ponteiro para armazenar o ano de validade do lote.
 * @param nmr_vacina ponteiro para armazenar o número de vacinas no lote.
 * @return 1 se os dados forem válidos, 0 caso contrário.
 */
 int verifica_e_processa_lote(Sys *sys, const char *in, char *nome_lote, 
                    char *nome_vacina_lote, unsigned short *dia, 
                    unsigned short *mes, unsigned short *ano, int *nmr_vacina);

