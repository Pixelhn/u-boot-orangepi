/*
 * Copyright (C) 2019 Allwinnertech, <liuli@allwinnertech.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 */
#include "include/eink_driver.h"
#include "include/eink_sys_source.h"
#include "lowlevel/eink_reg.h"

static struct index_manager *g_idx_mgr;

struct index_manager *get_index_manager(void)
{
	return g_idx_mgr;
}

int set_rmi_addr(struct index_manager *mgr)
{
	unsigned long inaddr = 0, outaddr = 0;

	inaddr = (unsigned long)mgr->rmi_paddr;
	outaddr = (unsigned long)mgr->rmi_paddr;/* in and out use same buf*/

	EINK_INFO_MSG("rmi paddr = 0x%p, vaddr = 0x%p\n",
		      mgr->rmi_paddr, mgr->rmi_vaddr);

	eink_set_rmi_inaddr(inaddr);
	eink_set_rmi_outaddr(outaddr);
	return 0;
}

int index_mgr_init(struct eink_manager *eink_mgr)
{
	int ret = 0;
	u32 width = 0, height = 0;
	struct index_manager *mgr = NULL;

	mgr = (struct index_manager *)malloc(sizeof(struct index_manager));
	if (!mgr) {
		pr_err("index mgr malloc failed!\n");
		ret = -ENOMEM;
		goto err_out;
	}
	memset(mgr, 0, sizeof(struct index_manager));

	width = eink_mgr->panel_info.width;
	height = eink_mgr->panel_info.height;
	mgr->rmi_size = width * height * 2;
	mgr->rmi_vaddr = malloc_aligned(mgr->rmi_size, ARCH_DMA_MINALIGN);
	if (!mgr->rmi_vaddr) {
		pr_err("%s:rmi malloc failed!\n", __func__);
		ret = -ENOMEM;
		goto err_out;
	}

	mgr->rmi_paddr = mgr->rmi_vaddr;
	memset(mgr->rmi_vaddr, 0xff, mgr->rmi_size);
	mgr->set_rmi_addr = set_rmi_addr;
	eink_mgr->index_mgr = mgr;

	return ret;

err_out:
	free(mgr);
	return ret;
}
