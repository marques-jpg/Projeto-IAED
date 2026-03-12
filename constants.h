/**
 * Constantes e erros.
 * Cada erro tem uma mensagem em português e inglês.
 * @file: constants.h
 * @author: ist1113868 (Guilherme Marques)
 */



/**<Inclui as diferentes bibliotecas.*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>



/**<Define os limites de certas variáveis.*/
#define BUFMAX 65536
#define MAXLOTES 1000
#define MAXNOMELOTE 21
#define MAXNOMEDOENCA 51
#define MAXVACINAS 1000



/**<Define os erros que podem ocorrer no sistema.*/
#define EEXCESSOLOTE_PT "Demasiados lotes."
#define EEXCESSOLOTE_EN "too many vaccines"
#define ELOTEDUPLICADO_PT "número de lote duplicado"
#define ELOTEDUPLICADO_EN "duplicate batch number"
#define ENOMELOTEINVALIDO_PT "lote inválido"
#define ENOMELOTEINVALIDO_EN "invalid batch"
#define ENOMEINVALIDO_PT "nome inválido"
#define ENOMEINVALIDO_EN "invalid name"
#define EDATAINVALIDA_PT "data inválida"
#define EDATAINVALIDA_EN "invalid date"
#define EQUANTIDADEINVALIDA_PT "quantidade inválida"
#define EQUANTIDADEINVALIDA_EN "invalid quantity"
#define EINVALIDO_PT "comando inválido"
#define EINVALIDO_EN "invalid command"
#define ESEMVACINA_PT "vacina inexistente"
#define ESEMVACINA_EN "no such vaccine"
#define EJAVACINADO_PT "já vacinado"
#define EJAVACINADO_EN "already vaccinated"
#define ELOTEINEXISTENTE_PT "lote inexistente"
#define ELOTEINEXISTENTE_EN "no such batch"
#define ESEMSTOCK_PT "esgotado"
#define ESEMSTOCK_EN "no stock"
#define ESEMUSUARIO_EN "no such user"
#define ESEMUSUARIO_PT "utente inexistente"