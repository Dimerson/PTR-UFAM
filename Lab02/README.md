# Lab02

Descrição do Lab2:

Um robô móvel com acionamento diferencial pode ser descrito pelo modelo no
espaço de estados 1:

x ̇(t) =

|sin(x3) 0|
|cos(x3) 0| * u(t)
| 0      1|



y(t) =

|1 0 0|
|0 1 0| * x(t)
|0 0 1|


onde x(t) = [x1 x2 x3]T = [xc yc θ]
T
, sendo (xc, yc) a posição do centro de massa

do robô e θ a sua orientação. u(t) = [v ω]

T é a entrada do sistema, sendo v a
velocidade linear e ω a velocidade angular do robô. A saída do sistema é y(t).
Faça um programa na linguagem C para simular a resposta desse sistema para
uma entrada igual a:


	{0, para t < 0

u(t) =	|  1 |
	|0.2π|, para 0 ⩽ t < 10

	|  1  |
	|−0.2π|, para t ⩾ 10}



OBSERVAÇÕES:


• Utilize a estrutura gerada no exercício anterior e a expanda para este pro-
grama.
• O programa deverá fazer a simulação para t ∈ [0, 20]s e gerar como saída um
arquivo ASCII contendo uma linha para cada valor de t. Os valores deverão
ser separados pelo caractere tab.
• Cada linha deverá conter: o correspondente valor de t, o valor de u(t) e o
valor de y(t).
• É aconselhável que a estrutura do programa já preveja variações na entrada.
• O nome do arquivo onde serão salvos os dados deve ser passado como
parâmetro para o programa ou ser criado por redirecionamento de saída do
SO no terminal.
• As funções que realizam os cálculos devem ser implementadas em arquivos
separados apropriados.
• Esta estrutura de arquivos será ampliada ao longo do curso e conterá funções
que serão utilizadas em diversos programas.
• A simulação em si deverá ser realizada em uma função implementada em um
arquivo separado das demais funções.
• A obtenção do valor de u(k) a cada instante da simulação deverá ser feito
através da chamada de uma função. O único parâmetro para esta função
deve ser k.
• A escrita de cada valor de t, u(t) e y(t) no arquivo de saída deverá ser feita
através de uma função chamada pela função que faz a simulação. Os únicos
parâmetros para esta função devem ser t, u e y.
• Gere os gráficos de u(t), y(t) e yc(t)×xc(t), a partir do arquivo ASCII gerado,
utilizando o Matlab, Gnuplot, Gwave ou outro software apropriado.
