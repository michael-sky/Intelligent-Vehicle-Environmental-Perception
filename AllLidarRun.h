

/************************************************************************/
	/* �״�����ͷ�ļ�;
	   
		
	*/
	/************************************************************************/



#include "database.h"
#include "ibeo.h"
#include "lidar.h"

//����ʵ��
extern SingleLineLidar lidar_BR;
extern SingleLineLidar lidar_BL;
extern SingleLineLidar lidar_ML;
extern SingleLineLidar lidar_MR;
extern IbeoData TempIbeoData;
extern IbeoLidar Fleft;
extern IbeoLidar FRight;


//����ʵ��
void AllLidarInit();	//	�����״��ʼ������;
void IbeoThreadFLeft();		//	ǰ��Ibeo�״�;
void IbeoThreadFRight();	//	ǰ��Ibeo�״�;
void runLidarML();
void runLidarMR();
void runLidarBL();
void runLidarBR();
