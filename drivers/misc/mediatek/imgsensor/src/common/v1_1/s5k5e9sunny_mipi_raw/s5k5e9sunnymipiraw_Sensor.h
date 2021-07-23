/*
 * Copyright (C) 2018 XiaoMi, Inc.
 * Copyright (C) 2021 XiaoMi, Inc.
 * Copyright (C) 2020 XiaoMi, Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See http://www.gnu.org/licenses/gpl-2.0.html for more details.
 */
/*****************************************************************************
 *
 * Filename:
 * ---------
 *	 S5K5E9SUNNYmipi_Sensor.h
 *
 * Project:
 * --------
 *	 ALPS
 *
 * Description:
 * ------------
 *	 CMOS sensor header file
 *
 ****************************************************************************/
#ifndef _S5K5E9SUNNYMIPI_SENSOR_H
#define _S5K5E9SUNNYMIPI_SENSOR_H

static kal_uint16 s5k5e9sunny_init_setting[] = {
	0x0100, 0x00,
	0x0000, 0x04,
	0x0000, 0x55,
	0x0A02, 0x3F,
	0x0100, 0x00,
	0x3B45, 0x01,
	0x0B05, 0x01,
	0x392F, 0x01,
	0x3930, 0x00,
	0x3924, 0x7F,
	0x3925, 0xFD,
	0x3C08, 0xFF,
	0x3C09, 0xFF,
	0x3C31, 0xFF,
	0x3C32, 0xFF,
	0x3290, 0x10,
	0x3200, 0x01,
	0x3074, 0x06,
	0x3075, 0x2F,
	0x308A, 0x20,
	0x308B, 0x08,
	0x308C, 0x0B,
	0x3081, 0x07,
	0x307B, 0x85,
	0x307A, 0x0A,
	0x3079, 0x0A,
	0x306E, 0x71,
	0x306F, 0x28,
	0x301F, 0x20,
	0x3012, 0x4E,
	0x306B, 0x9A,
	0x3091, 0x16,
	0x30C4, 0x06,
	0x306A, 0x79,
	0x30B0, 0xFF,
	0x306D, 0x08,
	0x3084, 0x16,
	0x3070, 0x0F,
	0x30C2, 0x05,
	0x3069, 0x87,
	0x3C0F, 0x00,
	0x3083, 0x14,
	0x3080, 0x08,
	0x3C34, 0xEA,
	0x3C35, 0x5C,
	0x3931, 0x02,
};

static kal_uint16 s5k5e9sunny_preview_setting[] = {
	0x0100, 0x00,
	0x0136, 0x18,
	0x0137, 0x00,
	0x0305, 0x04,
	0x0306, 0x00,
	0x0307, 0x5F,
	0x030D, 0x04,
	0x030E, 0x00,
	0x030F, 0x92,
	0x3C1F, 0x00,
	0x3C17, 0x00,
	0x0112, 0x0A,
	0x0113, 0x0A,
	0x0114, 0x01,
	0x0820, 0x03,
	0x0821, 0x6C,
	0x0822, 0x00,
	0x0823, 0x00,
	0x3929, 0x0F,
	0x0344, 0x00,
	0x0345, 0x08,
	0x0346, 0x00,
	0x0347, 0x0A,
	0x0348, 0x0A,
	0x0349, 0x27,
	0x034A, 0x07,
	0x034B, 0x9D,
	0x034C, 0x0A,
	0x034D, 0x20,
	0x034E, 0x07,
	0x034F, 0x94,
	0x0900, 0x00,
	0x0901, 0x00,
	0x0381, 0x01,
	0x0383, 0x01,
	0x0385, 0x01,
	0x0387, 0x01,
	0x0101, 0x00,
	0x0340, 0x07,
	0x0341, 0xEE,
	0x0342, 0x0C,
	0x0343, 0x28,
	0x0200, 0x0B,
	0x0201, 0x9C,
	0x0202, 0x00,
	0x0203, 0x02,
	0x30B8, 0x2E,
	0x30BA, 0x36,
	0x3931, 0x02,
};

