#include "Hand Card.h"



HandCard::HandCard(GlobalObject * ȫ�ֱ���)
{
	ȫ�ֱ���->_HandCard = this;
	_global = ȫ�ֱ���;

	for (size_t i = 0; i < 9; i++)
		_hand_cards[i] = 0;
}

HandCard::~HandCard()
{
}

ErrorType HandCard::init(int ��ʼ����[9])
{
	bool ������ֵ�����޸�(false);
	
	for (size_t i = 0; i < 9; i++)
	{
		if (��ʼ����[i] < 0 || ��ʼ����[i] >= 5)
			������ֵ�����޸� = true;
		��ʼ����[i] = GlobalTool::clamp(��ʼ����[i], 0, 4);
	}

	//�������ƶѵ����е����Ƿ��ͻ
	ErrorType temp = _global->getDropedCardRecord()->checkTotalCounts(��ʼ����);
	if (temp != ErrorType::OK)
		return temp;

	for (size_t i = 0; i < 9; i++)
	{
		_hand_cards[i] = ��ʼ����[i];
	}


	if (������ֵ�����޸�)
		return ErrorType::Almost_OK;
	else
		return ErrorType::OK;
}

ErrorType HandCard::init(char * str, int safeLength)
{
	if (safeLength <= 0)
		return ErrorType::Bad_Param;
	char* buf = new char[safeLength];
	memcpy(buf, str, safeLength);
	buf[safeLength - 1] = 0;

	GlobalTool::text_2_cards(buf, safeLength, _hand_cards);
	delete[]buf;
	
	//�����ر�������
	bool ������������(true);
	for (size_t i = 0; i < 9; i++)
	{
		_hand_cards[i] = GlobalTool::clamp(_hand_cards[i], 0, 4);
		������������ = false;
	}
	
	if (������������)
		return ErrorType::OK;
	else
		return ErrorType::Almost_OK;
}



WinningState HandCard::HasWon()
{
	int ������(0);
	for (size_t i = 0; i < 9; i++)
		������ += _hand_cards[i];

	if (0 == ������)
		return WinningState::��������е���;

	//3n+1���ǿ϶�û��˵����
	if (������ % 3 == 1)
		return WinningState::Not_yet;

	//3n��ʱ��Ͷ���3��һ��
	if (������ % 3 == 0)
	{
		int ���������[9];
		for (size_t i = 0; i < 9; i++)
		{
			���������[i] = _hand_cards[i];
		}
		

		//������������ɻ�

		//�����˼·���а��ӵĻ�������ϣ�Ȼ��ֱ��ȥ����������������������ơ�
		//һ����������ǣ������111222333����ô����ư����Ӻ�˳����ϣ����Ƿ�Ӯ��û��Ӱ��ģ��������������Ҫ�õ��Ľ��Ҳ��û��Ӱ�졣
		for (size_t i = 0; i < 9; i++)
		{
			if (0 == ������)
				return WinningState::Win;
			//�а��ӵĻ�ֱ��ȥ��
			if (���������[i] >= 3)
			{
				���������[i] -= 3;
				������ -= 3;
			}
			//û������ƾ�ֱ�Ӽ��������
			if (0 == ���������[i])
				continue;
			//û�а��ӵ�ʱ����2�����飬�����˳�Ӳ�����i�Ƿ����7
			if (1 == ���������[i] ||2 == ���������[i])
			{
				int ���Ƶ�����(���������[i]);
				if (i > 7)
					return WinningState::Not_yet;
				if (���������[i + 1]<���Ƶ����� || ���������[i + 2]<���Ƶ�����)
					return WinningState::Not_yet;

				���������[i] -= ���Ƶ�����;
				���������[i + 1] -= ���Ƶ�����;
				���������[i + 2] -= ���Ƶ�����;
				������ -= 3;
			}
		}//for i 0 9
	}//if (������ % 3 == 0)



	//3n+2�����Ҫ���жϽ�
	if (������ % 3 == 2)
	{
		int ���������[9];
		for (size_t i = 0; i < 9; i++)
		{
			���������[i] = _hand_cards[i];
		}
		int temp������(������);
		//������������ɻ�

		//˼·�ǣ����ҽ����ҵ����Ժ��ӵ���Ȼ������� (������ % 3 == 0) �����
		for (size_t ���ķ��� = 0; ���ķ��� < 9; ���ķ���++)
		{
			if (_hand_cards[���ķ���] >= 2)
			{
				//���õ���
				_hand_cards[���ķ���] -= 2;
				temp������ -= 2;

				//

				for (size_t i = 0; i < 9; i++)
				{
					if (0 == temp������)
						return WinningState::Win;
					//�а��ӵĻ�ֱ��ȥ��
					if (���������[i] >= 3)
					{
						���������[i] -= 3;
						temp������ -= 3;
					}
					//û������ƾ�ֱ�Ӽ��������
					if (0 == ���������[i])
						continue;
					//û�а��ӵ�ʱ����2�����飬�����˳�Ӳ�����i�Ƿ����7
					if (1 == ���������[i] || 2 == ���������[i])
					{
						int ���Ƶ�����(���������[i]);
						if (i > 7)
							return WinningState::Not_yet;
						if (���������[i + 1]<���Ƶ����� || ���������[i + 2]<���Ƶ�����)
							return WinningState::Not_yet;

						���������[i] -= ���Ƶ�����;
						���������[i + 1] -= ���Ƶ�����;
						���������[i + 2] -= ���Ƶ�����;
						temp������ -= 3;
					}
				}//for i 0 9
			}
		}
	}//if (������ % 3 == 2)


	//���һ�������û�õ�������Ū����
	return WinningState::Bad_Code;
}

ErrorType HandCard::tryDropCard(int �Ʒ���)
{
	if (_hand_cards[�Ʒ��� - 1] <= 0)
		return ErrorType::�Ʋ���;
	
	ErrorType temp = _global->getDropedCardRecord()->dropThisCard(�Ʒ���);
	if (ErrorType::OK != temp)
		return temp;
	else
	{
		_hand_cards[�Ʒ��� - 1] -= 1;
		return ErrorType::OK;
	}
}

ErrorType HandCard::GetCard(int �Ʒ���)
{
	//���Ƿ񳬹�4��
	if (�Ʒ��� <= 0 || �Ʒ��� >= 10)
		return ErrorType::�Ʒ��Ŵ���;

	//�����ƶѼ��������
	int ���ƶ��еĸ�������;
	_global->getDropedCardRecord()->getCount(�Ʒ���, &���ƶ��еĸ�������);
	if (���ƶ��еĸ������� + HandCard::_hand_cards[�Ʒ��� - 1] >= 4)
		return ErrorType::�����ƶѵ��Ƴ�ͻ;
	//����һ����������������Լ�������4����


	//��������
	_hand_cards[�Ʒ��� - 1] += 1;
	return ErrorType::OK;
}
