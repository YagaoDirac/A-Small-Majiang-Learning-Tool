#pragma once
//#include<vector>
#include"Define.h"
#include"Droped Cards Record.h"
#include"Global Object.h"

class GlobalObject;

class HandCard
{
public:
	HandCard(GlobalObject* ȫ�ֱ���);
	~HandCard();

	//��ʼ��
public:
	ErrorType init(int ��ʼ����[9]);
	ErrorType init(char* str, int safeLength);

	//��Ҫ����
public:
	WinningState HasWon();
	ErrorType tryDropCard(int);
	ErrorType GetCard(int);
private:
	int _hand_cards[9];

public://������Ҫ�ĳ�˽��
	GlobalObject* _global;
};