static kal_uint16 s5k5e9sunny_cap_setting[] = {
	0x0100, 0x00,
	0x0136, 0x18,
	0x0137, 0x00,
	0x0305, 0x04,
	0x0306, 0x00,
	0x0307, 0x5F,
	0x030D, 0x04,
	0x030E, 0x00,
	0x030F, 0x92,
	0x3C1F, 0x00,
	0x3C17, 0x00,
	0x0112, 0x0A,
	0x0113, 0x0A,
	0x0114, 0x01,
	0x0820, 0x03,
	0x0821, 0x6C,
	0x0822, 0x00,
	0x0823, 0x00,
	0x3929, 0x0F,
	0x0344, 0x00,
	0x0345, 0x08,
	0x0346, 0x00,
	0x0347, 0x0A,
	0x0348, 0x0A,
	0x0349, 0x27,
	0x034A, 0x07,
	0x034B, 0x9D,
	0x034C, 0x0A,
	0x034D, 0x20,
	0x034E, 0x07,
	0x034F, 0x94,
	0x0900, 0x00,
	0x0901, 0x00,
	0x0381, 0x01,
	0x0383, 0x01,
	0x0385, 0x01,
	0x0387, 0x01,
	0x0101, 0x00,
	0x0340, 0x07,
	0x0341, 0xEE,
	0x0342, 0x0C,
	0x0343, 0x28,
	0x0200, 0x0B,
	0x0201, 0x9C,
	0x0202, 0x00,
	0x0203, 0x02,
	0x30B8, 0x2E,
	0x30BA, 0x36,
};

static kal_uint16 s5k5e9sunny_normal_video_setting[] = {
	0x0100, 0x00,
	0x0136, 0x18,
	0x0137, 0x00,
	0x0305, 0x04,
	0x0306, 0x00,
	0x0307, 0x5F,
	0x030D, 0x04,
	0x030E, 0x00,
	0x030F, 0x92,
	0x3C1F, 0x00,
	0x3C17, 0x00,
	0x0112, 0x0A,
	0x0113, 0x0A,
	0x0114, 0x01,
	0x0820, 0x03,
	0x0821, 0x6C,
	0x0822, 0x00,
	0x0823, 0x00,
	0x3929, 0x0F,
	0x0344, 0x00,
	0x0345, 0x08,
	0x0346, 0x00,
	0x0347, 0x0A,
	0x0348, 0x0A,
	0x0349, 0x27,
	0x034A, 0x07,
	0x034B, 0x9D,
	0x034C, 0x0A,
	0x034D, 0x20,
	0x034E, 0x07,
	0x034F, 0x94,
	0x0900, 0x00,
	0x0901, 0x00,
	0x0381, 0x01,
	0x0383, 0x01,
	0x0385, 0x01,
	0x0387, 0x01,
	0x0101, 0x00,
	0x0340, 0x07,
	0x0341, 0xEE,
	0x0342, 0x0C,
	0x0343, 0x28,
	0x0200, 0x0B,
	0x0201, 0x9C,
	0x0202, 0x00,
	0x0203, 0x02,
	0x30B8, 0x2E,
	0x30BA, 0x36,
};

static kal_uint16 s5k5e9sunny_hs_video_setting[] = {
	0x0100, 0x00,
	0x0136, 0x18,
	0x0137, 0x00,
	0x0305, 0x04,
	0x0306, 0x00,
	0x0307, 0x5F,
	0x030D, 0x04,
	0x030E, 0x00,
	0x030F, 0x92,
	0x3C1F, 0x00,
	0x3C17, 0x00,
	0x0112, 0x0A,
	0x0113, 0x0A,
	0x0114, 0x01,
	0x0820, 0x03,
	0x0821, 0x6C,
	0x0822, 0x00,
	0x0823, 0x00,
	0x3929, 0x0F,
	0x0344, 0x00,
	0x0345, 0x08,
	0x0346, 0x00,
	0x0347, 0x0A,
	0x0348, 0x0A,
	0x0349, 0x27,
	0x034A, 0x07,
	0x034B, 0x9D,
	0x034C, 0x0A,
	0x034D, 0x20,
	0x034E, 0x07,
	0x034F, 0x94,
	0x0900, 0x00,
	0x0901, 0x00,
	0x0381, 0x01,
	0x0383, 0x01,
	0x0385, 0x01,
	0x0387, 0x01,
	0x0101, 0x00,
	0x0340, 0x07,
	0x0341, 0xEE,
	0x0342, 0x0C,
	0x0343, 0x28,
	0x0200, 0x0B,
	0x0201, 0x9C,
	0x0202, 0x00,
	0x0203, 0x02,
	0x30B8, 0x2E,
	0x30BA, 0x36,
};

