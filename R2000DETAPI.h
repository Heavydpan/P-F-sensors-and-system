#include <iostream>
#include "stdio.h"
#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"
#include<new> 
//#include <exception>
#pragma once

typedef struct
{
	int i_TotalGroup;
}CONFIG_HEAD;
typedef struct
{
	//		int i_Group=15;//�����־λ
	int i_TotalZone;//��Ӧ�����������
}CONFIG_GROUP_NUM;
typedef struct
{
	//		int i_Zone=16;//�����־λ
	int64_t l_NumofPoints;//��Ӧ�������
}CONFIG_ZONE_NUM;
typedef struct//��Ӧ�����ŵ���������
{
	float x;
	float y;
}CONFIG_XY;

class R2000DET
{
public:
	R2000DET();
	~R2000DET();

	bool b_Init = false;//�Ƿ��ʼ���ɹ�
	bool InitAPI();
	bool SetCW_CCW(bool CW_CCW);//true:CCW,false:CW
	bool StartGroup(int i_Group);
	bool StartGroup_ROS(int i_Group, char Topic[]);
	bool StopGroup(int i_Group);
	bool EndAPI();
	bool *GetStatus(char* PointBuffer);//���ر����ж���Ϣ
	int AllGroupNum = -1;//Config����������
	static int ZoneofGroup;//��ǰ���������
	int Group = -1;//��ǰʹ�õķ�����
	struct tmpData
	{
		uint16_t magic;
		uint16_t packet_type;
		uint32_t packet_size;
		uint16_t header_size;
		uint16_t scan_number;
		uint16_t packet_number;
		uint64_t timestamp_raw;
		uint64_t timestamp_sync;
		//	UINT32 status_flags;
		uint16_t status_flags;
		uint16_t scan_frequency;
		uint16_t status_flags1;
		uint16_t num_points_scan;
		uint16_t num_points_packet;
		uint16_t first_index;
		int32_t first_angle;
		int32_t angular_increment;
		uint32_t output_status;
		uint32_t field_status;
	}R2000Head;
private:
	bool GetGroupNum();
	int64_t GetConfigFilePos(int i_Group, int i_Zone, char *buff);
	//int64_t ByteofConfigBuffer = 0;
	//int GroupNumInZoneBuffer = 0;//ZoneBuffer��������ķ�����
	bool* isInZone(char* PointBuffer);//PointBuffer R2000ԭʼ����
	static		bool* isInZone_ROS(const sensor_msgs::LaserScan::ConstPtr& PointBuffer);
	static bool isInOneZone(float tmpx, float tmpy, double x, uint32_t start, char *Buffer);
	static int iVersion;//0:��ͨ�汾��1:ROS��2��3������Ĭ�ϣ�-1��δѡ��
	void a2b(double angle, double distance);
	static double x1;
	static double y1;
	char * buff = nullptr;//����Config
	static	char * ZoneBuffer;//ÿ�ν�����һ�����飬������������+��������
	static bool *Zone_Status;//ÿ������״̬
	bool CW_CCW = true;
	static void R2000StatusCallback(const sensor_msgs::LaserScan::ConstPtr& msg);
 
};