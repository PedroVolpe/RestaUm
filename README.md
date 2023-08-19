# RestaUm
Algoritmo para encontrar uma solução automática para o Resta Um

O Resta Um é um jogo de tabuleiro cujo objetivo é deixar apenas uma peça restante no centro do tabuleiro.
Para eliminar uma peça, você precisa "pular" sobre ela, como no jogo de Damas. Para fazer isso, é necessário que exista um espaço vazio na direção que se deseja pular.
Para vencer, apenas uma peça pode estar no tabuleiro e ela deve estár na posição central do mesmo.

Como o algoritmo funciona ?
 - Primeiro definimos o tabuleiro em seu estado inicial.
 - Depois criamos uma Pilha auxiliar que armazenará os movimentos válidos para a solução. Dentro desse movimento, armazenamos a posição atual da peça, a direção em que essa peça está se movendo e a posição futura da mesma.
 - E assim finalmente iniciamos o algoritmo.
 - Seu primeiro passo é encontrar um movimento inicial válido (a partir de um loop) e continuar o jogo a partir dele, se nenhuma solução for encontrada por esse caminho inicial, ele buscará outro.
 - Com isso, depois de escolher um inicio válido, ele realizará a validação de todos os movimentos possiveis e irá executa-los em ordem, caso o movimento seja possivel ele será armazenado na Pilha de movimentos validos. Caso em um dado ponto o movimento seja inválido, o algoritmo irá retroceder e buscar outro ramo de solução possivel e remover todos os "movimentos validos" da Pilha, visto que eles não levam a uma solução.
 - Ao encontrar a solução, o algoritmo irá imprimir o resultado mostrando o passo a passo para encontrar aquela solução em um arquivo .txt
 - Mostrando não só o tabuleiro, como também o movimento efetuado.

Inconveniência encontrada: 
  - Visto que o algoritmo se baseia em um loop para buscar sua solução, em todos os casos de teste ele seguirá a mesma sequência de passos, e dessa forma encontranso sempre a mesma solução, que será a primeira possivel.
  - Mas isso não significa que essa é a única.

