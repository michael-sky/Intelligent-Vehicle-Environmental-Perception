



#include "AllLidarRun.h";


//����ÿ���״����ʵ��
SingleLineLidar lidar_BR;
SingleLineLidar lidar_BL;
SingleLineLidar lidar_ML;
SingleLineLidar lidar_MR;
IbeoData TempIbeoData;
IbeoLidar Fleft;
IbeoLidar FRight;

//****************************************//
//***���е��߼����״��ʼ������**************//
void AllLidarInit()
{
	if (g_nOpenflag[FrontLeft]==1 )
	{
		Fleft.init(FrontLeft);
	}

	if (g_nOpenflag[FrontLeft]!=1 && g_nOpenflag[FrontRight]==1) //���߼����״����ܴ�һ��;
	{
		FRight.init(FrontRight);
	}
	//****�����״�***********//
	if (g_nOpenflag[MidLeft]==1)
	{
		lidar_ML.open(MidLeft);
	}
	//****���ұ��״�***********//
	if (g_nOpenflag[MidRight]==1)
	{
		lidar_MR.open(MidRight);
	}

	if (g_nOpenflag[BackLeft]==1)
	{
		lidar_BL.open(BackLeft);
	}

	if (g_nOpenflag[BackRight]==1)
	{
		lidar_BR.open(BackRight);
	}

}


//****************************************//
//************���߼����״����г���**********//


void IbeoThreadFLeft()
{
	//**ǰ����߶��߼����״�**//
	Fleft.beginScan(FrontLeft);
}

void IbeoThreadFRight()
{
	//**ǰ���ұ߶��߼����״�**//
	FRight.beginScan(FrontRight);
	//cout<<"i am working"<<endl;
}


//****************************************//
//************���߼����״����г���**********//
void runLidarML()
{
	lidar_ML.beginScan(MidLeft);
	//cerr<<"MidLeft.size= " << lidar_ML.m_LidarScanData.size()<< std::endl;
}

void runLidarMR()
{
	lidar_MR.beginScan(MidRight);
	//	cerr<<"MidRight.size= " << lidar_MR.m_LidarScanData.size()<< std::endl;
}

void runLidarBL()
{
	lidar_BL.beginScan(BackLeft);
	//cerr<<"BackLeft.size= " << lidar_BL.m_LidarScanData.size()<< std::endl;
}

void runLidarBR()
{
	lidar_BR.beginScan(BackRight);
	//cerr<<"BackRight.size= " << lidar_BR.m_LidarScanData.size()<< std::endl;
}
