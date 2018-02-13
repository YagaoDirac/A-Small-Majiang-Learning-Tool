#include"Droped Cards Record.h"


DropedCardRecord::DropedCardRecord(GlobalObject * ȫ�ֱ���)
{
	ȫ�ֱ���->_DropedCardRecord = this;
	_global = ȫ�ֱ���;

	for (size_t i = 0; i < 9; i++)
		_droped_cards[i] = 0;
}

DropedCardRecord::~DropedCardRecord()
{
}

ErrorType DropedCardRecord::init()
{
	bool �Ƿ������ĳ�ʼ���������޸�(false);

//��������Χ������Ҫ�޸�
	for (size_t i = 0; i < 9; i++)
	{
		if (��ʼ����[i]<=0|| ��ʼ����[i]>=5)
		{
			�Ƿ������ĳ�ʼ���������޸� = true;
		}
		��ʼ����[i] = GlobalTool::clamp(��ʼ����[i], 1, 4);//�������齫�Ĺ�����ĳ���Ƶ�������Ϊ4����ô�޸�����ط�
	}
//����һ��
	for (size_t i = 0; i < 9; i++)
		_droped_cards[i] = ��ʼ����[i];

	if (�Ƿ������ĳ�ʼ���������޸�)
		return ErrorType::Almost_OK;
	else
		return ErrorType::OK;
}

ErrorType DropedCardRecord::getCount(int �Ʒ���,int* result)
{
	//����Ʒ���
	ErrorType temp = GlobalTool::_checkCardNumber(�Ʒ���);
	if (temp != ErrorType::OK)
		return temp;

	if (nullptr == result)
		return ErrorType::ָ��Ϊ��;

	*result = _droped_cards[�Ʒ��� - 1];
	return ErrorType::OK;
}

ErrorType DropedCardRecord::dropThisCard(int �Ʒ���)
{
	if (_droped_cards[�Ʒ��� - 1] >= 4)
		return ErrorType::�Ƴ���4��;

	_droped_cards[�Ʒ��� - 1] += 1;
	return ErrorType::OK;
}

ErrorType DropedCardRecord::checkTotalCounts(int ����[9])
{
	for (size_t i = 0; i < 9; i++)
	{
		if (����[i] + _droped_cards[i] >= 5)
			return ErrorType::�����ƶѵ��Ƴ�ͻ;
	}

	return ErrorType::OK;
}
