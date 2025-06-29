#include "raylib.h"
#include <stdio.h>
#include <locale.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

//structs
typedef struct {
    const char *pergunta;
    const char *alternativas[4];
    int respostaCorreta;
} Questao;

typedef struct {
    char nome[50];
    int pontos;
} Jogador;

//variaveis gloabais
Jogador jogadores[100];
int totalJogadores = 0;

//funcoes
void carregarRanking() {
    FILE *pont_arq = fopen("C:\\Users\\jefer\\Desktop\\projeto_do_jogo\\Placar\\save.txt", "r");
    totalJogadores = 0;

    if (pont_arq != NULL) {
        while (fscanf(pont_arq, "%s %d", jogadores[totalJogadores].nome, &jogadores[totalJogadores].pontos) != EOF) {
            totalJogadores++;
        }
        fclose(pont_arq);
    }
}

void removerDuplicados() {
    for (int i = 0; i < totalJogadores - 1; i++) {
        for (int j = i + 1; j < totalJogadores; ) {
            if (strcmp(jogadores[i].nome, jogadores[j].nome) == 0) {
                if (jogadores[j].pontos > jogadores[i].pontos) {
                    jogadores[i] = jogadores[j];
                }
                for (int k = j; k < totalJogadores - 1; k++) {
                    jogadores[k] = jogadores[k + 1];
                }
                totalJogadores--;
            } else {
                j++;
            }
        }
    }
}

void salvarPontuacao(const char *nome, int pontos) {
    FILE *pont_arq = fopen("C:\\Users\\jefer\\Desktop\\projeto_do_jogo\\Placar\\save.txt", "a");
    if (pont_arq != NULL) {
        fprintf(pont_arq, "%s %d\n", nome, pontos);
        fclose(pont_arq);
    }
}

void OrdenarRanking(Jogador jogadores[], int totalJogadores) {
    for (int i = 0; i < totalJogadores - 1; i++) {
        for (int j = 0; j < totalJogadores - i - 1; j++) {
            if (jogadores[j].pontos < jogadores[j + 1].pontos) {
                // Trocar os jogadores de lugar
                Jogador temp = jogadores[j];
                jogadores[j] = jogadores[j + 1];
                jogadores[j + 1] = temp;
            }
        }
    }
}

//variaveis globais
char nome_jogador[20] = "";
int quantidadeLetra = 0;
int pontosTotais = 0;


