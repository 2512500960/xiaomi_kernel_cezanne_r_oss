/*
 *
 * FocalTech TouchScreen driver.
 *
 * Copyright (c) 2010-2017, Focaltech Ltd. All rights reserved.
 * Copyright (C) 2021 XiaoMi, Inc.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

/*****************************************************************************
*
* File Name: Focaltech_ex_fun.c
*
* Author: Focaltech Driver Team
*
* Created: 2016-08-08
*
* Abstract:
*
* Reference:
*
*****************************************************************************/

/*****************************************************************************
* 1.Included header files
*****************************************************************************/
#include "focaltech_core.h"

/*****************************************************************************
* Private constant and macro definitions using #define
*****************************************************************************/
/*create apk debug channel*/
#define PROC_UPGRADE					0
#define PROC_READ_REGISTER				1
#define PROC_WRITE_REGISTER				2
#define PROC_AUTOCLB					4
#define PROC_UPGRADE_INFO				5
#define PROC_WRITE_DATA					6
#define PROC_READ_DATA					7
#define PROC_SET_TEST_FLAG				8
#define PROC_SET_SLAVE_ADDR				10
#define PROC_HW_RESET					11
#define PROC_NAME						"ftxxxx-debug"
#define PROC_WRITE_BUF_SIZE				256
#define PROC_READ_BUF_SIZE				256

/*****************************************************************************
* Private enumerations, structures and unions using typedef
*****************************************************************************/

/*****************************************************************************
* Static variables
*****************************************************************************/
enum {
	RWREG_OP_READ = 0,
	RWREG_OP_WRITE = 1,
};
static struct rwreg_operation_t {
	int type;		/*  0: read, 1: write */
	int reg;		/*  register */
	int len;		/*  read/write length */
	int val;		/*  length = 1; read: return value, write: op return */
	int res;		/*  0: success, otherwise: fail */
	char *opbuf;		/*  length >= 1, read return value, write: op return */
} rw_op;

/*****************************************************************************
* Global variable or extern global variabls/functions
*****************************************************************************/
/*****************************************************************************
* Static function prototypes
*****************************************************************************/


/************************************************************************
 * sysfs interface
 ***********************************************************************/

/*
 * fts_hw_reset interface
 */
static ssize_t fts_hw_reset_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
	return -EPERM;
}

static ssize_t fts_hw_reset_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct input_dev *input_dev = fts_data->input_dev;
	ssize_t count = 0;

	mutex_lock(&input_dev->mutex);
	fts_reset_proc(1);
	count = snprintf(buf, PAGE_SIZE, "hw reset executed\n");
	mutex_unlock(&input_dev->mutex);

	return count;
}

/*
 * fts_irq interface
 */
static ssize_t fts_irq_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
	struct input_dev *input_dev = fts_data->input_dev;

	mutex_lock(&input_dev->mutex);
	if (FTS_SYSFS_ECHO_ON(buf)) {
		MI_TOUCH_LOGI(1, "[EX-FUN]enable irq");
		fts_irq_enable();
	} else if (FTS_SYSFS_ECHO_OFF(buf)) {
		MI_TOUCH_LOGI(1, "[EX-FUN]disable irq");
		fts_irq_disable();
	}
	mutex_unlock(&input_dev->mutex);
	return count;
}

static ssize_t fts_irq_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	return -EPERM;
}

