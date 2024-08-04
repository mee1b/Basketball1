#include <iostream>
#include <ctime>
#include <string>
#include <cstdlib>
#include <windows.h>

/*  The basketball class - ��� ������������ ����, � ������� �� ���������� �
    ���� �������� � ����������� ������� ������������ ��������
    � ���� ������������ �������� ����������� ��� ������������� ������� ������ ����.
    �� ������ �������� ���� �������, � ����� �������������� ����� */

const int ATTACK_TIME = 24;

int startMenu();
void gameRules();
int choiceDefense();
int jumpBall();
int probabilityHit();
void attackShot(int& shot);
bool playerAttack(int& scorePlayer, int& scoreOpponent, int& shot, int& defense);
bool opponentAttack(int& scorePlayer, int& scoreOpponent, int& shot, int& defense, std::string opponentName);
bool rebound();
void game(int jump, int& scorePlayer, int& scoreOpponent, int& shot, int& defense, std::string opponentName, std::string myTeam);
void score(int scorePlayer, int scoreOpponent);

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int scorePlayer{ 0 }, scoreOpponent{ 0 }, shot;
    int startGame = startMenu();
    if (startGame == 3)
    {
        return 0;
    }
    std::cout << "����� ��������� ������� �����? ";
    int defense = choiceDefense();
    std::string opponentName, myTeam = "����������� �������";
    std::cout << "������� �������� ������� ����������: ";
    std::cin.ignore();
    std::getline(std::cin, opponentName);
    int jump = jumpBall();
    if (jump == 0)
    {
        std::cout << "����� ����������� ��� ����� � ���������� ����� �...\n";
        Sleep(1000);
        std::cout << "������������ ���������� " << myTeam << "\n\n";
    }
    else
    {
        std::cout << "����� ����������� ��� ����� � ���������� ����� �...\n";
        Sleep(1000);
        std::cout << "������������ ���������� " << opponentName << "\n\n";
    }
    game(jump, scorePlayer, scoreOpponent, shot, defense, opponentName, myTeam);
    std::cout << "\n������ �������, ������ ������� ����� �� �������!\n��������� ����� ��������� ����� �� ����� ��������!\n\n";
    std::system("pause");
    std::system("cls");
    std::cout << "���������� ������ ����! �������!!!\n\n";
    Sleep(1000);
    if (jump == 0)
    {
        jump = 1;
    }
    else
    {
        jump = 0;
    }
    game(jump, scorePlayer, scoreOpponent, shot, defense, opponentName, myTeam);
    std::cout << "��������� ������� ����� �������! ����� ���� �������!\n��������� ���� �� �����\n" << myTeam << ": " << scorePlayer << ' ' << opponentName << ": " << scoreOpponent << "\n";
    Sleep(1000);
    if (scorePlayer > scoreOpponent)
    {
        std::cout << "����������� " << myTeam << " � �������!";
    }
    else if (scorePlayer < scoreOpponent)
    {
        std::cout << "����������� " << opponentName << " � �������!";
    }
    else
    {
        std::cout << "������� ���������� �� �������, �� � ��������� ��� ������� ����������!\n\n";
    }

    return 0;
}

int startMenu()
{
    int startGame{};
    std::cout << "����� ���������� � ���� \"���������\"\n";
    std::cout << "1. ������� ����.\n";
    std::cout << "2. ������ ����.\n";
    std::cout << "3. ����� �� ����.\n\n";
    std::cout << "��� ����������� �������� ��������: ";
    std::cin >> startGame;
    std::cout << "\n";
    while (startGame == 1)
    {
        gameRules();
        std::cout << "1. ������� ����.\n";
        std::cout << "2. ������ ����.\n";
        std::cout << "3. ����� �� ����.\n\n";
        std::cout << "��� ����������� �������� ��������: ";
        std::cin >> startGame;
    }

    return startGame;
}

