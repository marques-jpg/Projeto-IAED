/**
 * Programa de organização e aplicação de vacinas.
 * Cada Lote tem um numero de identificação, nome da vacina e data de validade.
 * @file: project.c
 * @author: ist1113868 (Guilherme Marques)
 */


 
/**< inclui as restantes funções, estruturas e constantes*/
#include "principais.h"



/** Função principal do programa.
 *  @return retorna sempre 0.
 *  @param argc número de argumentos dados.
 *  @param argv array de argumentos dados.
 */
int main(int argc, char *argv[]) {
    char buf[BUFMAX] = {0};
    Sys sys = {0};
    /**< muda o idioma consoante a opção dada*/
    if (argc > 1 && strcmp(argv[1], "pt") == 0) { sys.idioma_pt = 1; }
    else { sys.idioma_pt = 0; }
    /**< aloca memória para as inoculações*/
    sys.inoculacao = (Inoculacao *)malloc(100 * sizeof(Inoculacao));   
    if (sys.inoculacao == NULL) {
        fprintf(stderr, "Erro ao alocar memória para inoculacoes\n");
        return 1; }
    /**< Inicializa algumas variáveis*/
    sys.cap_inoculacoes = 4;
    sys.num_inoculacoes = 0;
    sys.data_sistema.dia = 1;
    sys.data_sistema.mes = 1;
    sys.data_sistema.ano = 2025;
    sys.cnt = 0;
    /**< Processa as entradas do utilizador*/
    while (fgets(buf, BUFMAX, stdin)) {
        switch (buf[0]) {
            case 'q':
                /**< Liberta a memória alocada para as inoculações*/
                for (int i = 0; i < sys.num_inoculacoes; i++) {
                    free(sys.inoculacao[i].nome_paciente);
                    free(sys.inoculacao[i].nome_vacina);
                }
                free(sys.inoculacao);
                return 0;
            case 'c': cria_lote(&sys, buf); break;
            case 'l': lista_lote(&sys, buf); break;
            case 't': muda_tempo(&sys, buf); break;
            case 'a': aplica_vacina(&sys, buf); break;
            case 'r': remove_lote(&sys, buf); break;
            case 'u': lista_inoculacoes(&sys, buf); break;
            case 'd': remove_inoculacao(&sys, buf); break;
        }
    }
    /**< Liberta a memória alocada para as inoculações*/
    for (int i = 0; i < sys.num_inoculacoes; i++) {
        free(sys.inoculacao[i].nome_paciente);
        free(sys.inoculacao[i].nome_vacina);
    }
    free(sys.inoculacao);
    return 0;
}