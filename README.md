# Hash-Map-with-AVL-tree
Hash Map with AVL tree as part of an assignment for Data Structure II class at Catholic University of Santos. Lectured by Ciro Cine Trindade.

Description (in Portuguese)

O Portal da Transparência do Governo Federal (http://transparencia.gov.br/) é uma iniciativa da Controladoria-Geral da União (CGU), lançada em novembro de 2004, para assegurar a boa e correta aplicação dos recursos públicos. O objetivo é aumentar a transparência da gestão pública, permitindo que o cidadão acompanhe como o dinheiro público está sendo utilizado e ajude a fiscalizar.
Entre as informações divulgadas pelo portal, encontra-se a remuneração de servidores civis e militares. Este trabalho utiliza a base de dados da remuneração dos servidores civis no mês de agosto de 2017 (http://transparencia.gov.br/downloads/servidores.asp). Trata-se de um arquivo CVS (Comma Separated Values) que foi tratado e transformado em um arquivo binário contendo estruturas do tipo remuneracao mostrada a seguir: <br/>
<br/>#define CPF_LENGTH 15<br/>
#define NOME_LENGTH 51<br/>
typedef struct { int id;<br/>
char cpf[CPF_LENGTH]; char nome[NOME_LENGTH]; float salario_bruto;<br/>
} remuneracao;<br/><br/>
Implemente um programa em C que leia as informações do arquivo “Remuneracao_201708.dat” e carregue-as em um Hash Map, onde a chave é o id do servidor e o valor é o número do registro do servidor com esse id no arquivo “Remuneracao_201708.dat”. Portanto, a operação map_get() devolve o número do registro do servidor cujo id é fornecido como chave, e não as informações do servidor. Com o número do registro é possível fazer um acesso direto ao arquivo e lê as informações do servidor e em seguida exibi-las no vídeo. Essa estratégia visa diminuir a memória utilizada pelo Hash Map, pois o valor associado a cada chave é um int (4 bytes) e não uma estrutura do tipo remuneracao (76 bytes).
Utilize a função de hashing que usa o método do meio do quadrado (descrita em aula) para uma tabela de hashing com M = 1024 encaixes.
<br/>   Considerando que o número de encaixes da tabela hash é bem menor que o número de
2 servidores, haverá muitas colisões de chaves. Utilize o espalhamento externo para tratar as colisões e uma árvore AVL como estrutura de dados para armazenar as chaves sinônimas, ou
seja, o Hash Map utiliza um Tree Map para armazenar as chaves sinônimas.
Após carregar as informações do arquivo no Hash Map, o programa deverá solicitar repetidamente o id de um servidor, e caso ele seja localizado no mapa, exibir todos os seus dados, caso contrário, exibir uma mensagem de erro. O programa deve ser encerrado quando o usuário digitar um id igual 0.
