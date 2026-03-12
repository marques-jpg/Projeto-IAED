/**
 * Funções auxiliares do programa.
 * Cada Lote tem um numero de identificação, nome da vacina e data de validade.
 * @file: auxiliares.c
 * @author: ist1113868 (Guilherme Marques)
 */



/**<inclui as restantes funções, estruturas e constantes.*/
#include "auxiliares.h"



/** Verifica se a data fornecida é válida.
 *  @return 1 se a data for válida, 0 caso contrário.
 *  @param d dia.
 *  @param m mês.
 *  @param a ano.
 *  @param ds data do sistema.
 */
int verifica_data(int d, int m, int a, Data_sistema ds) {
    int dm[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (m < 1 || m > 12 || d < 1 || a < ds.ano || 
        (a == ds.ano && (m < ds.mes || (m == ds.mes && d < ds.dia)))) return 0;
    if (m == 2 && ((a % 4 == 0 && a % 100 != 0) || (a % 400 == 0))) dm[1] = 29;
    return d <= dm[m - 1];
}



/** Imprime os dados do lote.
 *  @param v Lote a imprimir.
 *  @param c Número de aplicações.
 */
void print_lote(Lote v, int c) {
    printf("%s %s %02hu-%02hu-%04hu %d %d\n", v.nome_vacina_lote, v.nome_lote, 
           v.data.dia, v.data.mes, v.data.ano, v.nmr_vacina, c);
}



/** Ordena os lotes por data e nome.
 *  @param lotes Array de lotes a ordenar.
 *  @param n Número de lotes.
 */
void ordena_lotes(Lote *lotes, int n) {
    for (int i = 1; i < n; i++) {
        Lote temp = lotes[i];
        int j = i - 1;
        while (j >= 0 && (lotes[j].data.ano > temp.data.ano ||
            (lotes[j].data.ano == temp.data.ano && 
            (lotes[j].data.mes > temp.data.mes || 
            (lotes[j].data.mes == temp.data.mes && 
            (lotes[j].data.dia > temp.data.dia || 
            (lotes[j].data.dia == temp.data.dia && 
            strcmp(lotes[j].nome_lote, temp.nome_lote) > 0))))))) {
            lotes[j + 1] = lotes[j];
            j--;
        }
        lotes[j + 1] = temp;
    }
}



/**
 * Função auxiliar que encontra o índice de um lote válido para aplicação.
 * @param sys estrutura do sistema.
 * @param nome_vacina nome da vacina a ser aplicada.
 * @return índice do lote válido ou -1 se nenhum lote for encontrado.
 */
int encontra_lote_valido(Sys *sys, const char *nome_vacina) {
    int lote_index = -1;
    for (int i = 0; i < sys->cnt; i++) {
        if (strcmp(sys->vacina[i].nome_vacina_lote, nome_vacina) == 0 &&
            sys->vacina[i].nmr_vacina > 0 &&
            (sys->vacina[i].data.ano > sys->data_sistema.ano ||
            (sys->vacina[i].data.ano == sys->data_sistema.ano && 
                sys->vacina[i].data.mes > sys->data_sistema.mes) ||
            (sys->vacina[i].data.ano == sys->data_sistema.ano && 
                sys->vacina[i].data.mes == sys->data_sistema.mes && 
                sys->vacina[i].data.dia >= sys->data_sistema.dia))) {
            if (lote_index == -1 || 
                sys->vacina[i].data.ano < sys->vacina[lote_index].data.ano ||
                (sys->vacina[i].data.ano == sys->vacina[lote_index].data.ano && 
                sys->vacina[i].data.mes < sys->vacina[lote_index].data.mes) ||
                (sys->vacina[i].data.ano == sys->vacina[lote_index].data.ano && 
                sys->vacina[i].data.mes == sys->vacina[lote_index].data.mes && 
                sys->vacina[i].data.dia < sys->vacina[lote_index].data.dia)) {
                lote_index = i;
            }
        }
    }
    return lote_index;
}



/**
 * Função auxiliar que verifica se o paciente já foi vacinado no mesmo dia.
 * @param sys estrutura do sistema.
 * @param nome_paciente nome do paciente.
 * @param nome_vacina nome da vacina.
 * @return 1 se o paciente já foi vacinado no mesmo dia, 0 caso contrário.
 */
int verifica_vacinacao_no_dia(Sys *sys, const char *nome_paciente, 
                              const char *nome_vacina) {
    for (int i = 0; i < sys->num_inoculacoes; i++) {
        if (strcmp(sys->inoculacao[i].nome_paciente, nome_paciente) == 0 &&
            strcmp(sys->inoculacao[i].nome_vacina, nome_vacina) == 0 &&
            sys->inoculacao[i].data_inoculacao.dia == sys->data_sistema.dia &&
            sys->inoculacao[i].data_inoculacao.mes == sys->data_sistema.mes &&
            sys->inoculacao[i].data_inoculacao.ano == sys->data_sistema.ano) {
            return 1; // Paciente já vacinado no mesmo dia
        }
    }
    return 0; // Paciente ainda não foi vacinado no mesmo dia
}



/**
 * Função auxiliar que realoca memória para o array de inoculações.
 * @param sys estrutura do sistema.
 * @return 1 se a realocação foi bem-sucedida, 0 caso contrário.
 */
int realoca_inoculacoes(Sys *sys) {
    sys->cap_inoculacoes += 500;
    sys->inoculacao = (Inoculacao *)realloc(sys->inoculacao, 
                                    sys->cap_inoculacoes * sizeof(Inoculacao));
    if (sys->inoculacao == NULL) {
        fprintf(stderr, "Erro ao alocar memória para inoculacoes\n");
        return 0; // Falha na realocação
    }
    return 1; // Sucesso na realocação
}



/**
 * Função auxiliar que aplica a vacina e armazena a inoculação no sistema.
 * @param sys estrutura do sistema.
 * @param nome_paciente nome do paciente.
 * @param nome_vacina nome da vacina.
 * @param lote_index índice do lote válido.
 */
void aplica_inoculacao(Sys *sys, const char *nome_paciente, 
                       const char *nome_vacina, int lote_index) {
    sys->vacina[lote_index].nmr_vacina--;
    sys->inoculacao[sys->num_inoculacoes].nome_paciente = strdup(nome_paciente);
    sys->inoculacao[sys->num_inoculacoes].nome_vacina = strdup(nome_vacina);
    strcpy(sys->inoculacao[sys->num_inoculacoes].nome_lote, 
           sys->vacina[lote_index].nome_lote);
    sys->inoculacao[sys->num_inoculacoes].data_inoculacao.dia = sys->data_sistema.dia;
    sys->inoculacao[sys->num_inoculacoes].data_inoculacao.mes = sys->data_sistema.mes;
    sys->inoculacao[sys->num_inoculacoes].data_inoculacao.ano = sys->data_sistema.ano;
    sys->vacina[lote_index].num_aplicacoes++;
    sys->num_inoculacoes++;
    printf("%s\n", sys->vacina[lote_index].nome_lote);
}



/**
 * Função auxiliar que lista todas as inoculações registradas no sistema.
 * @param sys estrutura do sistema.
 */
void lista_todas_inoculacoes(Sys *sys) {
    for (int i = 0; i < sys->num_inoculacoes; i++) {
        printf("%s %s %02hu-%02hu-%04hu\n", 
               sys->inoculacao[i].nome_paciente, 
               sys->inoculacao[i].nome_lote, 
               sys->inoculacao[i].data_inoculacao.dia, 
               sys->inoculacao[i].data_inoculacao.mes, 
               sys->inoculacao[i].data_inoculacao.ano);
    }
}



/**
 * Função auxiliar que valida o nome do lote.
 * @param nome_lote nome do lote a ser validado.
 * @param idioma_pt flag para idioma (1 para PT, 0 para EN).
 * @return 1 se o nome do lote for válido, 0 caso contrário.
 */
int valida_nome_lote(const char *nome_lote, int idioma_pt) {
    for (size_t i = 0; i < strlen(nome_lote); i++) {
        if (!isxdigit(nome_lote[i]) || (isalpha(nome_lote[i]) && 
            !isupper(nome_lote[i]))) {
            puts(idioma_pt ? ENOMELOTEINVALIDO_PT : ENOMELOTEINVALIDO_EN);
            return 0;
        }
    }
    return 1;
}



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
    char *nome_vacina_lote, unsigned short *dia, unsigned short *mes, 
    unsigned short *ano, int *nmr_vacina) {
    if (sscanf(in, "%*s %s %hu-%hu-%hu %d %s", nome_lote, dia, mes, 
        ano, nmr_vacina, nome_vacina_lote) != 6) {
        puts(sys->idioma_pt ? EINVALIDO_PT : EINVALIDO_EN);
        return 0;
    }
    if (!verifica_data(*dia, *mes, *ano, sys->data_sistema)) {
        puts(sys->idioma_pt ? EDATAINVALIDA_PT : EDATAINVALIDA_EN);
        return 0;
    }
    for (int i = 0; i < sys->cnt; i++) {
        if (!(strcmp(nome_lote, sys->vacina[i].nome_lote))) {
            puts(sys->idioma_pt ? ELOTEDUPLICADO_PT : ELOTEDUPLICADO_EN);
            return 0;
        }
    }
    if (strlen(nome_vacina_lote) >= MAXNOMEDOENCA) {
        puts(sys->idioma_pt ? ENOMEINVALIDO_PT : ENOMEINVALIDO_EN);
        return 0;
    }
    if (sys->cnt >= MAXLOTES) {
        puts(sys->idioma_pt ? EEXCESSOLOTE_PT : EEXCESSOLOTE_EN);
        return 0;
    }
    if (*nmr_vacina < 0) {
        puts(sys->idioma_pt ? EQUANTIDADEINVALIDA_PT : EQUANTIDADEINVALIDA_EN);
        return 0;
    }
    if (strlen(nome_lote) >= MAXNOMELOTE) {
        puts(sys->idioma_pt ? ENOMELOTEINVALIDO_PT : ENOMELOTEINVALIDO_EN);
        return 0;
    }
    if (!valida_nome_lote(nome_lote, sys->idioma_pt)) {
        return 0;
    }
    return 1;
}