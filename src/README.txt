ISTRUÇÕES PARA COMPILAR:
O ficheiro rlutil.h deve se encontrar na mesma pasta que o main.c
Comando aconselhado para compilação:
gcc main.c -o 4_em_Linha -Ofast -static-libgcc -static-libstdc++
  O comando acima vai gerar um ficheiro 4_em_Linha.exe na mesma pasta

No entanto já providenciei compilações do jogo pronto a correr
em 64 bits e 32 bits (se não conseguirem compilar)
  A versão 32 bits sai logo do jogo quando premimos x;
  A versão 64 bits, mostra uma mensagem antes de sair;

Se quiserem analizar o código-fonte do main.c e se alguns caracteres
aparecerem estranhos ou com pontos de interrogação é porque o ficheiro
está codificado em Western European DOS (CP 850)