/************************************************************************
* Name: fts_tprwreg_show
* Brief:  no
* Input: device, device attribute, char buf
* Output: no
* Return: EPERM
***********************************************************************/
static ssize_t fts_tprwreg_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	int count;
	int i;
	struct input_dev *input_dev = fts_data->input_dev;

	mutex_lock(&input_dev->mutex);

	if (rw_op.len < 0) {
		count = snprintf(buf, PAGE_SIZE, "Invalid cmd line\n");
	} else if (rw_op.len == 1) {
		if (RWREG_OP_READ == rw_op.type) {
			if (rw_op.res == 0) {
				count = snprintf(buf, PAGE_SIZE, "Read %02X: %02X\n", rw_op.reg, rw_op.val);
			} else {
				count = snprintf(buf, PAGE_SIZE, "Read %02X failed, ret: %d\n", rw_op.reg, rw_op.res);
			}
		} else {
			if (rw_op.res == 0) {
				count = snprintf(buf, PAGE_SIZE, "Write %02X, %02X success\n", rw_op.reg, rw_op.val);
			} else {
				count = snprintf(buf, PAGE_SIZE, "Write %02X failed, ret: %d\n", rw_op.reg, rw_op.res);
			}
		}
	} else {
		if (RWREG_OP_READ == rw_op.type) {
			count = snprintf(buf, PAGE_SIZE, "Read Reg: [%02X]-[%02X]\n", rw_op.reg, rw_op.reg + rw_op.len);
			count += snprintf(buf + count, PAGE_SIZE, "Result: ");
			if (rw_op.res) {
				count += snprintf(buf + count, PAGE_SIZE, "failed, ret: %d\n", rw_op.res);
			} else {
				if (rw_op.opbuf) {
					for (i = 0; i < rw_op.len; i++) {
						count += snprintf(buf + count, PAGE_SIZE, "%02X ", rw_op.opbuf[i]);
					}
					count += snprintf(buf + count, PAGE_SIZE, "\n");
				}
			}
		} else {
			;
			count =
			    snprintf(buf, PAGE_SIZE, "Write Reg: [%02X]-[%02X]\n", rw_op.reg,
				     rw_op.reg + rw_op.len - 1);
			count += snprintf(buf + count, PAGE_SIZE, "Write Data: ");
			if (rw_op.opbuf) {
				for (i = 1; i < rw_op.len; i++) {
					count += snprintf(buf + count, PAGE_SIZE, "%02X ", rw_op.opbuf[i]);
				}
				count += snprintf(buf + count, PAGE_SIZE, "\n");
			}
			if (rw_op.res) {
				count += snprintf(buf + count, PAGE_SIZE, "Result: failed, ret: %d\n", rw_op.res);
			} else {
				count += snprintf(buf + count, PAGE_SIZE, "Result: success\n");
			}
		}
		/*if (rw_op.opbuf) {
			kfree(rw_op.opbuf);
			rw_op.opbuf = NULL;
		} */
	}
	mutex_unlock(&input_dev->mutex);

	return count;
}

static int shex_to_int(const char *hex_buf, int size)
{
	int i;
	int base = 1;
	int value = 0;
	char single;

	for (i = size - 1; i >= 0; i--) {
		single = hex_buf[i];

		if ((single >= '0') && (single <= '9')) {
			value += (single - '0') * base;
		} else if ((single >= 'a') && (single <= 'z')) {
			value += (single - 'a' + 10) * base;
		} else if ((single >= 'A') && (single <= 'Z')) {
			value += (single - 'A' + 10) * base;
		} else {
			return -EINVAL;
		}

		base *= 16;
	}

	return value;
}

static u8 shex_to_u8(const char *hex_buf, int size)
{
	return (u8) shex_to_int(hex_buf, size);
}

/*
 * Format buf:
 * [0]: '0' write, '1' read(reserved)
 * [1-2]: addr, hex
 * [3-4]: length, hex
 * [5-6]...[n-(n+1)]: data, hex
 */
