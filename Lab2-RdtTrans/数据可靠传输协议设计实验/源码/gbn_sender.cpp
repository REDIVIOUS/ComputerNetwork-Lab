#include "stdafx.h"
#include "gbn_sender.h"
#include "Global.h"
using namespace std;

gbn_sender::gbn_sender():N(4),k(8),sndwinbuf(new Packet [8])
{
	//����ź���һ����ų�ʼ��Ϊ0
	base = 0;
	nextseqnum = 0;
}

gbn_sender::~gbn_sender()
{
	delete[] sndwinbuf;
}

//�����ķ��͸����շ�
bool gbn_sender::send(const Message& message) {
	if (getWaitingState()) {
		pUtils->printPacket("���ͷ������ʹ��������޷�����",sndwinbuf[nextseqnum]);
		return false;
	}
	else if(insendbuf(nextseqnum)){ //������һ��Ҫ���ķ���
		sndwinbuf[nextseqnum].acknum = -1; //���Ը��ֶ�
		sndwinbuf[nextseqnum].seqnum = nextseqnum; //��һ��Ҫ���͵����кţ�
		sndwinbuf[nextseqnum].checksum = 0; //��ʼchecksum��0
		memcpy(sndwinbuf[nextseqnum].payload, message.data, sizeof(message.data)); //data
		sndwinbuf[nextseqnum].checksum = pUtils->calculateCheckSum(sndwinbuf[nextseqnum]); //����checksum
		//�����ķ��͸����շ�
		pUtils->printPacket("���ͷ������ͱ���", sndwinbuf[nextseqnum]);
		//����ǰ��������
		cout << "���ͷ�������ǰ�Ļ������ڣ�\n";
		showbuf();
		//gbnֻ��һ����ʱ������base=nextseqnumʱ��������ֻҪ�ü�ʱ����ʱ���ش����������з���
		if (base == nextseqnum) { 
			pns->startTimer(SENDER, Configuration::TIME_OUT, 0);
		}
		pns->sendToNetworkLayer(RECEIVER, sndwinbuf[nextseqnum]); //���ݸ������
		nextseqnum = (nextseqnum + 1) % k; //׼��������һ������
		//���ͺ󻬶�����
		cout << "���ͷ������ͺ�Ļ������ڣ�\n";
		showbuf();
		return true;
	}
}

//���ս��շ����ع����ı���
void gbn_sender::receive(const Packet& ackpkt)
{
	//�Ƚ�У��ͣ��������Ƿ���
	int checksum;
	checksum = pUtils->calculateCheckSum(ackpkt);
	if (checksum != ackpkt.checksum) {
		pUtils->printPacket("���ͷ�:У��Ͳ���ȷ��������", ackpkt);
	}
	else { //����׼�����շ��صı���
		if (insendbuf(ackpkt.acknum)) {
			cout << "���ͷ������յ�ACK��" << ackpkt.acknum << endl;
			base = (ackpkt.acknum + 1) % 8;
			pns->stopTimer(SENDER, 0);
			if (base != nextseqnum) { //base��nextseqnum���ȵ�ʱ��������ʱ��
				pns->startTimer(SENDER, Configuration::TIME_OUT, 0);
			}
			//����ACK��Ļ�������
			cout << "���ͷ�������ACK��Ļ������ڣ�\n";
			showbuf();
		}
	}
}

//�Ƿ�Ӧ�õȴ�
bool gbn_sender::getWaitingState() //trueΪ��������Ҫ�ȴ���
{
	int limitseq = base + N;
	int crntcap = limitseq % k; //Ŀǰ���������������
	int crntocup = nextseqnum % k; //Ŀǰռ�õ������
	return crntcap == crntocup;
}

//��ʱ��֮���ش��������
void gbn_sender::timeoutHandler(int seqnum)
{
	pUtils->printPacket("���ͷ����з��鷢����ʱ",sndwinbuf[base]);
	pns->sendToNetworkLayer(RECEIVER, sndwinbuf[base]);
	pns->stopTimer(SENDER, 0);
	pns->startTimer(SENDER, Configuration::TIME_OUT, 0);
	pUtils->printPacket("���ͷ����ش����", sndwinbuf[base]);
}


//�жϵ�ǰ�����Ƿ��ڷ��ͷ�������
bool gbn_sender::insendbuf(int seqnum)
{
	int end = (base + N) % k;
	//����������������Ƿ��ͷ�����ĩβ�����кŴ�����ʼ���кţ�֤����������
	if (base < end) {
		//�÷������к�seqnumҪ�����ڷ��ʹ��ڵ���β���֮��
		return seqnum < end && seqnum >= base;
	}
	else { 
		//����ĩβ���к�С����ʼ���кţ�
		//֤���������Ǵӿ�ʼ���кŵ�k-1,Ȼ���ٴ�0��ĩβ�����ǽ��������������Χ
		return seqnum >= base || seqnum < end;
	}
}

//��ӡ���ʹ���
void gbn_sender::showbuf()
{
	for (int i = 0; i < k; i++) { //�������ڿ�ͷ�������
		if (i == base) cout << "("; 
		cout << i; //��ӡ���
		if (i == nextseqnum) cout << "|"; //������һ�������ķ��飬����ָ���'|'
		if (i == (base + N) % k) cout << ")"; //�������ڽ�β���������
		cout << " ";
	}
	cout << "\n";
}