int main(void) {
    //permite por acentos e Ç
    setlocale(LC_ALL, "Portuguese_Brazil.1252");

    //abre a janela do jogo
    InitWindow(0, 0, "Quem sabe, sabe");
    ToggleFullscreen();
    InitAudioDevice();
    const char *scoreFile = "placar.txt";

    float screenWidth = GetScreenWidth();
    float screenHeight = GetScreenHeight();

   Music menu = LoadMusicStream("C:/Users/jefer/Desktop/projeto_do_jogo/sounds/MENU.mp3");

    PlayMusicStream(menu);
    SetTargetFPS(60);

    // Carregar texturas
    Texture2D botao = LoadTexture("C:/Users/jefer/Desktop/projeto_do_jogo/texturas/botaoquest.png");
    Texture2D numero = LoadTexture("C:/Users/jefer/Desktop/projeto_do_jogo/texturas/numero_questao.png");
    Texture2D meme = LoadTexture("C:/Users/jefer/Desktop/projeto_do_jogo/texturas/emojimeme.png");
    Texture2D graca = LoadTexture("C:/Users/jefer/Desktop/projeto_do_jogo/texturas/graca.png");
    Texture2D dado = LoadTexture("C:/Users/jefer/Desktop/projeto_do_jogo/texturas/dado.png");
    Texture2D japao = LoadTexture("C:/Users/jefer/Desktop/projeto_do_jogo/texturas/japao.png");
    Texture2D oli = LoadTexture("C:/Users/jefer/Desktop/projeto_do_jogo/texturas/Oli.png");
    Texture2D logica4 = LoadTexture("C:/Users/jefer/Desktop/projeto_do_jogo/texturas/questaologica4.png");
    Texture2D questao = LoadTexture("C:/Users/jefer/Desktop/projeto_do_jogo/texturas/roda.jpeg");
    Texture2D questaoY = LoadTexture("C:/Users/jefer/Desktop/projeto_do_jogo/texturas/questaop.jpeg");
    Texture2D num23 = LoadTexture("C:/Users/jefer/Desktop/projeto_do_jogo/texturas/num23.jpeg");
    Texture2D holanda = LoadTexture("C:/Users/jefer/Desktop/projeto_do_jogo/texturas/holanda.png");
    Texture2D roda25 = LoadTexture("C:/Users/jefer/Desktop/projeto_do_jogo/texturas/roda25.jpeg");
    Texture2D cerebro = LoadTexture("C:/Users/jefer/Desktop/projeto_do_jogo/texturas/cerebro.png");
    Texture2D interrogacao = LoadTexture("C:/Users/jefer/Desktop/projeto_do_jogo/texturas/interrogacao.png");
    Texture2D lampada = LoadTexture("C:/Users/jefer/Desktop/projeto_do_jogo/texturas/lampada.png");
    Texture2D atomo = LoadTexture("C:/Users/jefer/Desktop/projeto_do_jogo/texturas/atomo.png");
    Texture2D cinema = LoadTexture("C:/Users/jefer/Desktop/projeto_do_jogo/texturas/CINEMA.jpg");
    Texture2D pray = LoadTexture("C:/Users/jefer/Desktop/projeto_do_jogo/texturas/bropray.jpeg");
    Texture2D amassado = LoadTexture("C:/Users/jefer/Desktop/projeto_do_jogo/texturas/amassado.jpeg");  
    Texture2D palco = LoadTexture("C:/Users/jefer/Desktop/projeto_do_jogo/texturas/palco.jpeg");
    Texture2D dialogo = LoadTexture("C:/Users/jefer/Desktop/projeto_do_jogo/texturas/dialogo.png");

    //textura dos numeros questoes
    Texture2D numero_questao1  = LoadTexture("C:/Users/jefer/Desktop/projeto_do_jogo/texturas/numero_questao1.png");
    Texture2D numero_questao2  = LoadTexture("C:/Users/jefer/Desktop/projeto_do_jogo/texturas/numero_questao2.png");
    Texture2D numero_questao3  = LoadTexture("C:/Users/jefer/Desktop/projeto_do_jogo/texturas/numero_questao3.png");
    Texture2D numero_questao4  = LoadTexture("C:/Users/jefer/Desktop/projeto_do_jogo/texturas/numero_questao4.png");
    Texture2D numero_questao5  = LoadTexture("C:/Users/jefer/Desktop/projeto_do_jogo/texturas/numero_questao5.png");
    Texture2D numero_questao6  = LoadTexture("C:/Users/jefer/Desktop/projeto_do_jogo/texturas/numero_questao6.png");
    Texture2D numero_questao7  = LoadTexture("C:/Users/jefer/Desktop/projeto_do_jogo/texturas/numero_questao7.png");
    Texture2D numero_questao8  = LoadTexture("C:/Users/jefer/Desktop/projeto_do_jogo/texturas/numero_questao8.png");
    Texture2D numero_questao9  = LoadTexture("C:/Users/jefer/Desktop/projeto_do_jogo/texturas/numero_questao9.png");
    Texture2D numero_questao10 = LoadTexture("C:/Users/jefer/Desktop/projeto_do_jogo/texturas/numero_questao10.png");
    Texture2D numero_questao11 = LoadTexture("C:/Users/jefer/Desktop/projeto_do_jogo/texturas/numero_questao11.png");
    Texture2D numero_questao12 = LoadTexture("C:/Users/jefer/Desktop/projeto_do_jogo/texturas/numero_questao12.png");
    Texture2D numero_questao13 = LoadTexture("C:/Users/jefer/Desktop/projeto_do_jogo/texturas/numero_questao13.png");
    Texture2D numero_questao14 = LoadTexture("C:/Users/jefer/Desktop/projeto_do_jogo/texturas/numero_questao14.png");
    Texture2D numero_questao15 = LoadTexture("C:/Users/jefer/Desktop/projeto_do_jogo/texturas/numero_questao15.png");
    Texture2D numero_questao16 = LoadTexture("C:/Users/jefer/Desktop/projeto_do_jogo/texturas/numero_questao16.png");
    Texture2D numero_questao17 = LoadTexture("C:/Users/jefer/Desktop/projeto_do_jogo/texturas/numero_questao17.png");
    Texture2D numero_questao18 = LoadTexture("C:/Users/jefer/Desktop/projeto_do_jogo/texturas/numero_questao18.png");
    Texture2D numero_questao19 = LoadTexture("C:/Users/jefer/Desktop/projeto_do_jogo/texturas/numero_questao19.png");
    Texture2D numero_questao20 = LoadTexture("C:/Users/jefer/Desktop/projeto_do_jogo/texturas/numero_questao20.png");
    Texture2D numero_questao21 = LoadTexture("C:/Users/jefer/Desktop/projeto_do_jogo/texturas/numero_questao21.png");
    Texture2D numero_questao22 = LoadTexture("C:/Users/jefer/Desktop/projeto_do_jogo/texturas/numero_questao22.png");
    Texture2D numero_questao23 = LoadTexture("C:/Users/jefer/Desktop/projeto_do_jogo/texturas/numero_questao23.png");
    Texture2D numero_questao24 = LoadTexture("C:/Users/jefer/Desktop/projeto_do_jogo/texturas/numero_questao24.png");
    Texture2D numero_questao25 = LoadTexture("C:/Users/jefer/Desktop/projeto_do_jogo/texturas/numero_questao25.png");


    char mensagem[100];

    //botoes
    //alternativas
    Vector2 posicoes[4] = {
        { 440, 500 },
        { 440, 800 },
        { 1050, 500 },
        { 1050, 800 }
    };
    //botoes das alternativas
    Rectangle botoes[4];
    for (int i = 0; i < 4; i++) {
        botoes[i] = (Rectangle){ posicoes[i].x, posicoes[i].y, botao.width, botao.height };

    }

    //botoes (retangulo)
    Rectangle botaoIniciar = { screenWidth/2 - 200, screenHeight/2 -100, 400, 100 };
    Rectangle botaoEnviarnome = { screenWidth/2 - 200, screenHeight/2 -100, 400, 100 };
    Rectangle espacoNome = { screenWidth/2 - 320, screenHeight/2 - 220, 640, 100 };
    Rectangle botaoComoJogar = { screenWidth/2 - 200, screenHeight/2 + 50, 400, 100};
    Rectangle botaoPlacar = {screenWidth/2 -200, screenHeight/2 + 200, 400, 100};
    Rectangle botaoCredito = {screenWidth/2 -200, screenHeight/2 + 350, 400, 100};
    Rectangle botaoSairF = {25, 30, 70, 70};

    //posicao do numero da questao
    Vector2 numero_pos = { 50, 50 };

    // a escrita das Questões
    Questao questoes[] = {
        
//Questoes
//0  1
//2  3
{"Qual o nome do item abaixo?", {"Graça", "Fogueira", "Lanterna", "Altar"}, 0},
{"  Se 5 máquinas fazem 5 produtos em 5 minutos,\n  quanto tempo 100 máquinas levam para fazer\n  100 produtos?", {"5 minutos", "10 minutos", "100 minutos", "50 minutos"}, 0},
{"Qual número completa a sequência?\n2, 6, 12, 20, 30, X ?", {"36", "40", "42", "48"}, 1},
{"Um pato põe um ovo na divisa entre o Brasil e\no Peru. De quem é o ovo?", {"Do Brasil", "Do Peru", "Dos dois", " "}, 3},
{"Qual o valor de Y?", {"30", "45", "90", "60"}, 3},
{" Em uma sala há quatro cantos, cada gato vê\n 3 gatos. Quantos gatos há na sala?", {"12", "4", "16", "8"}, 1},
{"Qual o maior país do mundo?", {"Estados Unidos", "Rússia", "China", "Brasil"}, 1},
{"Quantos animais de cada espécie Moisés colocou\nna arca?", {"Todos", "2 de cada", "Nenhum", "Depende"}, 2},
{"Um fazendeiro tem 17 cabras. Todas, exceto 8,\nmorrem. Quantas cabras morreram? ", {"8", "17", "9", "25"}, 2},
{"Qual a soma de todos os lados de um dado?", {"21", "23", "22", "19"}, 0},
{"Um trem elétrico está indo de norte para sul.\nPara onde vai a fumaça?", {"Nenhum", "Sul", "Leste", "Norte"}, 0},
{"Qual é a flor nacional do Japão?", {"Flor de \nCerejeira", "Rosas", "Tulipas", "Ameixeiras"}, 0},
{"Onde foram realizados os primeiros Jogos\nOlímpicos modernos?", {"Creta", "Esparta", "Macedônia", "Atenas"}, 3},
{"Qual o valor de X?", {"23", "25", "21", "26"}, 0},
{"Em uma corrida você ultrapassa o último \ncolocado, qual sua posição?", {"Último", "Penúltimo", "Primeiro", "Antepenúltimo"}, 2},
{"    Há dois relógios: o relógio verde está quebrado e\n    não funciona, mas o relógio amarelo atrasa um segundo\n    a cada 24 horas. Qual relógio é mais preciso?", {"Verde", "Amarelo", "Ambos", "Nenhum"}, 0},
{"Se você colocar um cubo de gelo em um copo de\nágua cheio até a borda, o que acontece\nquando ele derreter?", {"A água\ntransborda", "Nada", "O copo se\nquebra", "A água sobe"}, 1},
{"Se você tiver uma tigela com seis maçãs e retirar\nquatro, quantas maçãs você terá?", {"2", "6", "4", "Nenhuma"}, 2},
{"De qual país é essa bandeira?", {"Holanda", "França", "Rússia", "Brasil"}, 0},
{"Se um avião cai na fronteira entre Brasil e\nArgentina, onde enterram os sobreviventes?", {"Brasil", "Argentina", "Nenhum", "No cemíterio"}, 2},
{"Qual a probabilidade de acertar essa questão?", {"25%", "25%", "33,33%", "50%"}, 3},
{"Que fruto nasce da oliveira?", {"Amêndoa", "Oliva", "Azeitona", "Açaí"}, 2},
{"Uma mulher tem 4 filhas, e cada filha tem\num irmão. Quantos filhos ela tem?", {"4", "5", "8", "9"}, 1},
{"Um médico dá 3 comprimidos para tomar de meia em\nmeia hora. Quanto tempo leva pra tomar os 3?", {"1h", "1h30", "2h", "2h30"}, 0},
{"Qual o próximo número da sequência?", {"16", "20", "22", "18"}, 3},
};
    //calcula a quantidade de questoes automaticamente
    int totalQuestoes = 25;
    int questaoAtual = 0;

    // Estados 1 ou 0
    bool noMenu = true;
    bool escreverNome = false;
    bool noComoJogar = false;
    bool jogoAtivo= false;
    bool noPlacar= false;
    bool noCredito= false;
    bool mostrandoResultado = false;
    bool telaVitoriaFinal= false;
    bool telaVitoriaFinalDialogo= false;
    bool errou = false;
    bool tempoAcabou = false;
    bool botaoSair = false;

    //variaveis usadas no jogo
    float tempoRestante = 35.0f;
    int pontosQuestao = 100;
    int pontosTotais = 0;

    while (!WindowShouldClose()) {
        UpdateMusicStream(menu);

        Vector2 mousePos = GetMousePosition();
          
        if (noMenu) {
            pontosTotais = 0;

            //botao de voltar
            if (CheckCollisionPointRec(mousePos, botaoIniciar) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                noMenu = false;
                escreverNome = true;
                tempoRestante = 35.0f;
                jogoAtivo = false;

            }
            else if (CheckCollisionPointRec(mousePos, botaoComoJogar) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                noComoJogar = true;
                noMenu = false;
            }
            else if (CheckCollisionPointRec(mousePos, botaoPlacar) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                noPlacar= true;
                noMenu= false;
            }
            else if (CheckCollisionPointRec(mousePos, botaoCredito) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                noCredito= true;
                noMenu= false;
            }

        } else if (escreverNome) {
            int tecla = GetCharPressed();

            while(tecla>0){
                if ((tecla >= 32) && (tecla <= 125) && (quantidadeLetra < 19)){
                    nome_jogador[quantidadeLetra] = char(tecla);
                    quantidadeLetra++;
                    nome_jogador[quantidadeLetra]= '\0';
                }
                tecla = GetCharPressed();
            }
        
            if (IsKeyPressed(KEY_BACKSPACE)) {
                if (quantidadeLetra > 0) {
                    quantidadeLetra--;
                    nome_jogador[quantidadeLetra] = '\0';
                 }
             }

            if(quantidadeLetra >= 1){
                if(CheckCollisionPointRec(mousePos, botaoEnviarnome) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                   escreverNome = false;
                    jogoAtivo= true;
                    tempoRestante = 35.0f;
                    pontosQuestao = 100;
                    questaoAtual = 0;
                    pontosTotais = 0;
                    errou = false;
                    mostrandoResultado = false;
                    tempoAcabou = false;
                 }
            }
            if (CheckCollisionPointRec(mousePos, botaoSairF) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                 noMenu = true;
                escreverNome = false;
                }

        }else if(noComoJogar){
            botaoSair= true;
            if(CheckCollisionPointRec(mousePos, botaoSairF) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                noMenu= true;
                noComoJogar= false;
            }
            
        } else if(noPlacar){
            
            botaoSair= true;
            if(CheckCollisionPointRec(mousePos, botaoSairF) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                noMenu= true;
                noPlacar= false;
            }

        }else if(noCredito){
            botaoSair= true;
            if(CheckCollisionPointRec(mousePos, botaoSairF) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                noMenu= true;
                noCredito= false;
            }
        
        }else if (jogoAtivo) {
            tempoRestante -= GetFrameTime();
            if (tempoRestante > 0.0f) {
                if(questaoAtual>9 && questaoAtual<=19){
                    pontosQuestao = pow((int)(tempoRestante * 5.0f), 1.069);
                }
                else if(questaoAtual>19){
                    pontosQuestao = pow((int)(tempoRestante * 5.0f), 1.154);
                }
                else pontosQuestao = (int)(tempoRestante * 5.0f);
            } else {
                tempoRestante = 0.0f;
                pontosQuestao = 0;
                errou = true;
                tempoAcabou = true;
                jogoAtivo = false;
            }

            for (int i = 0; i < 4; i++) {

                if (CheckCollisionPointRec(GetMousePosition(), botoes[i]) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    if (i == questoes[questaoAtual].respostaCorreta) {
                        pontosTotais += pontosQuestao;
                        
                        // Avança para a próxima questão
                        questaoAtual +=1;
                        if (questaoAtual >= totalQuestoes) {
                            telaVitoriaFinal = true;
                            jogoAtivo = false;
                            questaoAtual = 0;
                        }
                        // Reinicia timer e pontos
                        tempoRestante = 35.0f;
                        pontosQuestao = 100;
                        errou = false;
                        tempoAcabou = false;
                    } else {
                        errou = true;
                        jogoAtivo = false;
                        tempoAcabou = false;
                    }
                }
            }
        } if(errou){
            // Aqui só espera ENTER para voltar ao menu se errou ou tempo esgotou
            if (IsKeyPressed(KEY_ENTER)) {
                if (errou) {
                    noMenu = true;
                    pontosTotais = 0;
                    questaoAtual = 0;
                    errou = false;
                    jogoAtivo= false;
                    mostrandoResultado = false;
                    tempoAcabou = false;
                }
            }

        } if(telaVitoriaFinal){
          
            if(IsKeyPressed(KEY_ENTER)){
                telaVitoriaFinalDialogo = true;
                telaVitoriaFinal= false;
                salvarPontuacao(nome_jogador, pontosTotais);
            } 
        }
        else if (telaVitoriaFinalDialogo){
            
            if(IsKeyPressed(KEY_ENTER)){
                noMenu= true;
                telaVitoriaFinalDialogo= false;
                }
            }
    // Desenho
        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (noMenu) {
             bool hover1;
             bool hover2;
             bool hover3;
             bool hover4;
            Color corBotao;
            Color corBotao2;
            Color corBotao3;
            Color corBotao4;
                
                    //tom escuro do jogar
                    hover1 = CheckCollisionPointRec(GetMousePosition(), botaoIniciar);
                    if (hover1) {
                        corBotao = (Color){70, 70, 70, 255};
                    } else {
                        corBotao = GRAY;
                    }
                    //tom escuro do comojogar
                    hover2 = CheckCollisionPointRec(GetMousePosition(), botaoComoJogar);
                    if (hover2) {
                        corBotao2 = (Color){70, 70, 70, 255};
                    } else {
                        corBotao2 = GRAY;
                    }
                    //tom escuro do placar
                    hover3 = CheckCollisionPointRec(GetMousePosition(), botaoPlacar);
                    if (hover3) {
                        corBotao3 = (Color){70, 70, 70, 255};
                    } else {
                        corBotao3 = GRAY;
                    }
                    //tom escuro do credito
                    hover4 = CheckCollisionPointRec(GetMousePosition(), botaoCredito);
                    if (hover4) {
                        corBotao4 = (Color){70, 70, 70, 255};
                    } else {
                        corBotao4 = GRAY;
                    }

             DrawText("QUEM SABE, SABE", screenWidth/2 - MeasureText("QUEM SABE, SABE", 120)/2, screenHeight/2 - 300, 120, BLACK);
             DrawRectangleRec(botaoIniciar, corBotao);
             DrawText("JOGAR", screenWidth/2 - MeasureText("JOGAR", 60)/2, screenHeight/2 - 80, 60, BLACK);
             DrawRectangleRec(botaoComoJogar, corBotao2);
             DrawText("COMO JOGAR", screenWidth/2 -MeasureText("COMO JOGAR", 57)/2, screenHeight/2 + 70, 57, BLACK);
             DrawRectangleRec(botaoPlacar, corBotao3);
             DrawText("PLACAR", screenWidth/2 - MeasureText("PLACAR", 60)/2, screenHeight/2 + 220, 60, BLACK);
             DrawRectangleRec(botaoCredito, corBotao4);
             DrawText("CRÉDITOS", screenWidth/2 - MeasureText("CREDITOS", 60)/2, screenHeight/2 + 370, 60, BLACK);
             DrawTexture(cerebro, 820, 0, WHITE);
             //DrawTexture(interrogacao, 870, 35, WHITE);
             DrawTexture(lampada, 100, 500, WHITE);
             DrawTexture(atomo, 1350, 530, WHITE);

         }else if(escreverNome){
            DrawText("Digite seu nome:", screenWidth/2 - MeasureText("Digite seu nome:", 60)/2, screenHeight/2 - 300, 60, BLACK);
            DrawText("enviar", screenWidth/2 - MeasureText("enviar", 60)/2, screenHeight/2 - 80, 60, BLACK);
            DrawText("<", 40, 30, 100, BLACK);
            DrawRectangleRec(espacoNome, GRAY);
            DrawText(nome_jogador, screenWidth/2 - MeasureText(nome_jogador, 60)/2, screenHeight/2 - 200, 60, BLACK);

        } else if(noComoJogar){
            DrawText("Siga as instrucões a seguir:\n\n 1-Cada pergunta só possui uma resposta correta.\n 2-Caso erre, o jogo reinicia.\n 3-Algumas perguntas podem ser pegadinhas.\n 4-Você apenas obtém pontuação no Ranking\n    ao completar o jogo.", 250, screenHeight/2 - 300, 60, BLACK);
            //DrawRectangleRec(botaoSairF, GRAY);
            DrawText("<", 40, 30, 100, BLACK);

        } else if(noPlacar){
            carregarRanking();
            removerDuplicados();
            OrdenarRanking(jogadores, totalJogadores);

            // Desenha a lista no placar
            int y = 350;
            for (int i = 0; i < totalJogadores && i < 10; i++) {
                char texto[64];
                sprintf(texto, "%dº %s - %d pontos", i+1, jogadores[i].nome, jogadores[i].pontos);
                DrawText(texto, 700, y, 45, BLACK);
                y += 65;
            }

            DrawText("Placar", screenWidth/2 - MeasureText("Placar", 60)/2, screenHeight/2 - 300, 60, BLACK);
            DrawText("<", 40, 30, 100, BLACK);

        } else if(noCredito){
            DrawText("-Jeferson Roberto", screenWidth/2 - MeasureText("-Jeferson Roberto", 60) + 300, screenHeight/2 - 350, 60, BLACK);
            DrawText("-João Pedro", screenWidth/2 - MeasureText("-João Pedro", 60) + 200, screenHeight/2 - 300, 60, BLACK);
            DrawText("-Imagens do Google", screenWidth/2 - MeasureText("-Imagens do Google", 60) + 300, screenHeight/2 - 250, 60, BLACK);
             DrawText("-Musica 'fallen down' de UNDERTALE", screenWidth/2 - MeasureText("-Musica 'fallen down' de UNDERTALE", 60) + 570, screenHeight/2 - 190, 60, BLACK);
            DrawText("<", 40, 30, 100, BLACK);
            DrawText("Créditos", 850, 30, 60, BLACK);
            DrawTexture(meme, 710, 500, WHITE);

        } else if(telaVitoriaFinal){
            DrawTexture(cinema, 0, 0, WHITE);
            DrawText("VITORIA!!", screenWidth/2 - MeasureText("VITORIA!!", 100)/2, screenHeight/2 - 450, 100, LIME);
            DrawText("Pressione ENTER para continuar", screenWidth/2 - MeasureText("Pressione ENTER para continuar", 60)/2, screenHeight/2 + 100, 60, WHITE);
        
        } else if(telaVitoriaFinalDialogo){

            DrawTexture(palco, 0, 0, WHITE);
            sprintf(mensagem, "Parabêns %s!\nVocê venceu com %d pontos!!!", nome_jogador, pontosTotais);
            DrawText(mensagem, 200, screenHeight/2 - 350, 80, WHITE);
            DrawTexture(dialogo, 450, 450, WHITE);
            DrawText("Pressione ENTER para voltar ao menu", screenWidth/2 - MeasureText("Pressione ENTER para voltar ao menu", 60)/2, screenHeight/2 + 450, 60, WHITE);
        }

        else if(jogoAtivo) {
            DrawText(TextFormat("Pontos: %d", pontosTotais), screenWidth - 290, 20, 40, DARKGRAY);
            DrawText(TextFormat("Tempo: %.1f s", tempoRestante), 800, 20, 55, DARKGRAY);
            DrawText(TextFormat("Ganho atual: %d", pontosQuestao), screenWidth - 290, 90, 35, DARKGRAY);
            DrawText(questoes[questaoAtual].pergunta, screenWidth/2 - MeasureText(questoes[questaoAtual].pergunta, 60)/2, 150, 60, BLACK);

                for (int i = 0; i < 4; i++) {
                    bool hover;
                    Color corBotao;

                    hover = CheckCollisionPointRec(GetMousePosition(), botoes[i]);

                    if (hover) {
                        corBotao = (Color){  100, 100, 100, 255   };
                    } else {
                        corBotao = WHITE;
                    }

                    DrawTexture(botao, posicoes[i].x, posicoes[i].y, corBotao);

                    DrawText(questoes[questaoAtual].alternativas[i],
                             posicoes[i].x + 30,
                             posicoes[i].y + botao.height/2 - 25, 50, BLACK);
                    //imagens de algumas questoes
                    if(questaoAtual==0){
                        DrawTexture(graca, 820, 280, WHITE);
                    }
                       if(questaoAtual==2){
                        DrawTexture(roda25, 750, 290, WHITE);
                    }
                    if(questaoAtual==4){
                        DrawTexture(questaoY, 740, 280, WHITE);
                    }
                    if(questaoAtual==9){
                        DrawTexture(dado, 855, 260, WHITE);
                    }
                    if(questaoAtual==11){
                        DrawTexture(japao, 820, 270, WHITE);
                    }
                    if(questaoAtual==12){
                        DrawTexture(oli, 820, 300, WHITE);
                    }
                    if(questaoAtual==13){
                        DrawTexture(num23, 820, 230, WHITE);
                    }
                    if(questaoAtual==18){
                        DrawTexture(holanda, 820, 260, WHITE);
                    }
                    if(questaoAtual==24){
                        DrawTexture(logica4, 820, 220, WHITE);
                    }

                    //numero das questoes
                    if (questaoAtual == 0) {
                        DrawTexture(numero_questao1, 30, 30, WHITE);
                    }
                    if (questaoAtual == 1) {
                        DrawTexture(numero_questao2, 30, 30, WHITE);
                    }
                    if (questaoAtual == 2) {
                        DrawTexture(numero_questao3, 30, 30, WHITE);
                    }
                    if (questaoAtual == 3) {
                         DrawTexture(numero_questao4, 30, 30, WHITE);
                    }       
                    if (questaoAtual == 4) {
                        DrawTexture(numero_questao5, 30, 30, WHITE);
                    }
                    if (questaoAtual == 5) {
                        DrawTexture(numero_questao6, 30, 30, WHITE);
                    }
                    if (questaoAtual == 6) {
                        DrawTexture(numero_questao7, 30, 30, WHITE);
                    }
                    if (questaoAtual == 7) {
                        DrawTexture(numero_questao8, 30, 30, WHITE);
                    }
                    if (questaoAtual == 8) {
                        DrawTexture(numero_questao9, 30, 30, WHITE);
                    }
                    if (questaoAtual == 9) {
                        DrawTexture(numero_questao10, 30, 30, WHITE);
                    }
                    if (questaoAtual == 10) {
                        DrawTexture(numero_questao11, 30, 30, WHITE);
                    }
                    if (questaoAtual == 11) {
                        DrawTexture(numero_questao12, 30, 30, WHITE);
                    }
                    if (questaoAtual == 12) {
                     DrawTexture(numero_questao13, 30, 30, WHITE);
                    }
                    if (questaoAtual == 13) {
                        DrawTexture(numero_questao14, 30, 30, WHITE);
                    }
                    if (questaoAtual == 14) {
                        DrawTexture(numero_questao15, 30, 30, WHITE);
                    }
                    if (questaoAtual == 15) {
                        DrawTexture(numero_questao16, 30, 30, WHITE);
                    }
                    if (questaoAtual == 16) {
                        DrawTexture(numero_questao17, 30, 30, WHITE);
                    }
                    if (questaoAtual == 17) {
                        DrawTexture(numero_questao18, 30, 30, WHITE);
                    }
                    if (questaoAtual == 18) {
                        DrawTexture(numero_questao19, 30, 30, WHITE);
                    }
                    if (questaoAtual == 19) {
                        DrawTexture(numero_questao20, 30, 30, WHITE);
                    }
                    if (questaoAtual == 20) {
                        DrawTexture(numero_questao21, 30, 30, WHITE);
                    }
                    if (questaoAtual == 21) {
                        DrawTexture(numero_questao22, 30, 30, WHITE);
                    }
                    if (questaoAtual == 22) {
                        DrawTexture(numero_questao23, 30, 30, WHITE);
                    }
                    if (questaoAtual == 23) {
                        DrawTexture(numero_questao24, 30, 30, WHITE);
                    }
                    if (questaoAtual == 24) {
                        DrawTexture(numero_questao25, 30, 30, WHITE);
                    }
                }

            } else {
                if (tempoAcabou){
                     DrawTexture(pray, 0, 0, WHITE);
                    DrawText("Tempo esgotado!", screenWidth/2 - MeasureText("Tempo esgotado!", 110)/2, screenHeight/2 - 250, 110, ORANGE);
                     DrawText("Pressione ENTER para voltar ao menu", screenWidth/2 - MeasureText("Pressione ENTER para voltar ao menu", 60)/2, screenHeight/2 + 100, 60, WHITE);
                }
                else if (errou){
                     DrawTexture(amassado, 0, 0, WHITE);
                    DrawText("Errou!", screenWidth/2 - MeasureText("Errou!", 110)/2, screenHeight/2 - 200, 110, RED);

                DrawText("Pressione ENTER para voltar ao menu", screenWidth/2 - MeasureText("Pressione ENTER para voltar ao menu", 60)/2, screenHeight/2, 60, WHITE);
            }
         }
        

        EndDrawing();
    }

    UnloadMusicStream(menu);
    CloseAudioDevice();

    CloseWindow();
    return 0;
}