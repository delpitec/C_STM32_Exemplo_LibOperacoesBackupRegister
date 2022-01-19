# Montagem para teste de utilização da biblioteca LibOperacoesBackupRegister:

**Descrição do programa:**<br>
Este programa tem como objetivo principal, testar as funcionalidades da biblioteca [LibOperacoesBackupRegister](https://github.com/delpitec/C_STM32_LibOperacoesBackupRegister), que permite operações de escrita e leitura nos *Backup Registers* do STM32F103C8T6.<br>
A seguir, temos a foto e o esquema de ligação da montagem teste, que está documentada em [vídeo neste link](https://youtu.be/B3UiPsuIEuk):
<br>
<br>
![montagem](https://user-images.githubusercontent.com/58537514/136506052-53745f08-4be3-4528-b47d-3d265d7dea04.png)
<br>
<br>
O microcontrolador STM32F103C8T6 (embarcado na placa *Bluepill*) enviará, através da sua UART, os valores armazenados nos seus *Backup Registers* e irá selecionar uma ação do usuário a partir dos comandos detalhados na mensagem:<br>
| Código<br>do comando | Descrição do <br>código do comando| Explicação resumida
| :---:   | :-: |  :-: |
| ED | Escreve dado | Escreve dado (HEX) no endereço especificado 
| AD | Apaga dado | Apaga dado no endereço especificado 
| AT | Apaga tudo | Apaga todos os valores armazenados

A mensagem exibida no monitor serial pode ser vista a seguir. Em cada uma das mensagens, há uma pequena descrição do formato em que o valor deve ser enviado ao microcontrolador.
Um exemplo pode ser visto a seguir, onde escrevemos o valor 0x0108 (hexadecimal) no *Backup Register* DR01 através do comando **ED DR01 0108** e apagamos o dado contido no DR02 através do comando **AD DR02**:
<br>
<br>
![terminal](https://user-images.githubusercontent.com/58537514/136858704-03f409b3-f3c0-4fc0-b7af-0d028cac20ad.png)
 &nbsp;<br> 
## Contact me:
💼[LinkedIn](https://br.linkedin.com/in/rafaeldelpino)&nbsp;&nbsp;&nbsp;
📹[Youtube](https://www.youtube.com/delpitec)&nbsp;&nbsp;&nbsp;
📸[Instagram](https://www.instagram.com/delpitec_/)&nbsp;&nbsp;&nbsp;
📧[E-mail](delpitec@gmail.com)&nbsp;&nbsp;&nbsp;

