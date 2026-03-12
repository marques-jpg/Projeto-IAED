/**
 * Funções principais do programa.
 * Cada Lote tem um numero de identificação, nome da vacina e data de validade.
 * @file: principais.c
 * @author: ist1113868 (Guilherme Marques)
 */



/**< inclui as restantes funções, estruturas e constantes*/
#include "principais.h"



/** Função que cria o lote e armazena-o no sistema.
 *  @param sys estrutura do sistema.
 *  @param in input do utilizador.
 */
void cria_lote(Sys *sys, char *in) {
    char nome_lote[MAXLOTES] = {0};
    char nome_vacina_lote[MAXLOTES] = {0};
    int nmr_vacina = 0;
    unsigned short dia = 0, mes = 0, ano = 0;
    /**< Verificação e processamento dos dados do lote. */
    if (!verifica_e_processa_lote(sys, in, nome_lote, nome_vacina_lote, 
                                  &dia, &mes, &ano, &nmr_vacina)) {
        return;
    }
    /**<Alocação dos dados no sistema.*/
    strncpy(sys->vacina[sys->cnt].nome_lote, nome_lote, MAXLOTES);
    sys->vacina[sys->cnt].data.dia = dia;
    sys->vacina[sys->cnt].data.mes = mes;
    sys->vacina[sys->cnt].data.ano = ano;
    sys->vacina[sys->cnt].nmr_vacina = nmr_vacina;
    strncpy(sys->vacina[sys->cnt].nome_vacina_lote, nome_vacina_lote, MAXLOTES);
    sys->cnt++;    printf("%s\n", nome_lote);
}



/** Função que lista os lotes de vacinas.
 *  @param sys estrutura do sistema.
 *  @param in input do utilizador.
 */
void lista_lote(Sys *sys, char *in) {
    if (in[strlen(in) - 1] == '\n') in[strlen(in) - 1] = '\0';
    /**<Inicialização do token dividido por um espaço.*/
    char *token = strtok(in, " ");
    /**<Caso a função seja chamada apenas por 'u'.*/
    if (!(token = strtok(NULL, " "))) {
        ordena_lotes(sys->vacina, sys->cnt);
        for (int i = 0; i < sys->cnt; i++) 
            print_lote(sys->vacina[i], sys->vacina[i].num_aplicacoes);
        return;
    }
    /**<Caso a função seja chamada com vários termos.*/
    Lote *filtrado = malloc(sys->cnt * sizeof(Lote));
    if (!filtrado) return;
    while (token) {
        int contador = 0;
        for (int i = 0; i < sys->cnt; i++) 
            if (!strcmp(sys->vacina[i].nome_vacina_lote, token)) 
                filtrado[contador++] = sys->vacina[i];
        if (contador) {
            ordena_lotes(filtrado, contador);
            for (int i = 0; i < contador; i++) 
                print_lote(filtrado[i], filtrado[i].num_aplicacoes);
        } else 
            printf("%s: %s\n", token, sys->idioma_pt ? 
                   ESEMVACINA_PT : ESEMVACINA_EN);
        token = strtok(NULL, " ");
    }
    free(filtrado);
}



/** Função que lista os lotes de vacinas.
 *  @param sys estrutura do sistema.
 *  @param in input do utilizador.
 */
void muda_tempo(Sys *sys, char *in) {
    unsigned short dia, mes, ano;
    if (sscanf(in, "%*s %hu-%hu-%hu", &dia, &mes, &ano) != 3 || 
        /**<Verifica se a data fornecida é válida.*/
        !verifica_data(dia, mes, ano, sys->data_sistema)) {
        puts(sscanf(in, "%*s %hu-%hu-%hu", &dia, &mes, &ano) != 3 ? 
             sys->idioma_pt ? EDATAINVALIDA_PT : EDATAINVALIDA_EN : 
             sys->idioma_pt ? EDATAINVALIDA_PT : EDATAINVALIDA_EN);
        return;
    }
    /**<Muda a data do sistema para a data fornecida.*/
    sys->data_sistema = (Data_sistema){dia, mes, ano};
    printf("%02hu-%02hu-%04hu\n", dia, mes, ano);
}



/** Função que aplica a vacina ao paciente.
 *  @param sys estrutura do sistema.
 *  @param in input do utilizador.
 */
