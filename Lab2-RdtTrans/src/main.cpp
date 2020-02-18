#include "stdafx.h"
#include "Global.h"
#include "RdtSender.h"
#include "RdtReceiver.h"
#include "gbn_sender.h"
#include "gbn_receiver.h"
#include "sr_sender.h"
#include "sr_receiver.h"
#include "tcp_sender.h"
#include "tcp_receiver.h"

int main(int argc, char* argv[])
{
	RdtSender* ps_gbn = new gbn_sender();
	RdtReceiver* pr_gbn = new gbn_receiver();
	RdtSender* ps_sr = new sr_sender();
	RdtReceiver* pr_sr = new sr_receiver();
	RdtSender* ps_tcp = new tcp_sender();
	RdtReceiver* pr_tcp = new tcp_receiver();
	// RdtReceiver* ps = new StopWaitRdtReceiver();
	// RdtSender* pr = new StopWaitRdtSender();

	//pns->setRunMode(0);  //VERBOSģʽ
	//pns->setRunMode(1);  //����ģʽ

	//gbn����
	pns->init();
	pns->setRtdSender(ps_gbn);
	pns->setRtdReceiver(pr_gbn);
	pns->setInputFile("C:\\Qt\\ComputerNetwork-Lab\\Lab2-RdtTrans\\input.txt");
	pns->setOutputFile("C:\\Qt\\ComputerNetwork-Lab\\Lab2-RdtTrans\\log\\gbn_output.txt");
	ofstream gbn_log;
	gbn_log.open("C:\\Qt\\ComputerNetwork-Lab\\Lab2-RdtTrans\\log\\gbn_out.log");
	cout.rdbuf(gbn_log.rdbuf());
	pns->start();

	////sr����
	//pns->init();
	//pns->setRtdSender(ps_sr);
	//pns->setRtdReceiver(pr_sr);
	//pns->setInputFile("C:\\Qt\\ComputerNetwork-Lab\\Lab2-RdtTrans\\input.txt");
	//pns->setOutputFile("C:\\Qt\\ComputerNetwork-Lab\\Lab2-RdtTrans\\log\\sr_output.txt");
	//ofstream sr_log;
	//sr_log.open("C:\\Qt\\ComputerNetwork-Lab\\Lab2-RdtTrans\\log\\sr_output.log");
	//cout.rdbuf(sr_log.rdbuf());
	//pns->start();

	////tcp����
	//pns->init();
	//pns->setRtdSender(ps_tcp);
	//pns->setRtdReceiver(pr_tcp);
	//pns->setInputFile("C:\\Qt\\ComputerNetwork-Lab\\Lab2-RdtTrans\\input.txt");
	//pns->setOutputFile("C:\\Qt\\ComputerNetwork-Lab\\Lab2-RdtTrans\\log\\tcp_output.txt");
	//ofstream tcp_log;
	//tcp_log.open("C:\\Qt\\ComputerNetwork-Lab\\Lab2-RdtTrans\\log\\tcp_output.log");
	//cout.rdbuf(tcp_log.rdbuf());
	//pns->start();

	delete ps_gbn;
	delete pr_gbn;
	delete ps_sr;
	delete pr_sr;
	delete ps_tcp;
	delete pr_tcp;
	delete pUtils;									//ָ��Ψһ�Ĺ�����ʵ����ֻ��main��������ǰdelete
	delete pns;										//ָ��Ψһ��ģ�����绷����ʵ����ֻ��main��������ǰdelete

	return 0;
}