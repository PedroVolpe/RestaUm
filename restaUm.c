//NOME: ERIC AKIO UCHIYAMADA                 TIA: 42107865
//NOME: PEDRO LOUREIRO MORONE BRANCO VOLPE   TIA: 42131936

#include <stdio.h>
#include <stdbool.h>
#include "pilha.h"

#define SIZE 9
//Tabuleiro do jogo
char board[SIZE][SIZE] = {
    {'#', '#', '#', '#', '#', '#', '#', '#', '#'},
    {'#', '#', '#', 'o', 'o', 'o', '#', '#', '#'},
    {'#', '#', '#', 'o', 'o', 'o', '#', '#', '#'},
    {'#', 'o', 'o', 'o', 'o', 'o', 'o', 'o', '#'},
    {'#', 'o', 'o', 'o', '.', 'o', 'o', 'o', '#'},
    {'#', 'o', 'o', 'o', 'o', 'o', 'o', 'o', '#'},
    {'#', '#', '#', 'o', 'o', 'o', '#', '#', '#'},
    {'#', '#', '#', 'o', 'o', 'o', '#', '#', '#'},
    {'#', '#', '#', '#', '#', '#', '#', '#', '#'}
};

//imprimir no arquivo txt
void imprimeMovimento(char M[SIZE][SIZE],int count,int x1,int y1,int x2,int y2){
  char *filename = "tabuleiro.txt";
  FILE *file = fopen(filename,"a");
  if(file == NULL){//se não encontrou arquivo
    printf("Erro em abrir arquivo %s\n",filename);
    return;
  }
  if(count != 0)
    fprintf(file,"Move %d: [%d,%d] -> [%d,%d]\n",count,x1,y1,x2,y2);
  for(int i = 0; i < SIZE;i++){
    for(int j = 0;j < SIZE;j++){
      fprintf(file,"%c  ", M[i][j]);
    }
    fprintf(file,"\n");
  }
  fprintf(file, "\n\n\n");

  fclose(file);
}

bool is_valid_move(int x, int y, int dx, int dy) {
    // Verifica se o resultado do movimento desejado (x + 2 * dx,y + 2 * dy), estiver "dentro" do tabuleiro, continue.
    if (x + 2 * dx >= 0 && x + 2 * dx < SIZE && y + 2 * dy >= 0 && y + 2 * dy < SIZE) {
        //Caso na posição atual(x,y), tenha uma peça E na direção(x+dx,y+dy) tiver outra peça, E no espaço afrente dessa(x+2dx,y+2dy) tenha
        //um espaço vazio, o movimento é valido.
        if (board[y][x] == 'o' && board[y + dy][x + dx] == 'o' && board[y + 2 * dy][x + 2 * dx] == '.') {
            return true;
        }
    }
    return false;
}

bool solve(int x, int y, int remaining, int move_count,Pilha *pilha) {
    //caso tenha apenas uma peça e ela esteja na posição central do tabuleiro, retorna true
    if ((remaining == 1) && board[4][4] == 'o' && (move_count == 31)) {
       return true;
    }
  
    //Direções do movimento, direita(1,0), esquerda(-1,0), baixo(0,-1) e cima(0,1) OBS:caso caiu um movimento invalido como (-1,-1)
    //ele sera removido com a função de verificação (is_valid_move)
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};
    
    for (int i = 0; i < 4; i++) {
        if (is_valid_move(x, y, dx[i], dy[i])) {
            //Movimento é valido então
            //A posição atual fica vazia
            board[y][x] = '.';
            //Posição da direção do movimento(onde uma peça foi "comida") fica vazia
            board[y + dy[i]][x + dx[i]] = '.';
            //Posição a frente da direção do movimento, recebe a peça da posição inicial
            board[y + 2 * dy[i]][x + 2 * dx[i]] = 'o';
            // Continua o jogo conforme o movimento inicial
            for (int nx = 0; nx < SIZE; nx++) {
                for (int ny = 0; ny < SIZE; ny++) {
                    if (solve(nx, ny, remaining - 1, move_count + 1, pilha)) {
                        int movimentos[tam_vet] = {y, x, (y + dy[i]), (x + dx[i]), (y + 2 * dy[i]), (x + 2 * dx[i])};
                        push(pilha,movimentos);
                        return true;
                    }
                    else{
                      int *lixo = pop(pilha);
                    }
                }
            }
        
            board[y][x] = 'o';
            board[y + dy[i]][x + dx[i]] = 'o';
            board[y + 2 * dy[i]][x + 2 * dx[i]] = '.';
      }
  }
  
  return false;
}
void coletaPassos(Pilha *p){//coletar cada passo para colocar no arquivo
  char tabuleiro[SIZE][SIZE] = {
    {'#', '#', '#', '#', '#', '#', '#', '#', '#'},
    {'#', '#', '#', 'o', 'o', 'o', '#', '#', '#'},
    {'#', '#', '#', 'o', 'o', 'o', '#', '#', '#'},
    {'#', 'o', 'o', 'o', 'o', 'o', 'o', 'o', '#'},
    {'#', 'o', 'o', 'o', '.', 'o', 'o', 'o', '#'},
    {'#', 'o', 'o', 'o', 'o', 'o', 'o', 'o', '#'},
    {'#', '#', '#', 'o', 'o', 'o', '#', '#', '#'},
    {'#', '#', '#', 'o', 'o', 'o', '#', '#', '#'},
    {'#', '#', '#', '#', '#', '#', '#', '#', '#'}
  };
  
  imprimeMovimento(tabuleiro,0,0,0,0,0);
  
  No *movimento = p->topo;
  int move_count = 1;
  while (movimento != NULL) {
    tabuleiro[movimento->info[0]][movimento->info[1]] = '.';  
    tabuleiro[movimento->info[2]][movimento->info[3]] = '.';   
    tabuleiro[movimento->info[4]][movimento->info[5]] = 'o';
    
    imprimeMovimento(tabuleiro, move_count,movimento->info[0], movimento->info[1], movimento->info[4], movimento->info[5]);
    
    move_count++;
    movimento = movimento->next;
  }
}
int main() {
    printf("Aguarde, o programa vai demorar um pouquinho...");
  //Busca solução para diversos moviemntos iniciais 
    Pilha *pilha = create_stack();

    //reiniciar o arquivo txt com nada escrito, caso precise testar várias vezes
    FILE* file = fopen("tabuleiro.txt","w");
    fprintf(file,"");
    fclose(file);

    for (int x = 0; x < SIZE; x++) {
        for (int y = 0; y < SIZE; y++) {
            if (solve(x, y, 32, 0, pilha)) {
                  printf("\nSolution found!\n");
                  printf("\nVisualize no arquivo txt!\n");
                  coletaPassos(pilha);
                  free_stack(pilha);
                return 0;
            }
        }
    }
    printf("No solution found.\n");
    free_stack(pilha);
    return 0;
}