void aplica_vacina(Sys *sys, char *in) {
    char *nome_paciente = (char *)malloc(BUFMAX * sizeof(char));
    char *nome_vacina = (char *)malloc(BUFMAX * sizeof(char));
    char *nome_dentro = (char *)malloc(BUFMAX * sizeof(char));
/**<Se o nome estiver dentro de "", então guarda no nome_dentro o que está dentro.*/
    if (in[2] == '"') {
        snprintf(nome_dentro, BUFMAX, "a \"%%%d[^\"]\" %%%ds", BUFMAX-1, BUFMAX-1);
        if (sscanf(in, nome_dentro, nome_paciente, nome_vacina) != 2) {
            puts(sys->idioma_pt ? EINVALIDO_PT : EINVALIDO_EN);
            free(nome_paciente); free(nome_dentro); return;}
    } else {
        /**<Caso contrário, guarda o nome normalmente.*/
        snprintf(nome_dentro, BUFMAX, "a %%%ds %%%ds", BUFMAX-1, BUFMAX-1);
        if (sscanf(in, nome_dentro, nome_paciente, nome_vacina) != 2) {
            puts(sys->idioma_pt ? EINVALIDO_PT : EINVALIDO_EN);
            free(nome_paciente); free(nome_dentro); return; }}
    /** Verifica se o paciente já foi vacinado no mesmo dia. */
    if (verifica_vacinacao_no_dia(sys, nome_paciente, nome_vacina)) {
        puts(sys->idioma_pt ? EJAVACINADO_PT : EJAVACINADO_EN);
        free(nome_paciente); free(nome_vacina); free(nome_dentro); return; }
    /**<Verifica se é válido vacinar o paciente com a vacina pedida. */
    int lote_index = encontra_lote_valido(sys, nome_vacina);
    if (lote_index == -1) {
        puts(sys->idioma_pt ? ESEMSTOCK_PT : ESEMSTOCK_EN);
        free(nome_paciente); free(nome_vacina); free(nome_dentro); return; }
    if (sys->cap_inoculacoes == sys->num_inoculacoes) {
        if (!realoca_inoculacoes(sys)) {
            free(nome_paciente); free(nome_vacina); free(nome_dentro); return;}}
    /**<Aplica a vacina e armazena a inoculação no sistema.*/
    aplica_inoculacao(sys, nome_paciente, nome_vacina, lote_index);
    free(nome_paciente); free(nome_vacina); free(nome_dentro);
}




/** Função que remove um lote do sistema, ou as vacinas de um lote.
 *  @param sys estrutura do sistema.
 *  @param in input do utilizador.
 */
void remove_lote(Sys *sys, char *in) {
    char nome_lote[MAXLOTES] = {0};
    if (sscanf(in, "%*s %s", nome_lote) != 1) {
        puts(sys->idioma_pt ? EINVALIDO_PT : EINVALIDO_EN);
        return; }
    for (int i = 0; i < sys->cnt; i++) {

        if (!strcmp(sys->vacina[i].nome_lote, nome_lote)) {
            /**<Remove as vacinas de um lote.*/
            if (sys->vacina[i].num_aplicacoes > 0) {
                sys->vacina[i].nmr_vacina = 0;
            /**<Remove o lote por completo.*/
            } else {
                sys->vacina[i] = sys->vacina[--sys->cnt];
            }
            printf("%d\n", sys->vacina[i].num_aplicacoes);
            return; }
    }
    printf(sys->idioma_pt ? "%s: lote inexistente\n" : "%s: no such batch\n", 
           nome_lote);
}



/** Função que lista as inoculações.
 *  @param sys estrutura do sistema.
 *  @param in input do utilizador.
 */
void lista_inoculacoes(Sys *sys, char *in) {
    if (in[strlen(in) - 1] == '\n') in[strlen(in) - 1] = '\0';
    char *token = strchr(in, ' ');
    /**<Se não houver token, lista todas as inoculações.*/
    if (!token) {
        lista_todas_inoculacoes(sys);
        return;
    }
    token++;
    char *nome_paciente = token[0] == '"' ? token + 1 : token;
    char *fim_nome = token[0] == '"' ? strchr(nome_paciente, '"') : NULL;
    if (fim_nome) *fim_nome = '\0';
    int encontrado = 0;
    /**<Lista as inoculações do(s) paciente(s).*/
    for (int i = 0; i < sys->num_inoculacoes; i++) {
        if (!strcmp(sys->inoculacao[i].nome_paciente, nome_paciente)) {
            printf("%s %s %02hu-%02hu-%04hu\n", 
                   sys->inoculacao[i].nome_paciente, 
                   sys->inoculacao[i].nome_lote, 
                   sys->inoculacao[i].data_inoculacao.dia, 
                   sys->inoculacao[i].data_inoculacao.mes, 
                   sys->inoculacao[i].data_inoculacao.ano); encontrado = 1;
        }
    /**<Caso não exista o paciente dado no sistema.*/
    } if (!encontrado) {
        printf("%s: %s\n", nome_paciente, 
               sys->idioma_pt ? ESEMUSUARIO_PT : ESEMUSUARIO_EN);
    }
}



