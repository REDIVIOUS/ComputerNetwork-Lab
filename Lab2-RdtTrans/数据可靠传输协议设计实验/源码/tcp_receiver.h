#include "RdtReceiver.h"
class tcp_receiver :public RdtReceiver
{
private:
	int expectSequenceNumberRcvd;	// �ڴ��յ�����һ���������
	Packet lastAckPkt;				//�ϴη��͵�ȷ�ϱ���
	const int k; //��ų���

public:
	tcp_receiver();
	virtual ~tcp_receiver();

public:
	void receive(const Packet& packet);	//���ձ��ģ�����NetworkService����
};