static int fts_parse_buf(const char *buf, size_t cmd_len)
{
	int length;
	int i;
	char *tmpbuf;

	rw_op.reg = shex_to_u8(buf + 1, 2);
	length = shex_to_int(buf + 3, 2);

	if (buf[0] == '1') {
		rw_op.len = length;
		rw_op.type = RWREG_OP_READ;
		MI_TOUCH_LOGN(1, "read %02X, %d bytes", rw_op.reg, rw_op.len);
	} else {
		if (cmd_len < (length * 2 + 5)) {
			MI_TOUCH_LOGE(1, "data invalided!");
			return -EINVAL;
		}
		MI_TOUCH_LOGN(1, "write %02X, %d bytes", rw_op.reg, length);

		/* first byte is the register addr */
		rw_op.type = RWREG_OP_WRITE;
		rw_op.len = length + 1;
	}

	if (rw_op.len > 0) {
		tmpbuf = (char *)kzalloc(rw_op.len, GFP_KERNEL);
		if (!tmpbuf) {
			MI_TOUCH_LOGE(1, "allocate memory failed!");
			return -ENOMEM;
		}

		if (RWREG_OP_WRITE == rw_op.type) {
			tmpbuf[0] = rw_op.reg & 0xFF;
			MI_TOUCH_LOGN(1, "write buffer: ");
			for (i = 1; i < rw_op.len; i++) {
				tmpbuf[i] = shex_to_u8(buf + 5 + i * 2 - 2, 2);
				MI_TOUCH_LOGN(1, "buf[%d]: %02X", i, tmpbuf[i] & 0xFF);
			}
		}
		rw_op.opbuf = tmpbuf;
	}

	return rw_op.len;
}

/************************************************************************
* Name: fts_tprwreg_store
* Brief:  read/write register
* Input: device, device attribute, char buf, char count
* Output: print register value
* Return: char count
***********************************************************************/
static ssize_t fts_tprwreg_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
	struct input_dev *input_dev = fts_data->input_dev;
	struct i2c_client *client = container_of(dev, struct i2c_client, dev);
	ssize_t cmd_length = 0;

	mutex_lock(&input_dev->mutex);
	cmd_length = count - 1;

	if (rw_op.opbuf) {
		kfree(rw_op.opbuf);
		rw_op.opbuf = NULL;
	}

	MI_TOUCH_LOGN(1, "cmd len: %d, buf: %s", (int)cmd_length, buf);
	/* compatible old ops */
	if (2 == cmd_length) {
		rw_op.type = RWREG_OP_READ;
		rw_op.len = 1;

		rw_op.reg = shex_to_int(buf, 2);
	} else if (4 == cmd_length) {
		rw_op.type = RWREG_OP_WRITE;
		rw_op.len = 1;
		rw_op.reg = shex_to_int(buf, 2);
		rw_op.val = shex_to_int(buf + 2, 2);

	} else if (cmd_length < 5) {
		MI_TOUCH_LOGE(1, "Invalid cmd buffer");
		mutex_unlock(&input_dev->mutex);
		return -EINVAL;
	} else {
		rw_op.len = fts_parse_buf(buf, cmd_length);
	}

#if FTS_ESDCHECK_EN
	fts_esdcheck_proc_busy(1);
#endif
	if (rw_op.len < 0) {
		MI_TOUCH_LOGE(1, "cmd buffer error!");

	} else {
		if (RWREG_OP_READ == rw_op.type) {
			if (rw_op.len == 1) {
				u8 reg, val;
				reg = rw_op.reg & 0xFF;
				rw_op.res = fts_i2c_read_reg(client, reg, &val);
				rw_op.val = val;
			} else {
				char reg;
				reg = rw_op.reg & 0xFF;

				rw_op.res = fts_i2c_read(client, &reg, 1, rw_op.opbuf, rw_op.len);
			}

			if (rw_op.res < 0) {
				MI_TOUCH_LOGE(1, "Could not read 0x%02x", rw_op.reg);
			} else {
				MI_TOUCH_LOGI(1, "read 0x%02x, %d bytes successful", rw_op.reg, rw_op.len);
				rw_op.res = 0;
			}

		} else {
			if (rw_op.len == 1) {
				u8 reg, val;
				reg = rw_op.reg & 0xFF;
				val = rw_op.val & 0xFF;
				rw_op.res = fts_i2c_write_reg(client, reg, val);
			} else {
				rw_op.res = fts_i2c_write(client, rw_op.opbuf, rw_op.len);
			}
			if (rw_op.res < 0) {
				MI_TOUCH_LOGE(1, "Could not write 0x%02x", rw_op.reg);

			} else {
				MI_TOUCH_LOGI(1, "Write 0x%02x, %d bytes successful", rw_op.val, rw_op.len);
				rw_op.res = 0;
			}
		}
	}