/** Função que remove uma inoculação do sistema.
 *  @param sys estrutura do sistema.
 *  @param in input do utilizador.
 */
void remove_inoculacao(Sys *sys, char *in) {
    char nome_paciente[BUFMAX] = {0};
    unsigned short dia = 0, mes = 0, ano = 0;
    char nome_lote[MAXNOMELOTE] = {0};
    int num_apagados = 0;
    int argumentos = sscanf(in, "d %s %hu-%hu-%hu %s", nome_paciente, &dia, &mes, 
                            &ano, nome_lote);
    /**<Caso seja fornecido apenas um nome.*/
    if (argumentos == 1) {
        int encontrado = 0;
        for (int i = 0; i < sys->num_inoculacoes; ) {
            if (strcmp(sys->inoculacao[i].nome_paciente, nome_paciente) == 0) {
                free(sys->inoculacao[i].nome_paciente);
                free(sys->inoculacao[i].nome_vacina);
                sys->inoculacao[i] = sys->inoculacao[sys->num_inoculacoes - 1];
                sys->num_inoculacoes--;
                num_apagados++;
                encontrado = 1;
            } else { i++; }
        }
        if (!encontrado) {
            if (sys->idioma_pt) {
                printf("%s: utente inexistente\n", nome_paciente);
            } else {
                printf("%s: no such user\n", nome_paciente);
            } return; }
    /**<Caso seja fornecido um nome e uma data.*/
    } else if (argumentos == 4) {
        if ((ano > sys->data_sistema.ano ||
            (ano == sys->data_sistema.ano && mes > sys->data_sistema.mes) ||
            (ano == sys->data_sistema.ano && mes == sys->data_sistema.mes && 
             dia > sys->data_sistema.dia))) {
                puts(sys->idioma_pt ? EDATAINVALIDA_PT : EDATAINVALIDA_EN);
                return; } int encontrado = 0;
        for (int i = 0; i < sys->num_inoculacoes; ) {
            if (strcmp(sys->inoculacao[i].nome_paciente, nome_paciente) == 0 &&
                sys->inoculacao[i].data_inoculacao.dia == dia &&
                sys->inoculacao[i].data_inoculacao.mes == mes &&
                sys->inoculacao[i].data_inoculacao.ano == ano) {
                free(sys->inoculacao[i].nome_paciente);
                free(sys->inoculacao[i].nome_vacina);
                sys->inoculacao[i] = sys->inoculacao[sys->num_inoculacoes - 1];
                sys->num_inoculacoes--;
                num_apagados++;
                encontrado = 1;
            } else { i++; }
        }
        if (!encontrado) { printf("0\n"); return; }
    /**<Caso seja fornecido um nome, uma data e um lote.*/
    } else if (argumentos == 5) {
        int encontrado = 0;
        for (int i = 0; i < sys->num_inoculacoes; ) {
            if (strcmp(sys->inoculacao[i].nome_paciente, nome_paciente) == 0 &&
                sys->inoculacao[i].data_inoculacao.dia == dia &&
                sys->inoculacao[i].data_inoculacao.mes == mes &&
                sys->inoculacao[i].data_inoculacao.ano == ano &&
                strcmp(sys->inoculacao[i].nome_lote, nome_lote) == 0) {
                free(sys->inoculacao[i].nome_paciente);
                free(sys->inoculacao[i].nome_vacina);
                sys->inoculacao[i] = sys->inoculacao[sys->num_inoculacoes - 1];
                sys->num_inoculacoes--;
                num_apagados++;
                encontrado = 1;
            } else { i++; }
        } if (!encontrado) {
            if (sys->idioma_pt) {
                printf("%s: lote inexistente\n", nome_lote);
            } else {
                printf("%s: no such batch\n", nome_lote);
            }
            return;
        }
    } else { puts(sys->idioma_pt ? EINVALIDO_PT : EINVALIDO_EN); return; }
    printf("%d\n", num_apagados);
}