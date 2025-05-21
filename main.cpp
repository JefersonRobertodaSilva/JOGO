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
    float ok;
    Texture2D questao1 = LoadTexture("C:/Users/jefer/Desktop/projeto_do_jogo/texturas/botaoquest.png");
    Vector2 posicao1 = { 440, 500 };
     Texture2D questao2 = LoadTexture("C:/Users/jefer/Desktop/projeto_do_jogo/texturas/botaoquest.png");
    Vector2 posicao2 = { 440, 775 };
     Texture2D questao3 = LoadTexture("C:/Users/jefer/Desktop/projeto_do_jogo/texturas/botaoquest.png");
    Vector2 posicao3 = { 1050, 500 };
    Texture2D questao4 = LoadTexture("C:/Users/jefer/Desktop/projeto_do_jogo/texturas/botaoquest.png");
    Vector2 posicao4 = { 1050, 775 };

    
    Texture2D numero = LoadTexture("C:/Users/jefer/Desktop/projeto_do_jogo/texturas/numero_questao.png");
    Vector2 numero_pos = { 50, 50 };
   

    float screenWidth = GetScreenWidth();
    float screenHeight = GetScreenHeight();

    SetTargetFPS(60);

    Questao questoes[] = {
        {"Quanto é 2 + 2?", {"1", "2", "3", "4"}, 3},
        {"Qual a capital do Brasil?", {"São Paulo", "Brasília", "Rio", "Curitiba"}, 1},
        {"Quantos dias tem uma semana?", {"5", "6", "7", "8"}, 2}
    };
    int totalQuestoes = sizeof(questoes) / sizeof(Questao);
    int questaoAtual = 0;

    Rectangle botoes[4];
    for (int i = 0; i < 4; i++) {
        ok=i;
        botoes[i] = (Rectangle){screenWidth/2 - 300, 200 + ok * 80, 600, 60};
    }

    bool noMenu = true;
    bool mostrandoResultado = false;
    bool errou = false;
    bool acertou = false;
    bool tempoAcabou = false;

    float tempoRestante = 10.0f;
    int pontosQuestao = 100;
    int pontosTotais = 0;

    while (!WindowShouldClose()) {
        if (noMenu) {
            if (IsKeyPressed(KEY_ENTER)) {
                noMenu = false;
                tempoRestante = 10.0f;
                pontosQuestao = 100;
                questaoAtual = 0;
                pontosTotais = 0;
                errou = false;
                acertou = false;
                tempoAcabou = false;
                mostrandoResultado = false;
            }
        } else if (!mostrandoResultado) {
            tempoRestante -= GetFrameTime();
            if (tempoRestante > 0.0f) {
                pontosQuestao = (int)(tempoRestante * 10.0f);
            } else {
                tempoRestante = 0.0f;
                pontosQuestao = 0;
                errou = true;
                tempoAcabou = true; // sinaliza que o tempo acabou
                mostrandoResultado = true;
            }

            for (int i = 0; i < 4; i++) {
                if (CheckCollisionPointRec(GetMousePosition(), botoes[i]) &&
                    IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    if (i == questoes[questaoAtual].respostaCorreta) {
                        acertou = true;
                        pontosTotais += pontosQuestao;
                    } else {
                        errou = true;
                    }
                    mostrandoResultado = true;
                    tempoAcabou = false; // Resposta foi dada, tempo acabou é falso
                }
            }
        } else {
            if (IsKeyPressed(KEY_ENTER)) {
                if (errou) {
                    // Reinicia tudo, volta para menu
                    noMenu = true;
                    pontosTotais = 0;
                    questaoAtual = 0;
                    errou = false;
                    acertou = false;
                    tempoAcabou = false;
                    mostrandoResultado = false;
                } else if (acertou) {
                    // Próxima questão
                    questaoAtual++;
                    if (questaoAtual >= totalQuestoes) {
                        // Acabou o quiz, volta para menu e zera tudo
                        noMenu = true;
                        pontosTotais = 0;
                        questaoAtual = 0;
                    }
                    tempoRestante = 10.0f;
                    pontosQuestao = 100;
                    acertou = false;
                    mostrandoResultado = false;
                    tempoAcabou = false;
                }
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);
    
        if (noMenu) {
            DrawText("GÊNIO QUIZ", screenWidth/2 - MeasureText("GÊNIO QUIZ", 60)/2, screenHeight/2 - 100, 60, DARKBLUE);
            DrawText("Pressione ENTER para começar", screenWidth/2 - MeasureText("Pressione ENTER para começar", 30)/2, screenHeight/2 + 20, 30, GRAY);
        } else {
            DrawText(TextFormat("Questão %d de %d", questaoAtual + 1, totalQuestoes), 20, 20, 30, DARKGRAY);
            DrawText(TextFormat("Pontos: %d", pontosTotais), screenWidth - 250, 20, 30, DARKGRAY);

            if (!mostrandoResultado) {
                DrawText(TextFormat("Tempo: %.1f s", tempoRestante), 20, 60, 25, DARKGRAY);
                DrawText(TextFormat("Pontos desta: %d", pontosQuestao), screenWidth - 250, 60, 25, DARKGRAY);
                
                DrawTextureV(questao1, posicao1, WHITE);
                DrawTextureV(questao2, posicao2, WHITE);
                DrawTextureV(questao3, posicao3, WHITE);
                DrawTextureV(questao4, posicao4, WHITE);
                DrawTextureV(numero, numero_pos, WHITE);


                DrawText(questoes[questaoAtual].pergunta, screenWidth/2 - MeasureText(questoes[questaoAtual].pergunta, 30)/2, 130, 30, BLACK);

                for (int i = 0; i < 4; i++) {
                    Color cor = LIGHTGRAY;
                    if (CheckCollisionPointRec(GetMousePosition(), botoes[i]))
                        cor = GRAY;
                    DrawRectangleRec(botoes[i], cor);
                    DrawText(questoes[questaoAtual].alternativas[i], botoes[i].x + 20, botoes[i].y + 15, 25, DARKGRAY);
                }
            } else {
                if (tempoAcabou) {
                    DrawText("Tempo esgotado!", screenWidth/2 - MeasureText("Tempo esgotado!", 60)/2, screenHeight/2 - 90, 60, ORANGE);
                }
                if (acertou)
                    DrawText("Acertou!", screenWidth/2 - MeasureText("Acertou!", 60)/2, screenHeight/2 - 30, 60, GREEN);
                else if (errou && !tempoAcabou)
                    DrawText("Errou!", screenWidth/2 - MeasureText("Errou!", 60)/2, screenHeight/2 - 30, 60, RED);

                DrawText("Pressione ENTER para continuar", screenWidth/2 - MeasureText("Pressione ENTER para continuar", 30)/2, screenHeight/2 + 60, 30, GRAY);
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
