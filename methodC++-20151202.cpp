#include <iostream>
#include <fstream>
#include <string>
#include <cerrno>
#include <math.h>
#include <time.h>
using namespace std;

//C++ API方法,怎么会瞬间读取了300M的文件呢
//版本更新测试

int main()
{
    const int TimeFlagStartPosi = 13;//第零行的时间标识起始位置，标准帧和扩展帧通用
	const int MinLengthofOneLine = 93; //从第0行开始，时间标识为0.0000格式时的最小行字符数
	const int MinLengthofTimeFlag = 6;//时间标识格式位数为0.0000时候的长度
	//后面的变量类型定义呢，不是int怎么办
	//计算程序运行时间c
	clock_t start,finish;
   double totaltime;
   start=clock();
   //设置读取的文件，其实直接拖文件到生成的exe话，也是可以的输出的
   std::ifstream in("ZLG.txt", std::ios::in | std::ios::binary);
   std::ofstream OutputFiles("TestResult.asc");//,ios::out | ios::binary | ios::app);//定义后面这些格式的话，好像就不能好好地写入文件了呢
	std::string contents;
  //当前循环换行符号的位置，以及上一个循环换行符号的位置
  string::size_type CurrentLFPosition = 0,LastLFPosition = 0;//由string类类型和vector类类型定义的类型，用以保存任意string对象或vector对象的长度
  if (in)//?
	 {
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
	  }
  //设置行结束标识，
  string LF = "\n";
  double LineNumber = -2;//行数，-2147483648~+2147483647，2^32,要多算两行才行啊
  int LineNumberOffset = 0;//行标号数字增加导致后续字符位置相对整体的偏移
  int FlagTypeIndicator = 0;//测试时间标识类型，帧ID类型，后续测试是ZLG文件格式还是VDCI文件格式
  while((CurrentLFPosition = contents.find_first_of(LF,CurrentLFPosition)) != string::npos
	  && FlagTypeIndicator != )
  {
	LineNumber++;

  while((CurrentLFPosition = contents.find_first_of(LF,CurrentLFPosition)) != string::npos)
  {
	LineNumber++;
	if(LineNumber > 0)LineNumberOffset = floor(log10(LineNumber));
	//cout << contents.substr(LastLFPosition,position) << endl;真是够蠢的，你以为第二个参数是字符串最后的位置吗，不是，那是长度，长度，懂不懂
	//略过第一行的汉字标题,但是要保存第一行的结束符的在文件中的位置
	if( LineNumber == -1)
	{
		LastLFPosition = CurrentLFPosition;
	}
	if( LineNumber != -1 )
	{
		/*
		//CurLnTimeFlagStartPosi -> 当前行的时间标识起始位置 = 上一行换行符号结束位置 + 第零行的时间标识起始位置 +  行号增加导致的偏移量
		//CurLnTimeFlagLength -> 当前行的时间标识长度 = 当前行换行符位置 - 上一行换行符号结束位置 - 第零行的最小长度 + 时间标识格式位数为0.0000时候的长度 + 行号增加导致的偏移量
		*/
		int CurLnTimeFlagStartPosi = LastLFPosition + TimeFlagStartPosi + LineNumberOffset;
		int CurLnTimeFlagLength = CurrentLFPosition - LastLFPosition - MinLengthofOneLine + MinLengthofTimeFlag - LineNumberOffset;
		//cout << contents.substr(CurLnTimeFlagStartPosi,CurLnTimeFlagLength) << endl;//假设时间标识从0.0000开始
		OutputFiles << contents.substr(CurLnTimeFlagStartPosi,CurLnTimeFlagLength) << endl;
		//cout << "LastLFPosition is " << Linenumber << ":" << LastLFPosition << endl;
		LastLFPosition = CurrentLFPosition;
	}
	CurrentLFPosition ++;
  }
  cout << LineNumber << endl;
  cout << CurrentLFPosition << endl;
  //throw(errno);//总是能抛出异常来，怎么回事呢,其实不用这个的话，也是没问题的
  //system ("Pause");
  OutputFiles.close();
  finish=clock();
  totaltime=(double)(finish-start)/CLOCKS_PER_SEC;
  cout<<"\n此程序的运行时间为"<<totaltime<<"秒~"<<endl;
	return 0;
}