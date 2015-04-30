


#include "init.h"
#include <iostream>


using namespace std;




int DataClear(list<LidarData> &data)
{
	/************************************************************************/
	/* ����ϵͳ��Ƶ�Ҫ�� ��ǰ���� 80m���� 20m;
	    ������ࡢ�Ҳࡢ�� 10m ���������ͼ;
		�����Χ��ĵ�;
	*/
	/************************************************************************/
	const int s_nGridFrontLenth=8000; //����ǰ�����ȵ�λ8000cm;
	const int s_nGridBackLenth=1000;
	const int s_nGridWidth=1000;
	const int s_nCarLenth=1000;
	const int s_nCarWidth=1000;

	list<LidarData>::iterator i;
	for (i=data.begin();i!=data.end();++i)
	{
		if ((abs(i->GetScanX())) >(s_nGridWidth+s_nCarWidth ))
		{
			data.erase(i);
		}
		
		if (i->GetScanY()>s_nGridFrontLenth || i->GetScanY()<-(s_nCarLenth+s_nGridBackLenth))
		{
			data.erase(i);
		}
	}
	return 0;
}