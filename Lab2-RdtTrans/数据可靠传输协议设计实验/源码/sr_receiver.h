#include "RdtReceiver.h"
class sr_receiver :public RdtReceiver
{
private:
	int base; //���մ��ڻ����
	int N, k; //���մ��ڴ�С�����г���
	bool *ifrcv; //������ÿ��λ���Ƿ��н��ܵ�ֵ
	Packet *rcvwinbuf; //���շ����ڻ���
	Packet lastAckPkt;	//�ϴη��͵�ȷ�ϱ���

private:
	bool inrcvbuf(int seqnum); //�ڷ��ͷ��Ļ���������
	void showbuf(); //չʾ���ͷ��Ļ�������

public:
	sr_receiver();
	virtual ~sr_receiver();

public:
	void receive(const Packet& packet);	//���ձ��ģ�����NetworkService����
};