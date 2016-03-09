#include <iostream>
#include <fstream>
#include <string>
#include <cerrno>
#include <math.h>
#include <time.h>
using namespace std;

//C++ API����,��ô��˲���ȡ��300M���ļ���
//�汾���²���

int main()
{
    const int TimeFlagStartPosi = 13;//�����е�ʱ���ʶ��ʼλ�ã���׼֡����չ֡ͨ��
	const int MinLengthofOneLine = 93; //�ӵ�0�п�ʼ��ʱ���ʶΪ0.0000��ʽʱ����С���ַ���
	const int MinLengthofTimeFlag = 6;//ʱ���ʶ��ʽλ��Ϊ0.0000ʱ��ĳ���
	//����ı������Ͷ����أ�����int��ô��
	//�����������ʱ��c
	clock_t start,finish;
   double totaltime;
   start=clock();
   //���ö�ȡ���ļ�����ʵֱ�����ļ������ɵ�exe����Ҳ�ǿ��Ե������
   std::ifstream in("ZLG.txt", std::ios::in | std::ios::binary);
   std::ofstream OutputFiles("TestResult.asc");//,ios::out | ios::binary | ios::app);//���������Щ��ʽ�Ļ�������Ͳ��ܺúõ�д���ļ�����
	std::string contents;
  //��ǰѭ�����з��ŵ�λ�ã��Լ���һ��ѭ�����з��ŵ�λ��
  string::size_type CurrentLFPosition = 0,LastLFPosition = 0;//��string�����ͺ�vector�����Ͷ�������ͣ����Ա�������string�����vector����ĳ���
  if (in)//?
	 {
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
	  }
  //�����н�����ʶ��
  string LF = "\n";
  double LineNumber = -2;//������-2147483648~+2147483647��2^32,Ҫ�������в��а�
  int LineNumberOffset = 0;//�б���������ӵ��º����ַ�λ����������ƫ��
  int FlagTypeIndicator = 0;//����ʱ���ʶ���ͣ�֡ID���ͣ�����������ZLG�ļ���ʽ����VDCI�ļ���ʽ
  while((CurrentLFPosition = contents.find_first_of(LF,CurrentLFPosition)) != string::npos
	  && FlagTypeIndicator != )
  {
	LineNumber++;

  while((CurrentLFPosition = contents.find_first_of(LF,CurrentLFPosition)) != string::npos)
  {
	LineNumber++;
	if(LineNumber > 0)LineNumberOffset = floor(log10(LineNumber));
	//cout << contents.substr(LastLFPosition,position) << endl;���ǹ����ģ�����Ϊ�ڶ����������ַ�������λ���𣬲��ǣ����ǳ��ȣ����ȣ�������
	//�Թ���һ�еĺ��ֱ���,����Ҫ�����һ�еĽ����������ļ��е�λ��
	if( LineNumber == -1)
	{
		LastLFPosition = CurrentLFPosition;
	}
	if( LineNumber != -1 )
	{
		/*
		//CurLnTimeFlagStartPosi -> ��ǰ�е�ʱ���ʶ��ʼλ�� = ��һ�л��з��Ž���λ�� + �����е�ʱ���ʶ��ʼλ�� +  �к����ӵ��µ�ƫ����
		//CurLnTimeFlagLength -> ��ǰ�е�ʱ���ʶ���� = ��ǰ�л��з�λ�� - ��һ�л��з��Ž���λ�� - �����е���С���� + ʱ���ʶ��ʽλ��Ϊ0.0000ʱ��ĳ��� + �к����ӵ��µ�ƫ����
		*/
		int CurLnTimeFlagStartPosi = LastLFPosition + TimeFlagStartPosi + LineNumberOffset;
		int CurLnTimeFlagLength = CurrentLFPosition - LastLFPosition - MinLengthofOneLine + MinLengthofTimeFlag - LineNumberOffset;
		//cout << contents.substr(CurLnTimeFlagStartPosi,CurLnTimeFlagLength) << endl;//����ʱ���ʶ��0.0000��ʼ
		OutputFiles << contents.substr(CurLnTimeFlagStartPosi,CurLnTimeFlagLength) << endl;
		//cout << "LastLFPosition is " << Linenumber << ":" << LastLFPosition << endl;
		LastLFPosition = CurrentLFPosition;
	}
	CurrentLFPosition ++;
  }
  cout << LineNumber << endl;
  cout << CurrentLFPosition << endl;
  //throw(errno);//�������׳��쳣������ô������,��ʵ��������Ļ���Ҳ��û�����
  //system ("Pause");
  OutputFiles.close();
  finish=clock();
  totaltime=(double)(finish-start)/CLOCKS_PER_SEC;
  cout<<"\n�˳��������ʱ��Ϊ"<<totaltime<<"��~"<<endl;
	return 0;
}