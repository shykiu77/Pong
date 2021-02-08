# Pong
Projeto final da matéria ihs.

link do video demonstrando o multiplayer funcionando em localhost:

https://youtu.be/jetZLCwwBVE

---------------------------------------------------------------------------------------------------------------

* Compilando o Projeto:

1 - Clone este repositório.

2 - Estando no projeto, vá até a pasta src e execute o arquivo make.

* Linkando os Dois Emuladores (Multiplayer):

1 - Abra a pasta tools/emulator e execute o bgb (emulador de gameboy). 

2 - Abra duas abas do emulador:

    2.1 - Em uma das duas abas, basta clicar com o botão direito na tela do emulator e selecionar Link->Listen->Selecionar Porta (8765 padrão do bgb).

<p align="center">
  <img src="https://i.imgur.com/ruEMJU2.png" />
</p>
<p align="center">
  <img src="https://i.imgur.com/VZMtBT7.png" />
</p>
    Ao final do proceso a barra superior da aba do gameboy deve esta com a informação "listening".
<p align="center">
  <img src="https://i.imgur.com/8bmMdC3.png" />
</p>

    2.2 - Na segunda aba, basta clicar com o botão direito na tela do emulador e selecionar Link->Connect->Selecionar IP:PORTA

<p align="center">
  <img src="https://i.imgur.com/xuVRgTw.png" />
</p>
    IP local host e PORTA padrão do bgb. 
<p align="center">
  <img src="https://i.imgur.com/VTgpO80.png" />
</p>
    Ao final do proceso a barra superior da aba de ambos os emuladores deve aparecer a informação "linked" (caso você ja tenha feito o load da rom do game) ou "linked, other gb inactive" (caso não tenha feito o load da rom, que é o caso dessa demonstração).
<p align="center">
  <img src="https://i.imgur.com/JAwOPd2.png" />
  <img src="https://i.imgur.com/T8DZMqA.png" />
</p>

* Executando a ROM do PONG-Multiplayer:

OBS: Nada impede que o usuário execute a ROM e depois link os dois emuladores, funcionará da mesma forma se todos os passos forem realizados corretamente.


1 - Seguindo o tutorial, uma vez que ja temos o projeto compilado, e os dois emuladores linkados, basta executarmos a ROM do jogo:

Clicar com o botão direito na tela do emulador e selecionar Load ROM
<p align="center">
  <img src="https://i.imgur.com/JcGLMml.png" />
</p>
Ir até a pasta do projeto->build->selecionar o arquivo main.gb 
<p align="center">
  <img src="https://i.imgur.com/mQOHSRM.png" />
</p>
    Repita esse mesmo processo de Load ROM na tela do outro emulador. Ao final do processo ambas as telas dos emuladores devem estar da seguinte forma:
<p align="center">
  <img src="https://i.imgur.com/GKLSnwK.png" />
</p>

* Iniciar o PONG-Multiplayer:

Uma vez estando na tela de START em ambos os emuladores, basta apertar em uma das telas a tecla A do teclado do PC (corresponde a B no gameboy) e na outra tela apertar a tecla S (corresponde a tecla A do gameboy)

PONG-Multiplayer rodando:
<p align="center">
  <img src="https://i.imgur.com/wlULM6b.png" />
</p>