#if FTS_ESDCHECK_EN
	fts_esdcheck_proc_busy(0);
#endif
	mutex_unlock(&input_dev->mutex);

	return count;
}

/*
 * fts_upgrade_bin interface
 */
static ssize_t fts_fwupgradebin_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	return -EPERM;
}

static ssize_t fts_fwupgradebin_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
	char fwname[FILE_NAME_LENGTH];
	struct fts_ts_data *ts_data = fts_data;
	struct input_dev *input_dev = ts_data->input_dev;
	struct i2c_client *client = ts_data->client;

	if ((count <= 1) || (count >= FILE_NAME_LENGTH - 32)) {
		MI_TOUCH_LOGE(1, "fw bin name's length(%d) fail", (int)count);
		return -EINVAL;
	}
	memset(fwname, 0, sizeof(fwname));
	snprintf(fwname, PAGE_SIZE, "%s", buf);
	fwname[count - 1] = '\0';

	MI_TOUCH_LOGI(1, "upgrade with bin file through sysfs node");
	mutex_lock(&input_dev->mutex);
	ts_data->fw_loading = 1;
	fts_irq_disable();
#if FTS_ESDCHECK_EN
	fts_esdcheck_switch(DISABLE);
#endif

	fts_upgrade_bin(client, fwname, 0);

#if FTS_ESDCHECK_EN
	fts_esdcheck_switch(ENABLE);
#endif
	fts_irq_enable();
	ts_data->fw_loading = 0;
	mutex_unlock(&input_dev->mutex);

	return count;
}

/*
 * fts_force_upgrade interface
 */
static ssize_t fts_fwforceupg_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	return -EPERM;
}

static ssize_t fts_fwforceupg_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
	char fwname[FILE_NAME_LENGTH];
	struct fts_ts_data *ts_data = fts_data;
	struct input_dev *input_dev = ts_data->input_dev;
	struct i2c_client *client = ts_data->client;

	if ((count <= 1) || (count >= FILE_NAME_LENGTH - 32)) {
		MI_TOUCH_LOGE(1, "fw bin name's length(%d) fail", (int)count);
		return -EINVAL;
	}
	memset(fwname, 0, sizeof(fwname));
	snprintf(fwname, PAGE_SIZE, "%s", buf);
	fwname[count - 1] = '\0';

	MI_TOUCH_LOGI(1, "force upgrade through sysfs node");
	mutex_lock(&input_dev->mutex);
	ts_data->fw_loading = 1;
	fts_irq_disable();
#if FTS_ESDCHECK_EN
	fts_esdcheck_switch(DISABLE);
#endif

	fts_upgrade_bin(client, fwname, 1);

#if FTS_ESDCHECK_EN
	fts_esdcheck_switch(ENABLE);
#endif
	fts_irq_enable();
	ts_data->fw_loading = 0;
	mutex_unlock(&input_dev->mutex);

	return count;
}

/*
 * fts_driver_version interface
 */
static ssize_t fts_driverversion_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	int count;
	struct input_dev *input_dev = fts_data->input_dev;

	mutex_lock(&input_dev->mutex);
	count = snprintf(buf, PAGE_SIZE, FTS_DRIVER_VERSION "\n");
	mutex_unlock(&input_dev->mutex);

	return count;
}

static ssize_t fts_driverversion_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
	return -EPERM;
}

/*
 * fts_dump_reg interface
 */
static ssize_t fts_dumpreg_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
	return -EPERM;
}

static ssize_t fts_dumpreg_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	int count = 0;
	u8 val = 0;
	struct i2c_client *client = container_of(dev, struct i2c_client, dev);
	struct input_dev *input_dev = fts_data->input_dev;

	mutex_lock(&input_dev->mutex);
#if FTS_ESDCHECK_EN
	fts_esdcheck_proc_busy(1);
