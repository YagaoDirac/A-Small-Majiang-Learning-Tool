#pragma once
//#include"define.h"
#include"Global Tool.h"
#include"Global Object.h"

class GlobalObject;

class DropedCardRecord
{
public:
	DropedCardRecord(GlobalObject* ȫ�ֱ���);
	~DropedCardRecord();

//�ֶ���ʼ��
public:
	ErrorType init();

public:
	ErrorType getCount(int �Ʒ���, int * result);
	ErrorType dropThisCard(int �Ʒ���);
	ErrorType checkTotalCounts(int ����[9]);

public:
	int ��ʼ����[9];

private:
	int _droped_cards[9];

public://������Ҫ�ĳ�˽��
	GlobalObject* _global;
};

