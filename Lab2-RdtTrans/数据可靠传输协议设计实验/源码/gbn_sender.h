#ifndef GBN_SENDER_H
#define GBN_SENDER_H
#include "DataStructure.h"
#include "RdtSender.h"
class gbn_sender :public RdtSender
{
private:
	int base, nextseqnum;	// ����ţ���һ����� 
	int N, k;		// ���ڴ�С����ų���
	Packet *sndwinbuf;		//���ʹ��ڻ�����

private:
	bool insendbuf(int seqnum); //�ڷ��ͷ��Ļ���������
	void showbuf(); //չʾ���ͷ��Ļ�������

public:
	bool getWaitingState();
	bool send(const Message& message);						//����Ӧ�ò�������Message����NetworkServiceSimulator����,������ͷ��ɹ��ؽ�Message���͵�����㣬����true;�����Ϊ���ͷ����ڵȴ���ȷȷ��״̬���ܾ�����Message���򷵻�false
	void receive(const Packet& ackpkt);						//����ȷ��Ack������NetworkServiceSimulator����	
	void timeoutHandler(int seqnum);					//Timeout handler������NetworkServiceSimulator����

public:
	gbn_sender();
	virtual ~gbn_sender();
};
#endif // !GBN_SENDER_H