void gameRules()
{
    // ��������� ���� � ����������
    std::cout << "��� ������������� ���� ������������ ��������. ";
    std::cout << "�� ������ ��������� � ������������ ����� �������.\n";
    std::cout << "���� ������ 2 ����� �� 4 ������. ���� ����� ������ 24 �������\n\n";
    std::cout << "������� ������ ��������� �������:\n";
    std::cout << "1. ������� (�����������) ������ � ������;\n2. ������� (�����������) ������ � ������;\n3. ��� - ���;\n4. ���������� � ������(������ ������ 2 ����)\n\n";
    std::cout << "��� ������� ����� ������������ ���� � �� �� ������.\n�������� ����� ��������� �������:\n";
    std::cout << "6. �������� - ����������� ������(���� ���� ������� ������ �� 10%)\n";
    std::cout << "7. ������ ����� - �������� ������ �� ������� � ������� �������(���� �������� �������� ������ � ��� - ���� -10%),\n";
    std::cout << "�� ����������� �������� ������� ��� ������� ������� � ����������(���� �������� �������� ������ � ���������� + 15 %);\n"; 
    std::cout << "8. ������ ������ - �������� ������ �� ������� ������� � ����������(���� �������� �������� ������ � ���������� -10%),\n";
    std::cout << "�� ����������� �������� ������� ��� ��� - ����� � ������� �������(���� �������� ��� - ���� � ������� ������� + 15%);\n";
    std::cout << "9. ��� ������ - ������� �������� � ������(���������� ���� ������� ���������� ���� ������� +20%)\n";
    std::cout << "����� �������� ������, ������ ������� 0 � �������� ���������� ������.\n\n";
    std::system("pause");
    std::system("cls");
}

int choiceDefense()
{
    int defense{};
    std::cin >> defense;
    while(defense < 6 || defense > 9)
    {
        std::cout << "�� ����������� �� �� ��������� ��� �����, �������!\n����� ������� ��, ��� �� ��� �����!\n";
        std::cout << "����� ����� ���� ��������� �������? ";
        std::cin >> defense;
    }

    return defense;
}

