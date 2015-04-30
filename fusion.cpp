//======================================================================
/*! \�״��ںϳ���
 *
 * 
 * \author Tz 
 * \date 2015.3.3
 *
 *һ���ں�ȫ���״�ĳ���
 * 
 *///-----------
#include "init.h"
#include "ibeo.h"
#include "lidar.h"
#include "DataProcessing.h"
#include <boost/thread/thread.hpp>  
#include <boost/thread/mutex.hpp>  
#include <boost/bind.hpp>  
#include <tchar.h>
#include <gl\glut.h> 

//****************************************//
IbeoLidar Fleft;
IbeoLidar FRight;
SingleLineLidar lidar_BR;
SingleLineLidar lidar_BL;
SingleLineLidar lidar_ML;
SingleLineLidar lidar_MR;
//****************************************//



//****************************************//
//***���е��߼����״��ʼ������**************//
void AllLidarInit()
{
	if (g_nOpenflag[FrontLeft]==1 )
	{
		Fleft.init(FrontLeft);
	}
	
	if (g_nOpenflag[FrontLeft]!=1 && g_nOpenflag[FrontRight]==1)
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
	cerr<<"TempIbeoData.m_LidarScanFLeft " << TempIbeoData.m_LidarScanFLeft.size()<< std::endl;
	cerr<<"TempIbeoData.m_LidarObjectFLeft"<<TempIbeoData.m_LidarObjectFLeft.size()<<endl;
	cerr<<"TempIbeoData.m_LidarScanFRight"<<TempIbeoData.m_LidarScanFRight.size()<<endl;
	cerr<<"TempIbeoData.m_LidarObjectFRight"<<TempIbeoData.m_LidarObjectFRight.size()<<endl;
}


//****************************************//
//************���߼����״����г���**********//
void runLidarML()
{
	lidar_ML.beginScan(MidLeft);
	cerr<<"MidLeft.size= " << lidar_ML.m_LidarScanMLeft.size()<< std::endl;
}

void runLidarMR()
{
	lidar_MR.beginScan(MidRight);
	cerr<<"MidRight.size= " << lidar_MR.m_LidarScanMRight.size()<< std::endl;
}

void runLidarBL()
{
	lidar_BL.beginScan(BackLeft);
	cerr<<"BackLeft.size= " << lidar_BL.m_LidarScanBLeft.size()<< std::endl;
}

void runLidarBR()
{
	lidar_BR.beginScan(BackRight);
	cerr<<"BackRight.size= " << lidar_BR.m_LidarScanBRight.size()<< std::endl;
}

/************************************************************************/
/* ��ͼ�ĳ���                                                            */
/************************************************************************/
void myDisplay(void)  
{   
	glFlush();  
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(1.0f);

	IbeoThreadFLeft();
	IbeoThreadFRight();	
	/* ������ʹ�� glVertex*ϵ�к��� ;*/
	list<LidarData>::iterator i;
	glBegin( GL_POINTS);
	for (i=TempIbeoData.m_LidarScanFLeft.begin();i!=TempIbeoData.m_LidarScanFLeft.end();++i)
	{
		float drawX=i->GetScanX();
		float drawY=i->GetScanY();
		glVertex2f(drawX/500, drawY/500);

	}
	for (i=TempIbeoData.m_LidarScanFRight.begin();i!=TempIbeoData.m_LidarScanFRight.end();++i)
	{
		float drawX=i->GetScanX();
		float drawY=i->GetScanY();
		glVertex2f(drawX/500, drawY/500);
		glVertex2f(0,0);
	}
	
	glEnd();
	glFlush();
}  
int draw_main(int argc, char *argv[])
{
	glutInit(&argc, argv);  
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);  
	glutInitWindowPosition(100, 100);  
	glutInitWindowSize(500, 500);  
	glutCreateWindow("��һ��OpenGL����");  
	glutDisplayFunc(&myDisplay);  
	glutMainLoop();  
	return 0;
}
	




int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}
int main(int argc, char *argv[])
{
	clock_t t_start; /* start time when test starts */ 
	clock_t t_end; /* end time when test ends */ 
	
	
	///*    �״��ʼ��   */
	////AllLidarInit();
	Fleft.init(FrontLeft);

	////****����ȫ�ֲɼ�����****/
	g_nMapUpdateTime=1;
	int time=0;
	t_start = clock(); /* get start time */ 
	while(g_nMapUpdateTime--)
	{
		/*ʹ�ö��߳̽������ݲɼ�*/
		//boost::thread_group grp;
		//grp.create_thread(&IbeoThreadFLeft);  // ʹ��create_thread 
		//grp.create_thread(&IbeoThreadFRight);  // ʹ��add_thread
		////***************//
		//grp.create_thread(&runLidarML); 
		//grp.create_thread(&runLidarMR); 
		//grp.create_thread(&runLidarBL); 
		//grp.create_thread(&runLidarBR); 
		//grp.join_all();

		/*IbeoThreadFLeft();
		IbeoThreadFRight();	*/
		DataClear(TempIbeoData.m_LidarScanFLeft);
		DataClear(TempIbeoData.m_LidarScanFRight);
		draw_main(argc,argv);
		cout<<"time="<<time<<endl;
	}

	//t_end = clock();/* get end time */ 
	//printf("time: %.3f s\n", (double)(t_end-t_start)/CLOCKS_PER_SEC); 	/*printf test time */ 

	return 0;
}
