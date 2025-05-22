#include "raylib.h"
#include <stdio.h>

typedef struct {
    const char *pergunta;
    const char *alternativas[4];
    int respostaCorreta;
} Questao;

int main(void) {
    InitWindow(0, 0, "Gênio Quiz");
    ToggleFullscreen();

    float screenWidth = GetScreenWidth();
    float screenHeight = GetScreenHeight();

    SetTargetFPS(60);

    // Carregar texturas
    Texture2D botao = LoadTexture("C:/Users/jefer/Desktop/projeto_do_jogo/texturas/botaoquest.png");
    Texture2D numero = LoadTexture("C:/Users/jefer/Desktop/projeto_do_jogo/texturas/numero_questao.png");


    //botoes
    //alternativas
    Vector2 posicoes[4] = {
        { 440, 500 },
        { 440, 800 },
        { 1050, 500 },
        { 1050, 800 }
    };

    Rectangle botoes[4];
    for (int i = 0; i < 4; i++) {
        botoes[i] = (Rectangle){ posicoes[i].x, posicoes[i].y, botao.width, botao.height };
    }

    //botao play
    Rectangle botaoIniciar = { screenWidth/2 - 200, screenHeight/2 -100, 400, 100 };
    Rectangle botaoComoJogar = { screenWidth/2 - 200, screenHeight/2 + 50, 400, 100};
    Rectangle botaoPlacar = {screenWidth/2 -200, screenHeight/2 + 200, 400, 100};
    Rectangle botaoCredito = {screenWidth/2 -200, screenHeight/2 + 350, 400, 100};
    Rectangle botaoSairF = {25, 30, 70, 70};

    //posicao do numero da questao
    Vector2 numero_pos = { 50, 50 };

    // a escriyta das Questões
    Questao questoes[] = {
        {"Quanto é 2 + 2?", {"1", "2", "3", "4"}, 3},
        {"Qual a capital do Brasil?", {"São Paulo", "Brasília", "Rio", "Curitiba"}, 1},
        {"Quantos dias tem uma semana?", {"5", "6", "7", "8"}, 2}
    };
    int totalQuestoes = sizeof(questoes) / sizeof(Questao);
    int questaoAtual = 0;

    // Estados 1 ou 0
    bool noMenu = true;
    bool noComoJogar = false;
    bool noPlacar= false;
    bool noCredito= false;
    bool mostrandoResultado = false;
    bool errou = false;
    bool tempoAcabou = false;
    bool botaoSair = false;

    float tempoRestante = 20.0f;
    int pontosQuestao = 100;
    int pontosTotais = 0;

    while (!WindowShouldClose()) {

        if (noMenu) {
            Vector2 mousePos = GetMousePosition();
            //iniciar
                 if (CheckCollisionPointRec(mousePos, botaoIniciar) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    noMenu = false;
                    tempoRestante = 20.0f;
                    pontosQuestao = 100;
                    questaoAtual = 0;
                    pontosTotais = 0;
                    errou = false;
                    mostrandoResultado = false;
                    tempoAcabou = false;
                  }
                  //como  jogar
                  else if(CheckCollisionPointRec(mousePos, botaoComoJogar) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                    noComoJogar= true;
                    noMenu= false;
                }

    } else if(noComoJogar){
         Vector2 mousePos = GetMousePosition();
            botaoSair= true;
            if(CheckCollisionPointRec(mousePos, botaoSairF) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                noMenu= true;
                noComoJogar= false;
            }

        } else if (!mostrandoResultado) {
            tempoRestante -= GetFrameTime();
            if (tempoRestante > 0.0f) {
                pontosQuestao = (int)(tempoRestante * 5.0f);
            } else {
                tempoRestante = 0.0f;
                pontosQuestao = 0;
                errou = true;
                tempoAcabou = true;
                mostrandoResultado = true;
            }

            for (int i = 0; i < 4; i++) {
                if (CheckCollisionPointRec(GetMousePosition(), botoes[i]) &&
                    IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    if (i == questoes[questaoAtual].respostaCorreta) {
                        pontosTotais += pontosQuestao;

                        // Avança para a próxima questão automaticamente
                        questaoAtual++;
                        if (questaoAtual >= totalQuestoes) {
                            noMenu = true;
                            pontosTotais = 0;
                            questaoAtual = 0;
                        }
                        // Reinicia timer e pontos
                        tempoRestante = 20.0f;
                        pontosQuestao = 100;
                        mostrandoResultado = false;
                        errou = false;
                        tempoAcabou = false;
                    } else {
                        errou = true;
                        mostrandoResultado = true;
                        tempoAcabou = false;
                    }
                }
            }
        } else {
            // Aqui só espera ENTER para voltar ao menu se errou ou tempo esgotou
            if (IsKeyPressed(KEY_ENTER)) {
                if (errou) {
                    noMenu = true;
                    pontosTotais = 0;
                    questaoAtual = 0;
                    errou = false;
                    mostrandoResultado = false;
                    tempoAcabou = false;
                }
            }
        }

        // Desenho
        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (noMenu) {
             DrawText("GÊNIO QUIZ", screenWidth/2 - MeasureText("GÊNIO QUIZ", 120)/2, screenHeight/2 - 300, 120, BLACK);
             DrawRectangleRec(botaoIniciar, GRAY);
             DrawText("JOGAR", screenWidth/2 - MeasureText("JOGAR", 60)/2, screenHeight/2 - 80, 60, BLACK);
             DrawRectangleRec(botaoComoJogar, GRAY);
             DrawText("COMO JOGAR", screenWidth/2 -MeasureText("COMO JOGAR", 57)/2, screenHeight/2 + 70, 57, BLACK);
             DrawRectangleRec(botaoPlacar, GRAY);
             DrawText("PLACAR", screenWidth/2 - MeasureText("PLACAR", 60)/2, screenHeight/2 + 220, 60, BLACK);
             DrawRectangleRec(botaoCredito, GRAY);
             DrawText("CREDITOS", screenWidth/2 - MeasureText("CREDITOS", 60)/2, screenHeight/2 + 370, 60, BLACK);

        } else if(noComoJogar){
            DrawText("so responder la mano lol", screenWidth/2 - MeasureText("GÊNIO QUIZ", 120)/2, screenHeight/2 - 300, 120, BLACK);
            //DrawRectangleRec(botaoSairF, GRAY);
            DrawText("<", 40, 30, 100, BLACK);

        }
        
        
        
        
        else {
            DrawTexture(numero, numero_pos.x, numero_pos.y, WHITE);
            DrawText(TextFormat("%d", questaoAtual + 1), 90, 70, 90, BLACK);
            DrawText(TextFormat("Pontos: %d", pontosTotais), screenWidth - 290, 20, 40, DARKGRAY);

            if (!mostrandoResultado) {
                DrawText(TextFormat("Tempo: %.1f s", tempoRestante), 800, 20, 55, DARKGRAY);
                DrawText(TextFormat("Ganho atual: %d", pontosQuestao), screenWidth - 290, 90, 35, DARKGRAY);

                DrawText(questoes[questaoAtual].pergunta,
                         screenWidth/2 - MeasureText(questoes[questaoAtual].pergunta, 60)/2,
                         150, 60, BLACK);

                for (int i = 0; i < 4; i++) {
                    bool hover = CheckCollisionPointRec(GetMousePosition(), botoes[i]);
                    Color corBotao = hover ? (Color){ 200, 200, 200, 255 } : WHITE;

                    DrawTexture(botao, posicoes[i].x, posicoes[i].y, corBotao);

                    DrawText(questoes[questaoAtual].alternativas[i],
                             posicoes[i].x + 30,
                             posicoes[i].y + botao.height/2 - 25,
                             50, DARKGRAY);
                }

            } else {
                if (tempoAcabou)
                    DrawText("Tempo esgotado!", screenWidth/2 - MeasureText("Tempo esgotado!", 110)/2, screenHeight/2 - 100, 110, ORANGE);
                else if (errou)
                    DrawText("Errou!", screenWidth/2 - MeasureText("Errou!", 110)/2, screenHeight/2 - 30, 110, RED);

                DrawText("Pressione ENTER para voltar ao menu", screenWidth/2 - MeasureText("Pressione ENTER para voltar ao menu", 60)/2, screenHeight/2 + 100, 60, GRAY);
            }
        }

        EndDrawing();
    }

    UnloadTexture(botao);
    UnloadTexture(numero);

    CloseWindow();
    return 0;
}