int jumpBall()
{
    srand(static_cast<unsigned int>(time(0)));
    if ((rand() % 100 + 1) > 40)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

int probabilityHit()
{
    srand(static_cast<unsigned int>(time(0)));
    int hit = (rand() % 100) + 1;

    return hit;
}

void attackShot(int& shot)
{
    std::cout << "\n�������! ����� ������ ������ � ���� �����? ";
    std::cin >> shot;
    while (shot < 0 || shot > 4)
    {
        std::cout << "�� ����������� �� �� ��������� ����� ������, �������!\n����� ������� ��, ��� �� ��� �����!\n";
        std::cout << "����� ������ ������ � ���� �����? ";
        std::cin >> shot;
    }   
}

bool playerAttack(int& scorePlayer, int& scoreOpponent, int& shot, int& defense)
{
    int hit{ 0 };
    attackShot(shot);
    std::cout << "\n";
    if (shot == 0)
    {
        std::cout << "�������, ����� ����� ������ ������? ";
        defense = choiceDefense();
        attackShot(shot);
    }
    if (shot == 1)
    {
        //���� ������������ 40% - �������
        std::cout << "����������� ������!!!\n";
        hit = probabilityHit();
        switch (defense)
        {
        case 6:
            if (hit > 70)
            {
                std::cout << "��� ���� � �������!!!\n";
                scorePlayer += 3;
                score(scorePlayer, scoreOpponent);
                return true;
            }
            else
            {
                std::cout << "������! ��� � �������, ��� �� �� ���������?\n\n";
                return false;
            }
        case 7:
            if (hit > 45)
            {
                std::cout << "��� ���� � �������!!!\n";
                scorePlayer += 3;
                score(scorePlayer, scoreOpponent);
                return true;
            }
            else
            {
                std::cout << "������! ��� � �������, ��� �� �� ���������?\n\n";
                return false;
            }
        case 8:
            if (hit > 70)
            {
                std::cout << "��� ���� � �������!!!\n";
                scorePlayer += 3;
                score(scorePlayer, scoreOpponent);
                return true;
            }
            else
            {
                std::cout << "������! ��� � �������, ��� �� �� ���������?\n\n";
                return false;
            }
        case 9:
            if (hit > 40)
            {
                std::cout << "��� ���� � �������!!!\n";
                scorePlayer += 3;
                score(scorePlayer, scoreOpponent);
                return true;
            }
            else
            {
                std::cout << "������! ��� � �������, ��� �� �� ���������?\n\n";
                return false;
            }
        }

    }
    if (shot == 2)
    {
        //���� ������������ 50% - �������
        std::cout << "������� ������!!!\n";
        hit = probabilityHit();
        switch (defense)
        {
        case 6:
            if (hit > 60)
            {
                std::cout << "��� ���� � �������!!!\n";
                scorePlayer += 2;
                score(scorePlayer, scoreOpponent);
                return true;
            }
            else
            {
                std::cout << "������! ��� � �������, ��� �� �� ���������?\n\n";
                return false;
            }
        case 7:
            if (hit > 60)
            {
                std::cout << "��� ���� � �������!!!\n";
                scorePlayer += 2;
                score(scorePlayer, scoreOpponent);
                return true;
            }
            else
            {
                std::cout << "������! ��� � �������, ��� �� �� ���������?\n\n";
                return false;
            }
        case 8:
            if (hit > 35)
            {
                std::cout << "��� ���� � �������!!!\n";
                scorePlayer += 2;
                score(scorePlayer, scoreOpponent);
                return true;
            }
            else
            {
                std::cout << "������! ��� � �������, ��� �� �� ���������?\n\n";
                return false;
            }
        case 9:
            if (hit > 30)
            {
                std::cout << "��� ���� � �������!!!\n";
                scorePlayer += 2;
                score(scorePlayer, scoreOpponent);
                return true;
            }
            else
            {
                std::cout << "������! ��� � �������, ��� �� �� ���������?\n\n";
                return false;
            }
        }
    }
    if (shot == 3)
    {
        //���� ��� - ���� 60% - �������
        std::cout << "��� �� ��� - ���!!!\n";
        hit = probabilityHit();
        switch (defense)
        {
        case 6:
            if (hit > 50)
            {
                std::cout << "��� ���� � �������!!!\n";
                scorePlayer += 2;
                score(scorePlayer, scoreOpponent);
                return true;
            }
            else
            {
                std::cout << "������! ��� � �������, ��� �� �� ���������?\n\n";
                return false;
            }
        case 7:
            if (hit > 50)
            {
                std::cout << "��� ���� � �������!!!\n";
                scorePlayer += 2;
                score(scorePlayer, scoreOpponent);
                return true;
            }
            else
            {
                std::cout << "������! ��� � �������, ��� �� �� ���������?\n\n";
                return false;
            }
        case 8:
            if (hit > 25)
            {
                std::cout << "��� ���� � �������!!!\n";
                scorePlayer += 2;
                score(scorePlayer, scoreOpponent);
                return true;
            }
            else
            {
                std::cout << "������! ��� � �������, ��� �� �� ���������?\n\n";
                return false;
            }
        case 9:
            if (hit > 20)
            {
                std::cout << "��� ���� � �������!!!\n";
                scorePlayer += 2;
                score(scorePlayer, scoreOpponent);
                return true;
            }
            else
            {
                std::cout << "������! ��� � �������, ��� �� �� ���������?\n\n";
                return false;
            }
        }
    }
    if (shot == 4)
    {
        //���� ���������� 55% - �������
        std::cout << "��������, ������ ����������� ����������!!!\n";
        hit = probabilityHit();
        switch (defense)
        {
        case 6:
            if (hit > 65)
            {
                std::cout << "��� ���� � �������!!!\n";
                scorePlayer += 2;
                score(scorePlayer, scoreOpponent);
                return true;
            }
            else
            {
                std::cout << "������! ��� � �������, ��� �� �� ���������?\n\n";
                return false;
            }
        case 7:
            if (hit > 40)
            {
                std::cout << "��� ���� � �������!!!\n";
                scorePlayer += 2;
                score(scorePlayer, scoreOpponent);
                return true;
            }
            else
            {
                std::cout << "������! ��� � �������, ��� �� �� ���������?\n\n";
                return false;
            }
        case 8:
            if (hit > 65)
            {
                std::cout << "��� ���� � �������!!!\n";
                scorePlayer += 2;
                score(scorePlayer, scoreOpponent);
                return true;
            }
            else
            {
                std::cout << "������! ��� � �������, ��� �� �� ���������?\n\n";
                return false;
            }
        case 9:
            if (hit > 35)
            {
                std::cout << "��� ���� � �������!!!\n";
                scorePlayer += 2;
                score(scorePlayer, scoreOpponent);
                return true;
            }
            else
            {
                std::cout << "������! ��� � �������, ��� �� �� ���������?\n\n";
                return false;
            }
        }
    }
    std::cout << "\n\n";
    Sleep(1000);
}

bool opponentAttack(int& scorePlayer, int& scoreOpponent, int& shot, int& defense, std::string opponentName)
{
    int hit{ 0 };
    srand(static_cast<unsigned int>(time(0)));
    shot = (rand() % 4) + 1;
    std::cout << opponentName << " � �����:\n";
    if (shot == 1)
    {
        //���� ������������ 40% - �������
        std::cout << "����������� ������!!!\n";
        hit = probabilityHit();
        switch (defense)
        {
        case 6:
            if (hit > 70)
            {
                std::cout << "��� ���� � �������!!!\n";
                scoreOpponent += 3;
                score(scorePlayer, scoreOpponent);
                return true;
            }
            else
            {
                std::cout << "������! ��� � �������, ��� �� �� ���������?\n\n";
                return false;
            }
        case 7:
            if (hit > 45)
            {
                std::cout << "��� ���� � �������!!!\n";
                scoreOpponent += 3;
                score(scorePlayer, scoreOpponent);
                return true;
            }
            else
            {
                std::cout << "������! ��� � �������, ��� �� �� ���������?\n\n";
                return false;
            }
        case 8:
            if (hit > 70)
            {
                std::cout << "��� ���� � �������!!!\n";
                scoreOpponent += 3;
                score(scorePlayer, scoreOpponent);
                return true;
            }
            else
            {
                std::cout << "������! ��� � �������, ��� �� �� ���������?\n\n";
                return false;
            }
        case 9:
            if (hit > 40)
            {
                std::cout << "��� ���� � �������!!!\n";
                scoreOpponent += 3;
                score(scorePlayer, scoreOpponent);
                return true;
            }
            else
            {
                std::cout << "������! ��� � �������, ��� �� �� ���������?\n\n";
                return false;
            }
        }

    }
    if (shot == 2)
    {
        //���� ������������ 50% - �������
        std::cout << "������� ������!!!\n";
        hit = probabilityHit();
        switch (defense)
        {
        case 6:
            if (hit > 60)
            {
                std::cout << "��� ���� � �������!!!\n";
                scoreOpponent += 2;
                score(scorePlayer, scoreOpponent);
                return true;
            }
            else
            {
                std::cout << "������! ��� � �������, ��� �� �� ���������?\n\n";
                return false;
            }
        case 7:
            if (hit > 60)
            {
                std::cout << "��� ���� � �������!!!\n";
                scoreOpponent += 2;
                score(scorePlayer, scoreOpponent);
                return true;
            }
            else
            {
                std::cout << "������! ��� � �������, ��� �� �� ���������?\n\n";
                return false;
            }
        case 8:
            if (hit > 35)
            {
                std::cout << "��� ���� � �������!!!\n";
                scoreOpponent += 2;
                score(scorePlayer, scoreOpponent);
                return true;
            }
            else
            {
                std::cout << "������! ��� � �������, ��� �� �� ���������?\n\n";
                return false;
            }
        case 9:
            if (hit > 30)
            {
                std::cout << "��� ���� � �������!!!\n";
                scoreOpponent += 2;
                score(scorePlayer, scoreOpponent);
                return true;
            }
            else
            {
                std::cout << "������! ��� � �������, ��� �� �� ���������?\n\n";
                return false;
            }
        }
    }
    if (shot == 3)
    {
        //���� ��� - ���� 60% - �������
        std::cout << "��� �� ��� - ���!!!\n";
        hit = probabilityHit();
        switch (defense)
        {
        case 6:
            if (hit > 50)
            {
                std::cout << "��� ���� � �������!!!\n";
                scoreOpponent += 2;
                score(scorePlayer, scoreOpponent);
                return true;
            }
            else
            {
                std::cout << "������! ��� � �������, ��� �� �� ���������?\n\n";
                return false;
            }
        case 7:
            if (hit > 50)
            {
                std::cout << "��� ���� � �������!!!\n";
                scoreOpponent += 2;
                score(scorePlayer, scoreOpponent);
                return true;
            }
            else
            {
                std::cout << "������! ��� � �������, ��� �� �� ���������?\n\n";
                return false;
            }
        case 8:
            if (hit > 25)
            {
                std::cout << "��� ���� � �������!!!\n";
                scoreOpponent += 2;
                score(scorePlayer, scoreOpponent);
                return true;
            }
            else
            {
                std::cout << "������! ��� � �������, ��� �� �� ���������?\n\n";
                return false;
            }
        case 9:
            if (hit > 20)
            {
                std::cout << "��� ���� � �������!!!\n";
                scoreOpponent += 2;
                score(scorePlayer, scoreOpponent);
                return true;
            }
            else
            {
                std::cout << "������! ��� � �������, ��� �� �� ���������?\n\n";
                return false;
            }
        }
    }
    if (shot == 4)
    {
        //���� ���������� 55% - �������
        std::cout << "��������, ������ ����������� ����������!!!\n";
        hit = probabilityHit();
        switch (defense)
        {
        case 6:
            if (hit > 65)
            {
                std::cout << "��� ���� � �������!!!\n";
                scoreOpponent += 2;
                score(scorePlayer, scoreOpponent);
                return true;
            }
            else
            {
                std::cout << "������! ��� � �������, ��� �� �� ���������?\n\n";
                return false;
            }
        case 7:
            if (hit > 40)
            {
                std::cout << "��� ���� � �������!!!\n";
                scoreOpponent += 2;
                score(scorePlayer, scoreOpponent);
                return true;
            }
            else
            {
                std::cout << "������! ��� � �������, ��� �� �� ���������?\n\n";
                return false;
            }
        case 8:
            if (hit > 65)
            {
                std::cout << "��� ���� � �������!!!\n";
                scoreOpponent += 2;
                score(scorePlayer, scoreOpponent);
                return true;
            }
            else
            {
                std::cout << "������! ��� � �������, ��� �� �� ���������?\n\n";
                return false;
            }
        case 9:
            if (hit > 35)
            {
                std::cout << "��� ���� � �������!!!\n";
                scoreOpponent += 2;
                score(scorePlayer, scoreOpponent);
                return true;
            }
            else
            {
                std::cout << "������! ��� � �������, ��� �� �� ���������?\n\n";
                return false;
            }
        }
    }
    std::cout << "\n\n";
    Sleep(1000);
}

bool rebound()
{
    srand(static_cast<unsigned int>(time(0)));
    if ((rand() % 100 + 1) > 75)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void game(int jump, int& scorePlayer, int& scoreOpponent, int& shot, int& defense, std::string opponentName, std::string myTeam)
{
    int period{ 0 };
    while (period < 120)
    {
        if (jump == 0)
        {
            if (!playerAttack(scorePlayer, scoreOpponent, shot, defense))
            {
                if (rebound())
                {
                    std::cout << "������ � ����� �� " << myTeam << "\n\n";
                    period += ATTACK_TIME;
                    continue;
                }
                else
                {
                    std::cout << "������ � ������ �� " << opponentName << "\n\n";
                    period += ATTACK_TIME;
                }
            }
            else
            {
                period += ATTACK_TIME;
            }
            if (!opponentAttack(scorePlayer, scoreOpponent, shot, defense, opponentName))
            {
                if (rebound())
                {
                    std::cout << "������ � ����� �� " << opponentName << "\n\n";
                    period += ATTACK_TIME;
                    opponentAttack(scorePlayer, scoreOpponent, shot, defense, opponentName);
                    period += ATTACK_TIME;
                }
                else
                {
                    std::cout << "������ � ������ �� " << myTeam << "\n\n";
                    period += ATTACK_TIME;
                }
            }
            else
            {
                period += ATTACK_TIME;
            }
        }
        else if (jump == 1)
        {
            if (!opponentAttack(scorePlayer, scoreOpponent, shot, defense, opponentName))
            {
                if (rebound())
                {
                    std::cout << "������ � ����� �� " << opponentName << "\n\n";
                    period += ATTACK_TIME;
                    continue;
                }
                else
                {
                    std::cout << "������ � ������ �� " << myTeam << "\n\n";
                    period += ATTACK_TIME;
                }
            }
            else
            {
                period += ATTACK_TIME;
            }
            if (!playerAttack(scorePlayer, scoreOpponent, shot, defense))
            {
                if (rebound())
                {
                    std::cout << "������ � ����� �� " << myTeam << "\n\n";
                    period += ATTACK_TIME;
                    playerAttack(scorePlayer, scoreOpponent, shot, defense);
                    period += ATTACK_TIME;
                }
                else
                {
                    std::cout << "������ � ������ �� " << opponentName << "\n\n";
                    period += ATTACK_TIME;
                }
            }
            else
            {
                period += ATTACK_TIME;
            }
        }
    }
}

void score(int scorePlayer, int scoreOpponent)
{
    std::cout << "����: " << scorePlayer << ' ' << scoreOpponent << "\n\n";
}