#endif
	fts_i2c_read_reg(client, FTS_REG_POWER_MODE, &val);
	count += snprintf(buf + count, PAGE_SIZE, "Power Mode:0x%02x\n", val);

	fts_i2c_read_reg(client, FTS_REG_FW_VER, &val);
	count += snprintf(buf + count, PAGE_SIZE, "FW Ver:0x%02x\n", val);

	fts_i2c_read_reg(client, FTS_REG_LIC_VER, &val);
	count += snprintf(buf + count, PAGE_SIZE, "LCD Initcode Ver:0x%02x\n", val);

	fts_i2c_read_reg(client, FTS_REG_IDE_PARA_VER_ID, &val);
	count += snprintf(buf + count, PAGE_SIZE, "Param Ver:0x%02x\n", val);

	fts_i2c_read_reg(client, FTS_REG_IDE_PARA_STATUS, &val);
	count += snprintf(buf + count, PAGE_SIZE, "Param status:0x%02x\n", val);

	fts_i2c_read_reg(client, FTS_REG_VENDOR_ID, &val);
	count += snprintf(buf + count, PAGE_SIZE, "Vendor ID:0x%02x\n", val);

	fts_i2c_read_reg(client, FTS_REG_LCD_BUSY_NUM, &val);
	count += snprintf(buf + count, PAGE_SIZE, "LCD Busy Number:0x%02x\n", val);

	fts_i2c_read_reg(client, FTS_REG_GESTURE_EN, &val);
	count += snprintf(buf + count, PAGE_SIZE, "Gesture Mode:0x%02x\n", val);

	fts_i2c_read_reg(client, FTS_REG_CHARGER_MODE_EN, &val);
	count += snprintf(buf + count, PAGE_SIZE, "charge stat:0x%02x\n", val);

	fts_i2c_read_reg(client, FTS_REG_INT_CNT, &val);
	count += snprintf(buf + count, PAGE_SIZE, "INT count:0x%02x\n", val);

	fts_i2c_read_reg(client, FTS_REG_FLOW_WORK_CNT, &val);
	count += snprintf(buf + count, PAGE_SIZE, "ESD count:0x%02x\n", val);
#if FTS_ESDCHECK_EN
	fts_esdcheck_proc_busy(0);
#endif

	mutex_unlock(&input_dev->mutex);
	return count;
}

static ssize_t fts_fod_test_store(struct device *dev,
					struct device_attribute *attr,
					const char *buf, size_t count)
{
	int value = 0;
	struct input_dev *input_dev = fts_data->input_dev;

	MI_TOUCH_LOGE(1, "%s,buf:%s,count:%u\n",__func__, buf, count);
	sscanf(buf, "%u", &value);
	if (value) {
		input_report_key(input_dev, BTN_INFO, 1);
		input_sync(input_dev);
		input_mt_slot(input_dev, 0);
		input_mt_report_slot_state(input_dev, MT_TOOL_FINGER, 1);
		input_report_key(input_dev, BTN_TOUCH, 1);
		input_report_key(input_dev, BTN_TOOL_FINGER, 1);
		input_report_abs(input_dev, ABS_MT_TRACKING_ID, 0);
		input_report_abs(input_dev, ABS_MT_WIDTH_MAJOR, 1);
		input_report_abs(input_dev, ABS_MT_WIDTH_MINOR, 1);
		input_report_abs(input_dev, ABS_MT_POSITION_X, 540);
		input_report_abs(input_dev, ABS_MT_POSITION_Y, 2120);
		input_sync(input_dev);
	} else {
		input_report_key(input_dev, BTN_INFO, 0);
		input_mt_slot(input_dev, 0);
		input_mt_report_slot_state(input_dev, MT_TOOL_FINGER, 0);
		input_report_key(input_dev, BTN_TOUCH, 0);
		input_report_abs(input_dev, ABS_MT_TRACKING_ID, -1);
		input_sync(input_dev);
	}
	return count;
}