static kal_uint16 s5k5e9sunny_slim_video_setting[] = {
	0x0100, 0x00,
	0x0136, 0x18,
	0x0137, 0x00,
	0x0305, 0x04,
	0x0306, 0x00,
	0x0307, 0x5F,
	0x030D, 0x04,
	0x030E, 0x00,
	0x030F, 0x92,
	0x3C1F, 0x00,
	0x3C17, 0x00,
	0x0112, 0x0A,
	0x0113, 0x0A,
	0x0114, 0x01,
	0x0820, 0x03,
	0x0821, 0x6C,
	0x0822, 0x00,
	0x0823, 0x00,
	0x3929, 0x0F,
	0x0344, 0x00,
	0x0345, 0x08,
	0x0346, 0x00,
	0x0347, 0x0A,
	0x0348, 0x0A,
	0x0349, 0x27,
	0x034A, 0x07,
	0x034B, 0x9D,
	0x034C, 0x0A,
	0x034D, 0x20,
	0x034E, 0x07,
	0x034F, 0x94,
	0x0900, 0x00,
	0x0901, 0x00,
	0x0381, 0x01,
	0x0383, 0x01,
	0x0385, 0x01,
	0x0387, 0x01,
	0x0101, 0x00,
	0x0340, 0x07,
	0x0341, 0xEE,
	0x0342, 0x0C,
	0x0343, 0x28,
	0x0200, 0x0B,
	0x0201, 0x9C,
	0x0202, 0x00,
	0x0203, 0x02,
	0x30B8, 0x2E,
	0x30BA, 0x36,
};

enum IMGSENSOR_MODE {
	IMGSENSOR_MODE_INIT,
	IMGSENSOR_MODE_PREVIEW,
	IMGSENSOR_MODE_CAPTURE,
	IMGSENSOR_MODE_VIDEO,
	IMGSENSOR_MODE_HIGH_SPEED_VIDEO,
	IMGSENSOR_MODE_SLIM_VIDEO,
};

struct imgsensor_mode_struct {
	kal_uint32 pclk;	//record different mode's pclk
	kal_uint32 linelength;	//record different mode's linelength
	kal_uint32 framelength;	//record different mode's framelength

	kal_uint8 startx;	//record different mode's startx of grabwindow
	kal_uint8 starty;	//record different mode's startx of grabwindow

	//record different mode's width of grabwindow
	kal_uint16 grabwindow_width;
	//record different mode's height of grabwindow
	kal_uint16 grabwindow_height;

	/*
	 * following for MIPIDataLowPwr2HighSpeedSettleDelayCount
	 * by different scenario
	 */
	kal_uint8 mipi_data_lp2hs_settle_dc;

	/* following for GetDefaultFramerateByScenario() */
	kal_uint16 max_framerate;
	kal_uint32 mipi_pixel_rate;
};

/* SENSOR PRIVATE STRUCT FOR VARIABLES*/
struct imgsensor_struct {
	kal_uint8 mirror;	//mirrorflip information

	kal_uint8 sensor_mode;	//record IMGSENSOR_MODE enum value

	kal_uint32 shutter;	//current shutter
	kal_uint16 gain;	//current gain

	kal_uint32 pclk;	//current pclk

	kal_uint32 frame_length;//current framelength
	kal_uint32 line_length;	//current linelength

	kal_uint32 min_frame_length;//current min framelength to max framerate
	kal_uint16 dummy_pixel;	//current dummypixel
	kal_uint16 dummy_line;	//current dummline
	kal_uint16 current_fps;	//current max fps
	kal_bool autoflicker_en;	//record autoflicker enable or disable
	kal_bool test_pattern;	//record test pattern mode or not
	kal_bool enable_secure;	/* run as secure driver or not */
	enum MSDK_SCENARIO_ID_ENUM current_scenario_id;	//current scenario id
	kal_uint8 ihdr_en;	//ihdr enable or disable

