/*
 * drivers/video/sunxi/disp2/disp/de/disp_tv.h
 *
 * Copyright (c) 2007-2019 Allwinnertech Co., Ltd.
 * Author: zhengxiaobin <zhengxiaobin@allwinnertech.com>
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
#ifndef __DISP_TV_H__
#define __DISP_TV_H__


#include "disp_private.h"

s32 disp_init_tv(void);//call by disp_display
s32 disp_tv_set_func(struct disp_device*  ptv, struct disp_tv_func * func);
s32 disp_tv_set_hpd(struct disp_device*  ptv, u32 state);

struct disp_device_private_data {
	u32 enabled;
	bool suspended;

	enum disp_tv_mode tv_mode;

	struct disp_tv_func tv_func;

	struct disp_video_timings *video_info;

	struct disp_clk_info lcd_clk;

	struct clk *clk;

	struct clk *clk_parent;

	u32 irq_no;

	u32 frame_per_sec;
	u32 usec_per_line;
	u32 judge_line;
};

s32 disp_tv_suspend(struct disp_device* ptv);
s32 disp_tv_resume(struct disp_device* ptv);


#endif