/* read and write register(s)
*   All data type is **HEX**
*   Single Byte:
*       read:   echo 88 > rw_reg ---read register 0x88
*       write:  echo 8807 > rw_reg ---write 0x07 into register 0x88
*   Multi-bytes:
*       [0:rw-flag][1-2: reg addr, hex][3-4: length, hex][5-6...n-n+1: write data, hex]
*       rw-flag: 0, write; 1, read
*       read:  echo 10005           > rw_reg ---read reg 0x00-0x05
*       write: echo 000050102030405 > rw_reg ---write reg 0x00-0x05 as 01,02,03,04,05
*  Get result:
*       cat rw_reg
*/
static DEVICE_ATTR(fts_rw_reg, S_IRUGO | S_IWUSR, fts_tprwreg_show, fts_tprwreg_store);
/*  upgrade from fw bin file   example:echo "*.bin" > fts_upgrade_bin */
static DEVICE_ATTR(fts_upgrade_bin, S_IRUGO | S_IWUSR, fts_fwupgradebin_show, fts_fwupgradebin_store);
static DEVICE_ATTR(fts_force_upgrade, S_IRUGO | S_IWUSR, fts_fwforceupg_show, fts_fwforceupg_store);
static DEVICE_ATTR(fts_driver_version, S_IRUGO | S_IWUSR, fts_driverversion_show, fts_driverversion_store);
static DEVICE_ATTR(fts_dump_reg, S_IRUGO | S_IWUSR, fts_dumpreg_show, fts_dumpreg_store);
static DEVICE_ATTR(fts_hw_reset, S_IRUGO | S_IWUSR, fts_hw_reset_show, fts_hw_reset_store);
static DEVICE_ATTR(fts_irq, S_IRUGO | S_IWUSR, fts_irq_show, fts_irq_store);
static DEVICE_ATTR(fod_test, S_IRUGO | S_IWUSR, NULL, fts_fod_test_store);


/* add your attr in here*/
static struct attribute *fts_attributes[] = {
	&dev_attr_fts_rw_reg.attr,
	&dev_attr_fts_dump_reg.attr,
	&dev_attr_fts_upgrade_bin.attr,
	&dev_attr_fts_force_upgrade.attr,
	&dev_attr_fts_driver_version.attr,
	&dev_attr_fts_hw_reset.attr,
	&dev_attr_fts_irq.attr,
	NULL
};

static struct attribute_group fts_attribute_group = {
	.attrs = fts_attributes
};

/************************************************************************
* Name: fts_create_sysfs
* Brief: create sysfs interface
* Input:
* Output:
* Return: return 0 if success
***********************************************************************/
int fts_create_sysfs(struct i2c_client *client)
{
	int ret = 0;

	ret = sysfs_create_group(&client->dev.kobj, &fts_attribute_group);
	if (ret) {
		MI_TOUCH_LOGE(1, "[EX]: sysfs_create_group() failed!!");
		sysfs_remove_group(&client->dev.kobj, &fts_attribute_group);
		return -ENOMEM;
	} else {
		MI_TOUCH_LOGI(1, "[EX]: sysfs_create_group() succeeded!!");
	}

	ret = sysfs_create_file(&fts_data->fts_touch_dev->kobj, &dev_attr_fod_test.attr);
	if (ret) {
		MI_TOUCH_LOGE(1, "[EX]: sysfs_create_file() failed!!");
		sysfs_remove_file(&fts_data->fts_touch_dev->kobj, &dev_attr_fod_test.attr);
		return -ENOMEM;
	} else {
		MI_TOUCH_LOGI(1, "[EX]: sysfs_create_file() succeeded!!");
	}

	return ret;
}

/************************************************************************
* Name: fts_remove_sysfs
* Brief: remove sysfs interface
* Input:
* Output:
* Return:
***********************************************************************/
int fts_remove_sysfs(struct i2c_client *client)
{
	sysfs_remove_group(&client->dev.kobj, &fts_attribute_group);
	return 0;
}