	kal_uint8 i2c_write_id;	//record current sensor's i2c write id
	kal_uint8 vendor_id;
	struct IMGSENSOR_AE_FRM_MODE ae_frm_mode;
	kal_uint8 current_ae_effective_frame;
};

/* SENSOR PRIVATE STRUCT FOR CONSTANT*/
struct imgsensor_info_struct {
	kal_uint16 sensor_id;	//record sensor id defined in Kd_imgsensor.h
	//#ifdef VENDOR_EDIT
	/*Zhenagjiang.zhu@camera.drv 2017/10/18,modify for different module */
	kal_uint16 module_id;
	//#endif
	kal_uint32 checksum_value;	//checksum value for Camera Auto Test
	//preview scenario relative information
	struct imgsensor_mode_struct pre;
	//capture scenario relative information
	struct imgsensor_mode_struct cap;
	//capture for PIP 24fps relative information
	struct imgsensor_mode_struct cap1;
	//normal video scenario relative information
	struct imgsensor_mode_struct normal_video;
	//high speed video scenario relative information
	struct imgsensor_mode_struct hs_video;
	//slim video for VT scenario relative information
	struct imgsensor_mode_struct slim_video;

	kal_uint8 ae_shut_delay_frame;	//shutter delay frame for AE cycle
	//sensor gain delay frame for AE cycle
	kal_uint8 ae_sensor_gain_delay_frame;
	kal_uint8 ae_ispGain_delay_frame;//isp gain delay frame for AE cycle
	kal_uint8  frame_time_delay_frame;
	kal_uint8 ihdr_support;	//1, support; 0,not support
	kal_uint8 ihdr_le_firstline;	//1,le first ; 0, se first
	kal_uint8 sensor_mode_num;	//support sensor mode num

	kal_uint8 cap_delay_frame;	//enter capture delay frame num
	kal_uint8 pre_delay_frame;	//enter preview delay frame num
	kal_uint8 video_delay_frame;	//enter video delay frame num
	kal_uint8 hs_video_delay_frame;//enter high speed video  delay frame num
	kal_uint8 slim_video_delay_frame;//enter slim video delay frame num

	kal_uint8 margin;	//sensor framelength & shutter margin
	kal_uint32 min_shutter;	//min shutter
	kal_uint32 min_gain;
	kal_uint32 max_gain;
	kal_uint32 min_gain_iso;
	kal_uint32 gain_step;
	kal_uint32 gain_type;
	//max framelength by sensor register's limitation
	kal_uint32 max_frame_length;

	kal_uint8 isp_driving_current;	//mclk driving current
	kal_uint8 sensor_interface_type;	//sensor_interface_type
	//0,MIPI_OPHY_NCSI2; 1,MIPI_OPHY_CSI2, default is NCSI2,
	//don't modify this para
	kal_uint8 mipi_sensor_type;
	//0, high speed signal auto detect; 1, use settle delay,unit is ns,
	//default is auto detect, don't modify this para
	kal_uint8 mipi_settle_delay_mode;
	kal_uint8 sensor_output_dataformat;
	kal_uint8 mclk;	//mclk value, suggest 24 or 26 for 24Mhz or 26Mhz

	kal_uint8 mipi_lane_num;	//mipi lane num
	//record sensor support all write id addr, only supprt 4,
	//must end with 0xff
	kal_uint8 i2c_addr_table[5];
	kal_uint32 i2c_speed;	//khz
};

/* SENSOR READ/WRITE ID */
//#define IMGSENSOR_WRITE_ID_1 (0x6c)
//#define IMGSENSOR_READ_ID_1  (0x6d)
//#define IMGSENSOR_WRITE_ID_2 (0x20)
//#define IMGSENSOR_READ_ID_2  (0x21)

extern int iReadRegI2C(u8 *a_pSendData, u16 a_sizeSendData,
		       u8 *a_pRecvData, u16 a_sizeRecvData,
		       u16 i2cId);
extern int iWriteRegI2C(u8 *a_pSendData, u16 a_sizeSendData, u16 i2cId);
extern int iBurstWriteReg_multi(u8 *pData, u32 bytes, u16 i2cId,
				u16 transfer_length, u16 timing);

#ifdef VENDOR_EDIT
extern void register_imgsensor_deviceinfo(char *name, char *version,
					  u8 module_id);
#endif

#endif
