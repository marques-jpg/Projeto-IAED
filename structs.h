/**
 * Funções principais do programa.
 * Cada Lote tem um numero de identificação, nome da vacina e data de validade.
 * @file: structs.h
 * @author: ist1113868 (Guilherme Marques)
 */



/**< inclui as restantes funções, estruturas e constantes*/
#include "constants.h"



/**<Estrutura que representa a data do sistema */
typedef struct Data_sistema {
    int dia;
    int mes;
    int ano;
} Data_sistema;



/**<Estrutura que representa a data do sistema */
typedef struct Data {
    int dia;
    int mes;
    int ano;
} Data;



/**<Estrutura que representa um lote de vacinas */
typedef struct Lote {
    char nome_lote[MAXLOTES];
    Data data;
    int nmr_vacina;
    char nome_vacina_lote[MAXLOTES];
    int num_aplicacoes;
} Lote;



/**<Estrutura que representa uma inoculação */
typedef struct Inoculacao {
    char *nome_paciente;
    char *nome_vacina;
    char nome_lote[MAXLOTES];
    Data data_inoculacao;
} Inoculacao;



/**< Estrutura que representa o sistema onde se vai armazenar 
 *os lotes e as inoculações */
typedef struct Sys {
    int cnt;
    Lote vacina[MAXLOTES];
    Data_sistema data_sistema;
    Inoculacao *inoculacao;
    int num_inoculacoes;
    int cap_inoculacoes;
    int idioma_pt;
} Sys;