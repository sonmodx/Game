#define _CRT_SECURE_NO_WARNINGS
#include "ScoreBoard.h"

ScoreBoard::ScoreBoard()
{
}

ScoreBoard::~ScoreBoard()
{
}

void ScoreBoard::ReadFile()
{
    this->fp = fopen("config/Score.txt", "r");
    for (int i = 0; i < 5; i++)
    {
       (void)fscanf(fp, "%s", &temp);
        name[i] = temp;
       (void)fscanf(fp, "%d", &score[i]);
        this->userScore.push_back(make_pair(this->score[i], this->name[i]));
    }
}

void ScoreBoard::WriteFile(string name, unsigned int score)
{
    ReadFile();
    this->name[5] = name;
    this->score[5] = score;
    this->userScore.push_back(make_pair(this->score[5], this->name[5]));
    sort(this->userScore.begin(), this->userScore.end());
    fclose(this->fp);

    (void)fopen("config/Score.txt", "w");
    for (int i = 5; i >= 1; i--)
    {
        strcpy(temp, userScore[i].second.c_str());
        fprintf(fp, "%s %d\n", temp, userScore[i].first);
    }
    fclose(this->fp);

}