#include "RdtReceiver.h"
class gbn_receiver :public RdtReceiver
{
private:
	int expectSequenceNumberRcvd;	// �ڴ��յ�����һ���������
	Packet lastAckPkt;				//�ϴη��͵�ȷ�ϱ���
	const int k; //��ų���

public:
	gbn_receiver();
	virtual ~gbn_receiver();

public:
	void receive(const Packet& packet);	//���ձ��ģ�����NetworkService����
};