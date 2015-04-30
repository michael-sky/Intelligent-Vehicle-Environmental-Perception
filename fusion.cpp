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
#include <gl/freeglut.h> //ʹ��freeglut;
//#include <gl/glut.h> //ʹ��glut;
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
	cout<<"i am working"<<endl;
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
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(1.0f);
	//boost::thread_group grp;
	//grp.create_thread(&IbeoThreadFLeft);  // ʹ��create_thread 
	//grp.create_thread(&IbeoThreadFRight);  // ʹ��add_thread
	//grp.join_all();
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
	glutSwapBuffers();
}  


int draw_main(int argc, char *argv[])
{
	glutInit(&argc, argv);  
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE );  // �޸��˲���Ϊ GLUT_DOUBLE;
	glutInitWindowPosition(100, 100);  
	glutInitWindowSize(500, 500);  
	glutCreateWindow("��һ��OpenGL����");  
	glutDisplayFunc(&myDisplay); 

	clock_t t_start; /* start time when test starts */ 
	clock_t t_end; /* end time when test ends */ 
	while(true)
	{
		t_start = clock(); /* get start time */ 
		glutMainLoopEvent();
		boost::thread_group grp;
		grp.create_thread(&IbeoThreadFLeft);  // ʹ��create_thread 
		grp.create_thread(&IbeoThreadFRight);
		grp.join_all();
		glutPostRedisplay();
		t_end = clock();/* get end time */ 
		printf("time: %.3f s\n", (double)(t_end-t_start)/CLOCKS_PER_SEC); 	/*printf test time */ 
	}

//	glutMainLoop();  
	return 0;
}
	





int main(int argc, char *argv[])
{
	
	
	///*    �״��ʼ��   */
	////AllLidarInit();
	Fleft.init(FrontLeft);

	////****����ȫ�ֲɼ�����****/
	g_nMapUpdateTime=1;
	int time=0;

	
	while(g_nMapUpdateTime--)
	{
		/*ʹ�ö��߳̽������ݲɼ�*/
		//boost::thread_group grp;
		//grp.create_thread(&IbeoThreadFLeft);  // ʹ��create_thread 
		//grp.create_thread(&IbeoThreadFRight);  // ʹ��add_thread
		//grp.create_thread(boost::bind(draw_main,argc,argv));
		//////***************//
		////grp.create_thread(&runLidarML); 
		////grp.create_thread(&runLidarMR); 
//	////grp.create_thread(&runLidarBL); 
		////grp.create_thread(&runLidarBR);
		/*grp.join_all();*/
		//draw_main(argc,argv);
		/*IbeoThreadFLeft();
		IbeoThreadFRight();	*/
		/*DataClear(TempIbeoData.m_LidarScanFLeft);		//ȥ����Χ��ĵ�
		DataClear(TempIbeoData.m_LidarScanFRight);*/
		//draw_main(argc,argv);
	//	cout<<"time=over"<<time<<endl;
	}
	boost::thread_group grp;
	grp.create_thread(boost::bind(draw_main,argc,argv));
	
	
	while (	1)
	{
		cout<<"this is main program"<<time<<endl;
	}
	grp.join_all();

	cout<<"time=over"<<time<<endl;
	//t_end = clock();/* get end time */ 
	//printf("time: %.3f s\n", (double)(t_end-t_start)/CLOCKS_PER_SEC); 	/*printf test time */ 

	return 0;
}
